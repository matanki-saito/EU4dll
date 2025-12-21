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
    #include <cstdint>
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
    typedef unsigned char UCHAR;
    typedef char* LPSTR;
    typedef const char* LPCSTR;
    typedef uint64_t UINT64;
    typedef uint32_t UINT32;
    typedef uint16_t UINT16;
    typedef uint8_t UINT8;
    typedef uint8_t BYTE;
    typedef int errno_t;

    #define TRUE 1
    #define FALSE 0
    #define MAX_PATH 1024

    // Memory protection constants
    #define PAGE_EXECUTE_READWRITE 0x40
    #define PAGE_EXECUTE_READ 0x20
    #define PAGE_READWRITE 0x04
    #define PAGE_READONLY 0x02

    // Exception codes
    #define EXCEPTION_ACCESS_VIOLATION 0xC0000005L
    #define EXCEPTION_EXECUTE_HANDLER 1
    #define EXCEPTION_CONTINUE_SEARCH 0

    // Mach-O structures for macOS (equivalent to Windows PE structures)
    #include <mach-o/loader.h>
    #include <mach-o/nlist.h>
    #include <sys/mman.h>

    // Define Windows PE structure types as Mach-O equivalents
    typedef struct mach_header_64* PIMAGE_DOS_HEADER;
    typedef struct mach_header_64* PIMAGE_NT_HEADERS;
    typedef struct section_64* PIMAGE_SECTION_HEADER;
    typedef struct mach_header_64 IMAGE_DOS_HEADER;
    typedef struct mach_header_64 IMAGE_NT_HEADERS;
    typedef struct section_64 IMAGE_SECTION_HEADER;

    // Dummy structure for compatibility
    struct IMAGE_DATA_DIRECTORY {
        uint32_t VirtualAddress;
        uint32_t Size;
    };

    // Windows API functions
    HMODULE GetModuleHandle(void* unused);
    HMODULE GetModuleHandleA(LPCSTR moduleName);
    DWORD GetModuleFileName(HMODULE hModule, wchar_t* lpFilename, DWORD nSize);
    BOOL VirtualProtect(LPVOID lpAddress, size_t dwSize, DWORD flNewProtect, DWORD* lpflOldProtect);
    DWORD GetExceptionCode(void);

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
    #include <cstdint>
    #include <dlfcn.h>

    #define LIBRARY_EXPORT __attribute__((visibility("default")))
    #define LIBRARY_CALL

    // Define Windows-like types for Linux
    typedef void* HMODULE;
    typedef unsigned long DWORD;
    typedef void* LPVOID;
    typedef int BOOL;
    typedef wchar_t WCHAR;
    typedef unsigned char UCHAR;
    typedef char* LPSTR;
    typedef const char* LPCSTR;
    typedef uint64_t UINT64;
    typedef uint32_t UINT32;
    typedef uint16_t UINT16;
    typedef uint8_t UINT8;
    typedef uint8_t BYTE;
    typedef int errno_t;

    #define TRUE 1
    #define FALSE 0
    #define MAX_PATH 4096

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

    // Memory protection constants (same as macOS)
    #define PAGE_EXECUTE_READWRITE 0x40
    #define PAGE_EXECUTE_READ 0x20
    #define PAGE_READWRITE 0x04
    #define PAGE_READONLY 0x02

    // Exception codes
    #define EXCEPTION_ACCESS_VIOLATION 0xC0000005L
    #define EXCEPTION_EXECUTE_HANDLER 1
    #define EXCEPTION_CONTINUE_SEARCH 0

    // Windows API functions (forward declarations)
    HMODULE GetModuleHandle(void* unused);
    HMODULE GetModuleHandleA(LPCSTR moduleName);
    DWORD GetModuleFileName(HMODULE hModule, wchar_t* lpFilename, DWORD nSize);
    BOOL VirtualProtect(LPVOID lpAddress, size_t dwSize, DWORD flNewProtect, DWORD* lpflOldProtect);
    DWORD GetExceptionCode(void);

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
