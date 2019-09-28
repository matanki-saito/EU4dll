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

void Initialize(HMODULE hSelf)
{
	wchar_t pluginpath[MAX_PATH];

	GetModuleFileNameW(hSelf, pluginpath, MAX_PATH);

	const path pluginsPath = path{ pluginpath }.parent_path() / L"plugins";

	if (!InitAutoUpdate(pluginsPath)) {
		exit(-1);
	}

	initInjector();

	LoadScripts(pluginsPath);
}


BOOL WINAPI DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Initialize(module);
	}

	return TRUE;
}