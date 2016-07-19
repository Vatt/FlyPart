#include "fpSharedPtr.h"
#include <iostream>
using namespace std;
namespace SmartPtrTest{
    struct test
    {
        int x, y, z;
        test(int x, int y, int z) :x(x), y(y), z(z) {}
        test(test const&  rv)
        {
            x = rv.x;y = rv.y;z = rv.z;
        }
        test(test&& rv)
        {
            x = rv.x;y = rv.y;z = rv.z;
        }
    };

    void SharedRefTestLValue(fpSharedRef<test>&  ref)
    {
        auto other (ref);
        cout << "in function ref counter(other): " << other.GetRefCount() << endl;
        cout << "in function ref counter(ref): " << ref.GetRefCount() << endl;
    }
    void WeakRefTestLValue(fpSharedRef<test>& ref)
    {
        fpWeakPtr<test> weak_1(ref);
        fpWeakPtr<test> weak_2(ref);
        cout<<"Two fpWeakPtr created from SharedRef"<<endl;
        cout<<"In function shared ref counter: "<<ref.GetRefCount()<<endl;
        cout<<"In function weak ref (weak_1) counter: "<<weak_1.GetRefCount()<<endl;
        cout<<"In function weak ref (weak_2) counter: "<<weak_2.GetRefCount()<<endl;
    }

    void SmartPtrTestRun()
    {
        fpSharedRef<test> SharedRef(new test(1,2,3));
        fpWeakPtr<test> WeakRef(SharedRef);
        cout<<"******************SmartPtrTest BEGIN***********************"<<endl;
        cout<<"Run LValue Functrion call ( void SharedRefTestLValue(fpSharedRef<test>& )"<<endl;
        cout << "before call SharedRefTestLValue shared counter: " << SharedRef.GetRefCount() << endl;
        SharedRefTestLValue(SharedRef);
        cout << "after call SharedRefTestLValue shared counter: " << SharedRef.GetRefCount() << endl;
        cout<<"End Copy Function Call"<<endl;
        cout<<"Run WeakRefTest"<<endl;
        cout << "before call WeakRefTestLValue weak counter: " << WeakRef.GetRefCount() << endl;
        cout << "before call WeakRefTestLValue shared counter: " << SharedRef.GetRefCount() << endl;
        WeakRefTestLValue(SharedRef);
        cout << "after call WeakRefTestLValue weak   counter: " << WeakRef.GetRefCount() << endl;
        cout << "after call WeakRefTestLValue shared counter: " << SharedRef.GetRefCount() << endl;
        cout<<"End WeakRefTest"<<endl;
        cout<<"after assignment SharedRef counter: "<<SharedRef.GetRefCount()<<endl;
        fpSharedRef<test> newRef = SharedRef;
        cout<<"before assignment SharedRef counter: "<<SharedRef.GetRefCount()<<endl;
        cout<<"before assignment newRef counter: "<<newRef.GetRefCount()<<endl;
        newRef.~fpSharedRef();
        cout<<"force destroy newRef, counter SharedRef: "<<SharedRef.GetRefCount()<<endl;
        cout<<"******************SmartPtrTest END**************************"<<endl;
    };

};
