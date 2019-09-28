#include "auto_update.h"

bool createProcess(WCHAR* szCmd, DWORD flag) {
	wstring message = L""s;
	wstring title = L"DLL autoupdate failed"s;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, 0, sizeof(STARTUPINFO));
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);

	BOOL createProcessSuccess = CreateProcess(NULL, szCmd, NULL, NULL, FALSE, flag, NULL, NULL, &si, &pi);

	if (createProcessSuccess) {
		DWORD result = WaitForSingleObject(pi.hProcess, 40 * 1000);
		switch (result){
		case WAIT_FAILED:
			message = L"WAIT_FAILED";
			createProcessSuccess = false;
			break;
		case WAIT_TIMEOUT:
			message = L"WAIT_TIMEOUT";
			createProcessSuccess = false;
			break;
		default:
			break;
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else {
		message = L"Retry please."s;
	}

	if (!createProcessSuccess) {
		MessageBox(NULL,message.c_str() , title.c_str(), MB_OK);
		return false;
	}

	return true;
}

bool InitAutoUpdate(const path& pluginsPath)
{
	path batFilePath = path{ pluginsPath } / L"autoupdate64.bat";

	if (exists(batFilePath)) {
		return createProcess(
			_wcsdup(batFilePath.c_str()),
			CREATE_NO_WINDOW
		);
	}

	return true;
}