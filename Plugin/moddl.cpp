#include "moddl.h"

bool createProcess(WCHAR* szCmd, DWORD flag) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	WCHAR *message = L"Autoupdate error. Please DELETE 'claes.exe'.";
	WCHAR *title = NULL;

	memset(&si, 0, sizeof(STARTUPINFO));
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);

	BOOL createProcessSuccess = CreateProcess(NULL, szCmd, NULL, NULL, FALSE, flag, NULL, NULL, &si, &pi);

	if (!createProcessSuccess) {
		title = L"Autoupdate createProcess failed.";
	}
	else {
		DWORD result = WaitForSingleObject(pi.hProcess, 35 * 1000); // 35 sec
		switch (result)
		{
		case WAIT_FAILED:
			title = L"moddownload wait failed.";
			break;
		case WAIT_TIMEOUT:
			title = L"moddownload wait timeout.";
			break;
		default:
			break;
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (title != NULL) {
			MessageBox(NULL, message, title, MB_OK);
			return false;
		}
	}

	return true;
}

bool InitAutoUpdate(const path &pluginsPath)
{
	path exeFilePath = path{ pluginsPath } / L"claes.exe";

	if (exists(exeFilePath)) {
		return createProcess(
			_wcsdup(exeFilePath.c_str()),
			CREATE_NO_WINDOW
		);
	}

	return true;
}