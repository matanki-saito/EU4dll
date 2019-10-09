//This is a very simplified version of Ultimate ASI Loader
//https://github.com/ThirteenAG/Ultimate-ASI-Loader

#include <windows.h>
#include <KnownFolders.h>
#include <filesystem>
#include <ShlObj.h>
#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")

#include "filedl.h"

using namespace std;
using namespace std::experimental::filesystem::v1;

struct
{
    HMODULE dll;
    FARPROC Direct3DCreate9;
    FARPROC Direct3DCreate9Ex;

    void LoadOriginalLibrary(HMODULE module)
    {
        dll = module;
        Direct3DCreate9 = GetProcAddress(module, "Direct3DCreate9");
        Direct3DCreate9Ex = GetProcAddress(module, "Direct3DCreate9Ex");
    }
} d3d9meta;

void InitD3D9()
{
    wchar_t *pd3d9path;
    path d3d9path;

    SHGetKnownFolderPath(FOLDERID_System, 0, NULL, &pd3d9path);
    d3d9path = path{ pd3d9path } / L"d3d9.dll";
    CoTaskMemFree(pd3d9path);

    d3d9meta.LoadOriginalLibrary(LoadLibraryW(d3d9path.c_str()));
}

void LoadScripts(const path &folder)
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

	#ifndef _DEBUG
	if (!InitAutoUpdate(pluginsPath)) exit(-1);
	#endif

    InitD3D9();

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


__declspec(naked) void _Direct3DCreate9() { _asm { jmp d3d9meta.Direct3DCreate9 } }
__declspec(naked) void _Direct3DCreate9Ex() { _asm { jmp d3d9meta.Direct3DCreate9Ex } }
