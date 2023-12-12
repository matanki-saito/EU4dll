#include "pch.h"
#include "mod_download.h"

namespace ModDownload{

	DllError createProcess(WCHAR* szCmd, DWORD flag) {
		DllError error = {};

		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		memset(&si, 0, sizeof(STARTUPINFO));
		memset(&pi, 0, sizeof(PROCESS_INFORMATION));
		si.cb = sizeof(STARTUPINFO);

		BOOL createProcessSuccess = CreateProcess(NULL, szCmd, NULL, NULL, FALSE, flag, NULL, NULL, &si, &pi);

		if (!createProcessSuccess) {
			error.mod.proccessFaild = true;
		}
		else {
			DWORD result = WaitForSingleObject(pi.hProcess, 20 * 1000); // 20 sec
			switch (result)
			{
			case WAIT_FAILED:
				/* error.mod.waitFailed = true; */
				/* skip */
				break;
			case WAIT_TIMEOUT:
				error.mod.timeout = true;
				break;
			default:
				break;
			}
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}

		return error;
	}

	DllError Init() {
		DllError error = {};

		wchar_t myDocumentPath[MAX_PATH];
		SHGetSpecialFolderPath(NULL, myDocumentPath, CSIDL_PERSONAL | CSIDL_FLAG_NO_ALIAS, 0);

		// steam
		const path gameDirPathSteam = path{ myDocumentPath } / L"Paradox Interactive" / L"Europa Universalis IV";
		path downloaderExePathSteam = path{ gameDirPathSteam } / L"claes.exe";

		if (exists(downloaderExePathSteam)) {
			error |= createProcess(
				_wcsdup(downloaderExePathSteam.c_str()),
				CREATE_NO_WINDOW
			);
		}

		// epic
		const path gameDirPathEpic = path{ myDocumentPath } / L"Paradox Interactive" / L"Europa Universalis IV EGS";
		path downloaderExePathEpic = path{ gameDirPathEpic } / L"claes.exe";

		if (exists(downloaderExePathEpic)) {
			error |= createProcess(
				_wcsdup(downloaderExePathEpic.c_str()),
				CREATE_NO_WINDOW
			);
		}

		return error;
	}

}