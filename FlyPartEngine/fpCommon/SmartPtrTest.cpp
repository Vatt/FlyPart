#include "fpSharedPtr.h"
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
    fpSharedRef<test> SharedRef(new test(1,2,3));
};