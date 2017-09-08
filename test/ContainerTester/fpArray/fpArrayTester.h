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
class fpArrayTester
{
private:
	static fpArray<ArrayValue>* Array;
	static vector<ArrayValue>* Vector;
    
    static uint32 TestedLength;
public:
    static void InitTester(uint32 Len)
    {
		
		Array = new fpArray<ArrayValue>();
		Vector = new vector<ArrayValue>();
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