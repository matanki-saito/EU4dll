// This is a very simplified version of Ultimate ASI Loader
// https://github.com/ThirteenAG/Ultimate-ASI-Loader

#include <windows.h>
#include <KnownFolders.h>
#include <filesystem>
#include <ShlObj.h>
#include <Objbase.h>
#include "auto_update.h"

using namespace std;
using namespace std::filesystem;
extern "C" {
	struct
	{
		FARPROC GetFileVersionInfoA;
		FARPROC GetFileVersionInfoByHandle;
		FARPROC GetFileVersionInfoExA;
		FARPROC GetFileVersionInfoExW;
		FARPROC GetFileVersionInfoSizeA;
		FARPROC GetFileVersionInfoSizeExA;
		FARPROC GetFileVersionInfoSizeExW;
		FARPROC GetFileVersionInfoSizeW;
		FARPROC GetFileVersionInfoW;
		FARPROC VerFindFileA;
		FARPROC VerFindFileW;
		FARPROC VerInstallFileA;
		FARPROC VerInstallFileW;
		FARPROC VerLanguageNameA;
		FARPROC VerLanguageNameW;
		FARPROC VerQueryValueA;
		FARPROC VerQueryValueW;

		void LoadOriginalLibrary(HMODULE module)
		{
			GetFileVersionInfoA = GetProcAddress(module, "GetFileVersionInfoA");
			GetFileVersionInfoByHandle = GetProcAddress(module, "GetFileVersionInfoByHandle");
			GetFileVersionInfoExA = GetProcAddress(module, "GetFileVersionInfoExA");
			GetFileVersionInfoExW = GetProcAddress(module, "GetFileVersionInfoExW");
			GetFileVersionInfoSizeA = GetProcAddress(module, "GetFileVersionInfoSizeA");
			GetFileVersionInfoSizeExA = GetProcAddress(module, "GetFileVersionInfoSizeExA");
			GetFileVersionInfoSizeExW = GetProcAddress(module, "GetFileVersionInfoSizeExW");
			GetFileVersionInfoSizeW = GetProcAddress(module, "GetFileVersionInfoSizeW");
			GetFileVersionInfoW = GetProcAddress(module, "GetFileVersionInfoW");
			VerFindFileA = GetProcAddress(module, "VerFindFileA");
			VerFindFileW = GetProcAddress(module, "VerFindFileW");
			VerInstallFileA = GetProcAddress(module, "VerInstallFileA");
			VerInstallFileW = GetProcAddress(module, "VerInstallFileW");
			VerLanguageNameA = GetProcAddress(module, "VerLanguageNameA");
			VerLanguageNameW = GetProcAddress(module, "VerLanguageNameW");
			VerQueryValueA = GetProcAddress(module, "VerQueryValueA");
			VerQueryValueW = GetProcAddress(module, "VerQueryValueW");
		}
	} version;
	void _GetFileVersionInfoA() { version.GetFileVersionInfoA(); }
    void _GetFileVersionInfoByHandle() { version.GetFileVersionInfoByHandle(); }
    void _GetFileVersionInfoExA() { version.GetFileVersionInfoExA(); }
    void _GetFileVersionInfoExW() { version.GetFileVersionInfoExW(); }
    void _GetFileVersionInfoSizeA() { version.GetFileVersionInfoSizeA(); }
    void _GetFileVersionInfoSizeExA() { version.GetFileVersionInfoSizeExA(); }
    void _GetFileVersionInfoSizeExW() { version.GetFileVersionInfoSizeExW(); }
    void _GetFileVersionInfoSizeW() { version.GetFileVersionInfoSizeW(); }
    void _GetFileVersionInfoW() { version.GetFileVersionInfoW(); }
    void _VerFindFileA() { version.VerFindFileA(); }
    void _VerFindFileW() { version.VerFindFileW(); }
    void _VerInstallFileA() { version.VerInstallFileA(); }
    void _VerInstallFileW() { version.VerInstallFileW(); }
    void _VerLanguageNameA() { version.VerLanguageNameA(); }
    void _VerLanguageNameW() { version.VerLanguageNameW(); }
    void _VerQueryValueA() { version.VerQueryValueA(); }
    void _VerQueryValueW() { version.VerQueryValueW(); }
}

void initInjector()
{
	wchar_t* pVersionPath;
	path versionPath;

	SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &pVersionPath);
	versionPath = path{ pVersionPath } / L"version.dll";
	CoTaskMemFree(pVersionPath);

	version.LoadOriginalLibrary(LoadLibraryW(versionPath.c_str()));
}

void LoadScripts(const path& folder)
{
	directory_iterator dirit{ folder };

	while (dirit != directory_iterator{})
	{
		auto _path = dirit->path();

		if (is_regular_file(_path) && _path.extension() == L".dll")
		{
			LoadLibraryW(_path.c_str());
		}

		++dirit;
	}
}

bool validateProcess() {
	wchar_t pluginpath[MAX_PATH];

	GetModuleFileNameW(NULL, pluginpath, MAX_PATH);

	WCHAR szDrive[_MAX_DRIVE];
	WCHAR szDir[_MAX_DIR];
	WCHAR szFileName[_MAX_FNAME];
	WCHAR szExt[_MAX_EXT];
	WCHAR szOutput[_MAX_PATH * 5 + 1024];
	DWORD dwRet;

	//初期化
	memset(szDrive, 0x00, sizeof(szDrive));
	memset(szDir, 0x00, sizeof(szDir));
	memset(szExt, 0x00, sizeof(szExt));
	memset(szOutput, 0x00, sizeof(szOutput));
	dwRet = 0;

	_wsplitpath_s(pluginpath, szDrive, szDir, szFileName, szExt);

	if (wcscmp(szFileName, L"eu4") == 0 && wcscmp(szExt, L".exe") == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Initialize(HMODULE hSelf)
{
	wchar_t pluginpath[MAX_PATH];

	GetModuleFileNameW(hSelf, pluginpath, MAX_PATH);

	const path pluginsPath = path{ pluginpath }.parent_path() / L"plugins";

	#ifndef _DEBUG
	if (!InitAutoUpdate(pluginsPath)) {
		//　アラートを出すのみで終了はしないことにした
	}
	#endif // DEBUG時は自動更新しない

	initInjector();

	LoadScripts(pluginsPath);
}


BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		if (validateProcess())
		{
			Initialize(module);
		}
		else {
			initInjector();
		}
	}

	return TRUE;
}