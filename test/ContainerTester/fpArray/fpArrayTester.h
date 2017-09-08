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
    fpArray<ArrayValue> Array  = { ArrayValue() };
    vector<ArrayValue> Vector  = { ArrayValue() };
    
    uint32 TestedLength;
public:
    fpArrayTester(uint32 Len)
    {
        TestedLength = Len;
    }
    void ArrayFillTest()
    {
        for(uint32 i = 0;i<=TestedLength;i++)
        {
            Array.PushBack(ArrayValue());
        }
    }
    void VectorFillTest()
    {
        for(uint32 i = 0;i<=TestedLength;i++)
        {
            Vector.push_back(ArrayValue());
        }
    }
    void RunPushTest()
    {
        ArrayFillTest();
        VectorFillTest();
    }
};
#endif