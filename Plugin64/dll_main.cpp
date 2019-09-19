// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ulReasonForCall,
                      LPVOID lpReserved){

	if (ulReasonForCall == DLL_PROCESS_ATTACH){
		BytePattern::StartLog(L"eu4_jps_2");

		// 設定
		RunOptions options;
		options.version = Version::GetVersion();

		// debug
		Debug::Init(options);

		// font
		Font::Init(options);

		BytePattern::LoggingInfo("DLL [OK]");

	}else if (ulReasonForCall == DLL_PROCESS_DETACH){
		BytePattern::ShutdownLog();
	}

    return TRUE;
}

