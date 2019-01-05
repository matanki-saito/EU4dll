#include "filedl.h"

void createProcess(WCHAR* szCmd, DWORD flag, BOOL fWait) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(STARTUPINFO));
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, flag, NULL, NULL, &si, &pi);
	if (fWait) WaitForSingleObject(pi.hProcess, INFINITE);	//èIóπÇë“Ç¬.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

int InitAutoUpdate(const path &pluginsPath)
{
	path batFilePath = path{ pluginsPath } / L"autoupdate.bat";

	if (std::experimental::filesystem::exists(batFilePath)) {
		createProcess(
			wcsdup(batFilePath.c_str()),
			CREATE_NO_WINDOW,
			true
		);
	}

	return 1;
}
