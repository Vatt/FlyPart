#pragma once 
#ifndef _FP_ARRAY_TESTER_INCLUDE_
#define _FP_ARRAY_TESTER_INCLUDE_
#include "../../../FlyPartEngine/fpCommon/fpCommon.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
using namespace std;
class ArrayValue
{
    static uint32 Index;
    static uint32 FillerLength;
public:
    uint32 X,Y,Z,A;
    uint32 filler[12];
    ArrayValue(uint32 x,uint32 y, uint32 z, uint32 a)
        :X(x),Y(y),Z(z),A(a)
    {
            
    }
    ArrayValue()
    {
        Index++;
        X = Index; Y = Index; Z = Index; A = Index;
        for(auto i = 0;i<=12;i++)
        {
            filler[i] = Index;
        }
    }
    bool operator==(ArrayValue& other)
    {
        return this->X==other.X && this->Y==other.Y &&
               this->Z==other.Z && this->A==other.A;
    }
}; 
namespace tester {

    template <class _Ty>
    class allocator {
    public:
        static_assert(!is_const_v<_Ty>, "The C++ Standard forbids containers of const elements "
            "because allocator<const T> is ill-formed.");

        using _From_primary = allocator;

        using value_type = _Ty;

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty* pointer;
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty* const_pointer;

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef _Ty& reference;
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS typedef const _Ty& const_reference;

        using size_type = size_t;
        using difference_type = ptrdiff_t;

        using propagate_on_container_move_assignment = true_type;
        using is_always_equal _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS = true_type;

        template <class _Other>
        struct _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS rebind {
            using other = allocator<_Other>;
        };

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD _Ty* address(_Ty& _Val) const noexcept {
            return _STD addressof(_Val);
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD const _Ty* address(const _Ty& _Val) const noexcept {
            return _STD addressof(_Val);
        }

        constexpr allocator() noexcept {}

        constexpr allocator(const allocator&) noexcept = default;
        template <class _Other>
        constexpr allocator(const allocator<_Other>&) noexcept {}

        void deallocate(_Ty* const _Ptr, const size_t _Count) {
            // no overflow check on the following multiply; we assume _Allocate did that check
            _Deallocate<_New_alignof<_Ty>>(_Ptr, sizeof(_Ty) * _Count);
        }

        _NODISCARD __declspec(allocator) _Ty* allocate(_CRT_GUARDOVERFLOW const size_t _Count) {
            return static_cast<_Ty*>(_Allocate<_New_alignof<_Ty>>(_Get_size_of_n<sizeof(_Ty)>(_Count)));
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD __declspec(allocator) _Ty* allocate(
            _CRT_GUARDOVERFLOW const size_t _Count, const void*) {
            return allocate(_Count);
        }

        template <class _Objty, class... _Types>
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS void construct(_Objty* const _Ptr, _Types&&... _Args) {
            ::new (const_cast<void*>(static_cast<const volatile void*>(_Ptr))) _Objty(_STD forward<_Types>(_Args)...);
        }

        template <class _Uty>
        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS void destroy(_Uty* const _Ptr) {
            _Ptr->~_Uty();
        }

        _CXX17_DEPRECATE_OLD_ALLOCATOR_MEMBERS _NODISCARD size_t max_size() const noexcept {
            return static_cast<size_t>(-1) / sizeof(_Ty);
        }
    };
}
class fpArrayTester
{
private:
	static fpArray<ArrayValue>* Array;
	static vector<ArrayValue, tester::allocator<ArrayValue>>* Vector;
    
    static uint32 TestedLength;
public:
    static void InitTester(uint32 Len)
    {
		
		Array = new fpArray<ArrayValue>();
		Vector = new vector<ArrayValue, tester::allocator<ArrayValue>>();
        TestedLength = Len;
    }
    static void ArrayFillTest()
    {
        for(uint32 i = 0;i<=TestedLength;i++)
        {
            Array->PushBack(ArrayValue());
        }
    }
    static void VectorFillTest()
    {
        for(uint32 i = 0;i<=TestedLength;i++)
        {
            Vector->push_back(ArrayValue());
        }
    }
    static void RunPushTest()
    {
		std::chrono::time_point<std::chrono::system_clock> custom_start, custom_end, default_start, default_end;
		int custom_elapsed, default_elapsed;

		custom_start = std::chrono::system_clock::now();
		ArrayFillTest();
		custom_end = std::chrono::system_clock::now();
		custom_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(custom_end - custom_start).count();
		std::cout << "fpArray fill time(ns): " << custom_elapsed << std::endl;


		default_start = std::chrono::system_clock::now();
		VectorFillTest();
		default_end = std::chrono::system_clock::now();
		default_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(default_end - default_start).count();
		std::cout << "vector fill time(ns): " << default_elapsed << std::endl;

		std::cout << "Difference vector/fpArray(ns): "<< (float)((float)default_elapsed/ (float)custom_elapsed) << std::endl;
    }
};
#endif