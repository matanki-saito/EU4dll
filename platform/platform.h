#pragma once

// Platform abstraction layer for cross-platform support

#ifdef _WIN32
    #define PLATFORM_WINDOWS 1
    #include <windows.h>
    #include <shlobj.h>

    #define LIBRARY_EXPORT __declspec(dllexport)
    #define LIBRARY_CALL __stdcall

    // Windows types are already defined

#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
    #include <dlfcn.h>
    #include <mach-o/dyld.h>
    #include <unistd.h>
    #include <pwd.h>
    #include <CoreFoundation/CoreFoundation.h>

    #define LIBRARY_EXPORT __attribute__((visibility("default")))
    #define LIBRARY_CALL

    // Define Windows-like types for macOS
    typedef void* HMODULE;
    typedef unsigned long DWORD;
    typedef void* LPVOID;
    typedef int BOOL;
    typedef wchar_t WCHAR;

    #define TRUE 1
    #define FALSE 0
    #define MAX_PATH 1024

    // DLL attachment reasons
    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0

    // Language/locale macros
    #define MAKELANGID(p, s) ((((unsigned short)(s)) << 10) | (unsigned short)(p))
    #define LANG_JAPANESE 0x11
    #define LANG_CHINESE_SIMPLIFIED 0x04
    #define LANG_CHINESE_TRADITIONAL 0x04
    #define LANG_KOREAN 0x12
    #define LANG_ENGLISH 0x09
    #define SUBLANG_JAPANESE_JAPAN 0x01
    #define SUBLANG_CHINESE_SIMPLIFIED 0x02
    #define SUBLANG_CHINESE_TRADITIONAL 0x01
    #define SUBLANG_KOREAN 0x01
    #define SUBLANG_ENGLISH_US 0x01

#elif defined(__linux__)
    #define PLATFORM_LINUX 1
    #include <dlfcn.h>

    #define LIBRARY_EXPORT __attribute__((visibility("default")))
    #define LIBRARY_CALL

    // Define Windows-like types for Linux
    typedef void* HMODULE;
    typedef unsigned long DWORD;
    typedef void* LPVOID;
    typedef int BOOL;
    typedef wchar_t WCHAR;

    #define TRUE 1
    #define FALSE 0
    #define MAX_PATH 4096

    #define DLL_PROCESS_ATTACH 1
    #define DLL_PROCESS_DETACH 0

#endif

// Cross-platform functions
namespace Platform {
    // Get user documents directory
    bool GetDocumentsPath(WCHAR* path, size_t maxLen);

    // Get system locale
    DWORD GetSystemLocale();

    // Show message box (cross-platform)
    void ShowMessageBox(const WCHAR* message, const WCHAR* caption);

    // Get current executable path
    bool GetExecutablePath(WCHAR* path, size_t maxLen);
}
