
#ifndef _REFERENCE_COUNTER_
#define _REFERENCE_COUNTER_
#pragma once
#include "typedefs.h"
#include "../Core/CoreCommonHeader.h"
#define FORCE_THREADSAFE_REFERENCE 0
namespace fpTemplate {
	namespace SmartPtrPrivate {
		enum RefControllerMode {
			ThreadSafe = 0,
			NotThreadSafe = 1,
			Auto = FORCE_THREADSAFE_REFERENCE ? 0 : 1,
		};
		class fpRefControllerBase {
		public:
			FORCEINLINE explicit fpRefControllerBase(void *obj) :
				SharedReferenceCount(1),
				WeakReferenceCount(1),
				Object(obj)
			{}
			/*
			*TODO: int32?
			*/
			int32 SharedReferenceCount;
			int32 WeakReferenceCount;
			void* Object;
			virtual void DestroyObj() = 0;
			virtual ~fpRefControllerBase() {};
		private:
			fpRefControllerBase(fpRefControllerBase& const);
			//fpRefControllerBase(fpRefControllerBase&& const);
			fpRefControllerBase& operator=(fpRefControllerBase& const);
			//fpRefControllerBase& operator=(fpRefControllerBase&& const);
		};
		template<typename ObjType, typename DeleterType>
		class fpRefControllerWithDeleter :public fpRefControllerBase, private DeleterType
		{
			explicit fpRefControllerWithDeleter(void* obj, DeleterType&& deleter) :
				fpRefControllerBase(obj), DeleterType(fpTemplate::Move(deleter))
			{}
			virtual void DestroyObj() {
				(*static_cast<DeleterType*>(this)) ((ObjType*)static_cast<fpRefControllerBase*>(this)->Object);
			}
		};

		template<typename ObjType>
		struct DefaultDeleter {
			FORCEINLINE void operator()(ObjType* Obj) const {
				delete Obj;
			}
		};
		template<typename ObjType>
		inline fpRefControllerBase* MakeDefaultReferenceController(ObjType* Obj)
		{
			return new fpRefControllerWithDeleter<ObjType, DefaultDeleter<ObjType>>(Obj, DefaultDeleter<ObjType>());
		};
		template<typename ObjType,typename DeleterType>
		inline fpRefControllerBase* MakeCustomReferenceController(ObjType* Obj, DeleterType&& Deleter)
		{
			using _DeleterType = typename RemoveReference<DeleterType>::Type;
			return new fpRefControllerWithDeleter<ObjType, _DeleterType>(Obj, Forward<DeleterType>(Deleter));
		};



		template<RefControllerMode Mode> struct RefControllerOps;
		template<>
		struct RefControllerOps<RefControllerMode::ThreadSafe>{
			static FORCEINLINE int32 GetSharedRefCount(fpRefControllerBase* controller)
			{
				return static_cast<int32 const volatile&>(controller->SharedReferenceCount);
			}
			static FORCEINLINE void AddSharedRef(fpRefControllerBase* controller)
			{
				fpAtomics::InterlockedIncrement_i32(&controller->SharedReferenceCount);
			}
			static FORCEINLINE void ReleaseSharedRef(fpRefControllerBase* controller)
			{
				if (fpAtomics::InterlockedDecrement_i32(&controller->SharedReferenceCount) == 0)
				{
					controller->DestroyObj();
					ReleaseWeakReference(controller);
				}
			}
			static FORCEINLINE int32 GetWeakReference(fpRefControllerBase* controller)
			{
				return static_cast<int32 const volatile&>(controller->WeakReferenceCount);
			}
			static FORCEINLINE void AddWeakReference(fpRefControllerBase* controller)
			{
				fpAtomics::InterlockedIncrement_i32(&controller->WeakReferenceCount);
			}
			static FORCEINLINE void ReleaseWeakReference(fpRefControllerBase* controller)
			{
				if (fpAtomics::InterlockedDecrement_i32(&controller->WeakReferenceCount) == 0)
				{
					delete controller;
				}
			}
		};
		template<>
		struct RefControllerOps<RefControllerMode::NotThreadSafe> {
			static FORCEINLINE int32 GetSharedRefCount(fpRefControllerBase* controller)
			{
				return controller->SharedReferenceCount;
			}
			static FORCEINLINE void AddSharedRef(fpRefControllerBase* controller)
			{
				++controller->SharedReferenceCount;
			}
			static FORCEINLINE void ReleaseSharedRef(fpRefControllerBase* controller)
			{
				if ((--controller->SharedReferenceCount) == 0)
				{
					controller->DestroyObj();
					ReleaseWeakRef(controller);
				}
			}
			static FORCEINLINE int32 GetWeakRefCount(fpRefControllerBase* controller)
			{
				return controller->WeakReferenceCount;
			}
			static FORCEINLINE void AddWeakReference(fpRefControllerBase* controller)
			{
				++controller->WeakReferenceCount;
			}
			static FORCEINLINE void ReleaseWeakRef(fpRefControllerBase* controller)
			{
				if ((--controller->WeakReferenceCount) == 0)
				{
					delete controller;
				}
			}
		};


		template<RefControllerMode Mode>
		class fpSharedRefController {
		private:
			typedef RefControllerOps<Mode> OPS;
		public:
			fpSharedRefController() :_controller(nullptr)
			{}
			fpSharedRefController(fpRefControllerBase* InController):_controller(InController)
			{}
			fpSharedRefController(fpSharedRefController& const  InSharedReference)
				:_controller(InSharedReference._controller)
			{
				if (_controller != nullptr)
				{
					OPS::AddSharedReference(_controller);
				}
			}
			fpSharedRefController(fpSharedRefController&& const InSharedReference)
				:_controller(InSharedReference._controller)
			{
				InSharedReference._controller = nullptr;
			}

			inline fpSharedRefController& operator=(fpSharedRefController const& InSharedRefController)
			{
				auto NewController = InSharedRefController._controller;
				if (NewController != _controller)
				{
					if (NewController != nullptr)
					{
						OPS::AddSharedReference(NewController);
					}
					if (_controller != nullptr)
					{
						OPS::ReleaseSharedReference(_controller);
					}
					_controller = NewController;
				}
				return *this;
			}
			inline fpSharedRefController& operator=(fpSharedRefController&& inSharedRefController)
			{
				auto New = inSharedRefController._controller;
				auto Old = _controller;
				if (New != Old)
				{				
					inSharedRefController._controller = nullptr;
					_controller = New;
					if (Old != nullptr)
					{
						OPS::ReleaseSharedReference(Old);
					}
				}
				return *this;
			}
			FORCEINLINE bool isValid()
			{
				return _controller != nullptr;
			}
			FORCEINLINE const int32 GetSharedRefCount()const 
			{
				return _controller != nullptr ? OPS::GetSharedRefCount() : 0;
			}
			FORCEINLINE const bool isUnique()const
			{
				return GetSharedRefCount() == 1;
			}
			~fpSharedRefController() 
			{
				if (_controller != nullptr) 
				{
					OPS::ReleaseSharedRef(_controller);
				}
			}
		private:
			fpRefControllerBase* _controller;
		};
	};
};
#endif