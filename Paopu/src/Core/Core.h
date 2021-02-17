#pragma once

#ifdef _WIN32
    #ifdef _WIN64
        #define PAO_PLATFORM_WINDOWS
    #endif
#elif defined(__linux__)
    #define PAO_PLATFORM_LINUX
    #error "Linux is not currently supported!"
#endif

#ifdef PAO_PLATFORM_WINDOWS
    #if PAO_DYNAMIC_LINK
        #ifdef PAO_BUILD_DLL
            #define PAOPU_API __declspec(dllexport)
        #else
            #define PAOPU_API __declspec(dllimport)
        #endif
    #else
        #define PAOPU_API
    #endif
#else
    #error Paopu currently only supports Windows!
#endif

#define BIT(x) (1 << x)