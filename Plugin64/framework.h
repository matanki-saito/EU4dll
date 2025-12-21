#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
// Windows ヘッダー ファイル
#include <windows.h>
#else
// Use platform abstraction for non-Windows platforms
#include "../platform/platform.h"
#endif
