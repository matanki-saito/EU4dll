#include "pch.h"
#include "plugin_64.h"

using namespace std;

namespace Ini {
	wstring constructIniPath() {
		// exeのパスを見つける
		wchar_t exe_path[1024];
		wchar_t drive[8];
		wchar_t dir[1024];
		wchar_t fname[128];
		wchar_t ext[128];

		GetModuleFileName(NULL, exe_path, 1024);

		_wsplitpath_s(exe_path, drive, dir, fname, ext);

		std::wstring newDir = std::wstring();
		newDir.append(dir);
		newDir.append(L"plugins");

		wchar_t ini_path[2048] = { 0 };

		_wmakepath_s(ini_path, drive, newDir.c_str(), L"plugin", L"ini");

		return ini_path;
	}

	void testMode(wstring ini_path, RunOptions *options) {
		wchar_t buf[64] = {0};
		DWORD  ret;

		ret = GetPrivateProfileString(
			L"options",
			L"ERROR_TEST",
			L"no",
			buf,
			64,
			ini_path.c_str()
		);
		options->test = lstrcmpW(buf, L"yes") == 0 ? true : false;
		if (options->test) {
			options->version = UNKNOWN;
		}
	}

	void separateCharacter(wstring ini_path, RunOptions* options) {
		wchar_t buf[64] = { 0 };
		DWORD  ret;

		ret = GetPrivateProfileString(
			L"options",
			L"SEPARATE_CHARACTER_CODE_POINT",
			L"32",
			buf,
			64,
			ini_path.c_str()
		);
		options->separateCharacterCodePoint  = _wtoi(buf);
	}

	void GetOptionsFromIni(RunOptions* options) {
		wstring ini_path = constructIniPath();

		testMode(ini_path, options);
		separateCharacter(ini_path, options);
	}
}