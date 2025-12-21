#include "platform.h"
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <iostream>

#ifdef PLATFORM_MACOS
#include <locale>
#include <codecvt>
#endif

#ifdef PLATFORM_LINUX
#include <unistd.h>
#include <locale>
#include <codecvt>
#include <sys/mman.h>
#endif

namespace Platform {

bool GetDocumentsPath(WCHAR* path, size_t maxLen) {
#ifdef PLATFORM_WINDOWS
    return SHGetSpecialFolderPathW(NULL, path, CSIDL_PERSONAL, 0) != 0;

#elif defined(PLATFORM_MACOS)
    // Get home directory
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        struct passwd* pw = getpwuid(getuid());
        if (pw) {
            homeDir = pw->pw_dir;
        }
    }

    if (!homeDir) {
        return false;
    }

    // Convert to wide string
    std::string docsPath = std::string(homeDir) + "/Documents";
    std::mbstowcs(path, docsPath.c_str(), maxLen);
    return true;

#elif defined(PLATFORM_LINUX)
    const char* homeDir = getenv("HOME");
    if (!homeDir) {
        return false;
    }

    std::string docsPath = std::string(homeDir) + "/Documents";
    std::mbstowcs(path, docsPath.c_str(), maxLen);
    return true;

#endif
}

DWORD GetSystemLocale() {
#ifdef PLATFORM_WINDOWS
    return ::GetSystemDefaultLCID();

#elif defined(PLATFORM_MACOS) || defined(PLATFORM_LINUX)
    // Try to detect locale from environment
    const char* lang = getenv("LANG");
    if (!lang) {
        lang = getenv("LC_ALL");
    }
    if (!lang) {
        return MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
    }

    std::string locale(lang);

    if (locale.find("ja") != std::string::npos) {
        return MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN);
    } else if (locale.find("zh_CN") != std::string::npos) {
        return MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED);
    } else if (locale.find("zh_TW") != std::string::npos || locale.find("zh_HK") != std::string::npos) {
        return MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_TRADITIONAL);
    } else if (locale.find("ko") != std::string::npos) {
        return MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN);
    }

    return MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

#endif
}

void ShowMessageBox(const WCHAR* message, const WCHAR* caption) {
#ifdef PLATFORM_WINDOWS
    MessageBoxW(NULL, message, caption, MB_OK);

#elif defined(PLATFORM_MACOS)
    // Convert wide strings to UTF-8
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string msgUtf8 = converter.to_bytes(message);
    std::string capUtf8 = converter.to_bytes(caption);

    // Use CoreFoundation to show alert dialog
    CFStringRef cfCaption = CFStringCreateWithCString(NULL, capUtf8.c_str(), kCFStringEncodingUTF8);
    CFStringRef cfMessage = CFStringCreateWithCString(NULL, msgUtf8.c_str(), kCFStringEncodingUTF8);

    CFUserNotificationDisplayAlert(
        0, // timeout (0 = no timeout)
        kCFUserNotificationStopAlertLevel,
        NULL, // icon URL
        NULL, // sound URL
        NULL, // localization URL
        cfCaption,
        cfMessage,
        NULL, // default button title (OK)
        NULL, // alternate button title
        NULL, // other button title
        NULL  // response flags
    );

    if (cfCaption) CFRelease(cfCaption);
    if (cfMessage) CFRelease(cfMessage);

#elif defined(PLATFORM_LINUX)
    // For Linux, just print to stderr
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::cerr << converter.to_bytes(caption) << ": "
              << converter.to_bytes(message) << std::endl;

#endif
}

bool GetExecutablePath(WCHAR* path, size_t maxLen) {
#ifdef PLATFORM_WINDOWS
    DWORD result = GetModuleFileNameW(NULL, path, (DWORD)maxLen);
    return result != 0 && result < maxLen;

#elif defined(PLATFORM_MACOS)
    char exePath[MAX_PATH];
    uint32_t size = sizeof(exePath);

    if (_NSGetExecutablePath(exePath, &size) == 0) {
        std::mbstowcs(path, exePath, maxLen);
        return true;
    }
    return false;

#elif defined(PLATFORM_LINUX)
    char exePath[MAX_PATH];
    ssize_t len = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);

    if (len != -1) {
        exePath[len] = '\0';
        std::mbstowcs(path, exePath, maxLen);
        return true;
    }
    return false;

#endif
}

} // namespace Platform

// Windows API implementations for non-Windows platforms
#if defined(PLATFORM_MACOS) || defined(PLATFORM_LINUX)

HMODULE GetModuleHandle(void* unused) {
    // Get the handle to the current process's main executable
    return dlopen(NULL, RTLD_LAZY);
}

HMODULE GetModuleHandleA(LPCSTR moduleName) {
    if (moduleName == NULL) {
        return GetModuleHandle(NULL);
    }
    // Try to get a handle to the specified module
    return dlopen(moduleName, RTLD_LAZY | RTLD_NOLOAD);
}

DWORD GetModuleFileName(HMODULE hModule, wchar_t* lpFilename, DWORD nSize) {
    char exePath[MAX_PATH];

#ifdef PLATFORM_MACOS
    uint32_t size = sizeof(exePath);
    if (_NSGetExecutablePath(exePath, &size) == 0) {
        std::mbstowcs(lpFilename, exePath, nSize);
        return std::wcslen(lpFilename);
    }
#else  // Linux
    ssize_t len = readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len != -1) {
        exePath[len] = '\0';
        std::mbstowcs(lpFilename, exePath, nSize);
        return std::wcslen(lpFilename);
    }
#endif
    return 0;
}

BOOL VirtualProtect(LPVOID lpAddress, size_t dwSize, DWORD flNewProtect, DWORD* lpflOldProtect) {
    // Use mprotect to change memory protection
    int prot = 0;

    switch (flNewProtect) {
        case PAGE_EXECUTE_READWRITE:
            prot = PROT_READ | PROT_WRITE | PROT_EXEC;
            break;
        case PAGE_EXECUTE_READ:
            prot = PROT_READ | PROT_EXEC;
            break;
        case PAGE_READWRITE:
            prot = PROT_READ | PROT_WRITE;
            break;
        case PAGE_READONLY:
            prot = PROT_READ;
            break;
        default:
            prot = PROT_READ | PROT_WRITE;
            break;
    }

    // Align address to page boundary
    uintptr_t addr = (uintptr_t)lpAddress;
    uintptr_t page_size = sysconf(_SC_PAGESIZE);
    uintptr_t aligned_addr = addr & ~(page_size - 1);
    size_t aligned_size = dwSize + (addr - aligned_addr);

    // Store old protection (we can't easily get it, so just set it to RW)
    if (lpflOldProtect) {
        *lpflOldProtect = PAGE_READWRITE;
    }

    return mprotect((void*)aligned_addr, aligned_size, prot) == 0 ? TRUE : FALSE;
}

DWORD GetExceptionCode(void) {
    // Not used on Unix-like systems, return 0
    return 0;
}

#endif
