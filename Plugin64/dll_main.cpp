// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ulReasonForCall,
                      LPVOID lpReserved){

	if (ulReasonForCall == DLL_PROCESS_ATTACH){
		BytePattern::start_log(L"eu4_jps_2");

		// 設定
		RunOptions options;
		options.version = Version::GetVersion();

		// debug
		Debug::Init(options);

		BytePattern::temp_instance().debug_output2("DLL [OK]");

	}else if (ulReasonForCall == DLL_PROCESS_DETACH){
		BytePattern::shutdown_log();
	}

    return TRUE;
}

