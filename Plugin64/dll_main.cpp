// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ulReasonForCall,
                      LPVOID lpReserved){

	if (ulReasonForCall == DLL_PROCESS_ATTACH){
		DllError e = {};

		BytePattern::StartLog(L"eu4_jps_2");

		// 設定
		RunOptions options;
		options.version = Version::GetVersion();

		// debug
		e |= Debug::Init(options);

		// font
		//e |= Font::Init(options);

		// main text
		//e |= MainText::Init(options);

		// tooltip and button
		//e |= TooltipAndButton::Init(options);

		// map view
		//e |= MapView::Init(options);

		if (e.unmatch.code2 > 0) {
			exit(1);
		}
		else {
			BytePattern::LoggingInfo("DLL [OK]");
		}
	}else if (ulReasonForCall == DLL_PROCESS_DETACH){
		BytePattern::ShutdownLog();
	}

    return TRUE;
}

