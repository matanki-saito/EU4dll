#pragma once


#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

bool InitAutoUpdate(const path& folder);