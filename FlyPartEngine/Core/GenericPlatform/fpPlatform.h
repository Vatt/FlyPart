

#ifndef _FP_PLATFORM_H
#define _FP_PLATFORM_H
#include "defines.h"
#include "typedefs.h"
#ifdef PLATFORM_WINDOWS
    #include "../Windows/fpWindowsMemory.h"
    #include "../Windows/fpWindowsAtomics.h"
#endif
#ifdef PLATFORM_LINUX
    #include "../Linux/fpLinuxPlatformMemory.h"
    #include "../Linux/fpLinuxAtomics.h"
#endif
#endif //FLYPARTENGINE_FPPLATFORM_H
