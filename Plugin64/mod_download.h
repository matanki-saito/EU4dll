#pragma once

#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <filesystem>
#include <shlobj.h>
#include "plugin_64.h"

using namespace std;
using namespace std::filesystem;

namespace ModDownload {
	DllError Init();
}