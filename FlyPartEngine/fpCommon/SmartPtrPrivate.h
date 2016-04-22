
#ifndef _REFERENCE_COUNTER_
#define _REFERENCE_COUNTER_
#pragma once
#include "typedefs.h"
#include "CommonHelperFunctions.h"
#include "../Core/CoreCommonHeader.h"
#define FORCE_THREADSAFE_REFERENCE 0
namespace fpTemplate {
	enum RefControllerMode {
		ThreadSafe = 0,
		NotThreadSafe = 1,
		Auto = FORCE_THREADSAFE_REFERENCE ? 0 : 1,
	};

	namespace SmartPtrPrivate {	

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
            fpRefControllerBase(const fpRefControllerBase& );
			//fpRefControllerBase(fpRefControllerBase&& const);
            fpRefControllerBase& operator=(const fpRefControllerBase& );
			//fpRefControllerBase& operator=(fpRefControllerBase&& const);
		};
		template<typename ObjType, typename DeleterType>
		class fpRefControllerWithDeleter :public fpRefControllerBase, private DeleterType
		{
		public:
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
                fpAtomics::InterlockedIncrement(&controller->SharedReferenceCount);
			}
			static FORCEINLINE void ReleaseSharedRef(fpRefControllerBase* controller)
			{
                if (fpAtomics::InterlockedDecrement(&controller->SharedReferenceCount) == 0)
				{
					controller->DestroyObj();
					ReleaseWeakRef(controller);
				}
			}
			static FORCEINLINE int32 GetWeakRefCount(fpRefControllerBase* controller)
			{
				return static_cast<int32 const volatile&>(controller->WeakReferenceCount);
			}
			static FORCEINLINE void AddWeakRef(fpRefControllerBase* controller)
			{
                fpAtomics::InterlockedIncrement(&controller->WeakReferenceCount);
			}
			static FORCEINLINE void ReleaseWeakRef(fpRefControllerBase* controller)
			{
                if (fpAtomics::InterlockedDecrement(&controller->WeakReferenceCount) == 0)
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
			static FORCEINLINE void AddWeakRef(fpRefControllerBase* controller)
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


		template <RefControllerMode Mode> class fpWeakRefCounter;

		template<RefControllerMode Mode>
        class fpSharedRefCounter {
		private:
			typedef RefControllerOps<Mode> OPS;
			template <RefControllerMode OtherMode> friend class fpWeakRefCounter;
		public:
            fpSharedRefCounter() :_controller(nullptr)
			{}
            fpSharedRefCounter(fpRefControllerBase* InController):_controller(InController)
			{}
            fpSharedRefCounter(fpSharedRefCounter const&  InSharedReference)
				:_controller(InSharedReference._controller)
			{
				if (_controller != nullptr)
				{
					OPS::AddSharedRef(_controller);
				}
			}
            fpSharedRefCounter(fpWeakRefCounter<Mode> const& InWeakRefCounter)
                :_controller(InWeakRefCounter._controller)
            {
                if(_controller != nullptr)
                {
                    OPS::AddSharedRef(_controller);
                }
            }

            fpSharedRefCounter(fpSharedRefCounter&& InSharedReference)
				:_controller(InSharedReference._controller)
			{
				InSharedReference._controller = nullptr;
			}

            inline fpSharedRefCounter& operator=(fpSharedRefCounter const& InSharedRefCounter)
			{
                auto NewController = InSharedRefCounter._controller;
				if (NewController != _controller)
				{
					if (NewController != nullptr)
					{
						OPS::AddSharedRef(NewController);
					}
					if (_controller != nullptr)
					{
						OPS::ReleaseSharedRef(_controller);
					}
					_controller = NewController;
				}
				return *this;
			}
            inline fpSharedRefCounter& operator=(fpSharedRefCounter&& InSharedRefCounter)
			{
                auto New = InSharedRefCounter._controller;
				auto Old = _controller;
				if (New != Old)
				{				
                    InSharedRefCounter._controller = nullptr;
					_controller = New;
					if (Old != nullptr)
					{
						OPS::ReleaseSharedRef(Old);
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
				return _controller != nullptr ? OPS::GetSharedRefCount(_controller) : 0;
			}
			FORCEINLINE const bool isUnique()const
			{
				return GetSharedRefCount() == 1;
			}
            ~fpSharedRefCounter()
			{
				if (_controller != nullptr) 
				{
					OPS::ReleaseSharedRef(_controller);
				}
			}
		private:
			fpRefControllerBase* _controller;
		};


        template<RefControllerMode Mode>
        class fpWeakRefCounter{
        private:
            typedef RefControllerOps<Mode> OPS;
        public:
            FORCEINLINE fpWeakRefCounter():_controller(nullptr)
            {}
            FORCEINLINE fpWeakRefCounter(fpWeakRefCounter const& InWeakRefCounter)
                :_controller(InWeakRefCounter._controller)
            {
                if(_controller!=nullptr)
                {
                    OPS::AddWeakRef(_controller);
                }
            }
            FORCEINLINE fpWeakRefCounter(fpWeakRefCounter&& InWeakRefCounter)
                :_controller(InWeakRefCounter._controller)
            {
                InWeakRefCounter._controller = nullptr;
            }
            FORCEINLINE fpWeakRefCounter(fpSharedRefCounter<Mode> const& InSharedRefCounter)
                :_controller(InSharedRefCounter._controller)

            {
                if (_controller != nullptr)
                {
                    OPS::AddWeakRef(_controller);
                }
            }

            FORCEINLINE fpWeakRefCounter& operator=(fpWeakRefCounter const& InWeakRefCounter)
            {
                auto New = InWeakRefCounter._controller;
                if (New!=_controller){
                    if (New!=nullptr)
                    {
                        OPS::AddWeakRef(New);
                    }
                    if (_controller!=nullptr)
                    {
                        OPS::ReleaseWeakRef(_controller);
                    }
                    _controller = New;
                }
                return *this;
            }
            inline fpWeakRefCounter& operator=(fpWeakRefCounter&& InWeakRefCounter)
            {

            }
            FORCEINLINE const bool isValid()const
            {
                return _controller!=nullptr;
            }
            FORCEINLINE const bool isUnique()const
            {
                return _controller->WeakReferenceCount==1;
            }
            FORCEINLINE const int32 GetWeakRefCount()const
            {
                return _controller->WeakReferenceCount;
            }
            ~fpWeakRefCounter()
            {
                if(_controller!=nullptr)
                {
                    OPS::ReleaseWeakRef(_controller);
                }
            }
        private:
            fpRefControllerBase* _controller;
        };
	};
};
#endif
