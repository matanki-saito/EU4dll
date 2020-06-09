// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include "plugin_64.h"
#include "mod_download.h"

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ulReasonForCall,
                      LPVOID lpReserved){

	if (ulReasonForCall == DLL_PROCESS_ATTACH){
		BytePattern::StartLog(L"eu4_jps_2");

		DllError e = {};

		// mod download
		#ifndef _DEBUG
		e |= ModDownload::Init();
		#endif

		// 設定
		RunOptions options;

		// Version取得
		Version::GetVersionFromExe(&options);
		// INIから取得
		Ini::GetOptionsFromIni(&options);

		// デバッグ用
		#ifdef _DEBUG
		e |= Debug::Init(options);
		#endif

		// フォント読み込み
		e |= Font::Init(options);

		// UIの表示
		e |= MainText::Init(options);

		// ツールチップとボタンの表示
		e |= TooltipAndButton::Init(options);

		// マップ文字の表示
		e |= MapView::Init(options);

		// マップ文字の表示（nudge）
		e |= MapNudgeView::Init(options);

		// マップ文字の調整
		e |= MapAdjustment::Init(options);

		// マップ文字の調整
		//e |= MapJustify::Init(options);

		// イベントダイアログとマップ文字の調整
		//e |= EventDialog::Init(options);

		// マップ上に浮き出る文字の表示
		//e |= MapPopup::Init(options);

		// リスト表示の文字の調整
		//e |= ListFieldAdjustment::Init(options);

		// ファイルセーブ
		//e |= FileSave::Init(options);

		// 日付
		//e |= Date::Init(options);

		// IME
		//e |= Ime::Init(options);

		// 入力
		//e |= Input::Init(options);

		// 文字列順序入れ替え
		//e |= WordOrder::Init(options);

		Validator::Validate(e,options);
	}else if (ulReasonForCall == DLL_PROCESS_DETACH){
		BytePattern::ShutdownLog();
	}

    return TRUE;
}

