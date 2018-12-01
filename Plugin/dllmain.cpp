#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
		byte_pattern::start_log(L"eu4jps");

		// versionを文字列から取得
		EU4Version version = Misc::getVersion();
		
		errno_t success = NOERROR;

		// フォント関連の修正
		success |= Font::init(version);

		// 本文テキスト表示の修正
		success |= TextView::init(version);

		// マップ文字位置調整
		success |= MapAdj::init(version);

		// マップ文字justify
		success |= MapJustify::init(version);

		// マップ文字表示
		success |= MapView::init(version);

		// その他
		success |= Misc::init(version);

		//入力修正
		success |= Input::init(version);

		//IME修正
		success |= IME::init(version);

		//ツールチップとボタン
		success |= ButtonAndToolTip::init(version);

		//ツールチップ追加処理
		success |= ToolTipApx::init(version);

		//マップ上のポップアップ文字
		success |= PopupCharOnMap::init(version);

		// issue19の修正
		success |= InputIssue19::init(version);

		// イベントダイアログの修正とマップ上の修正
		success |= EventDialog::init(version);

		// ファイルセーブ関連
		success |= FileSave::init(version);

		// issue66の修正
		success |= Issue66::init(version);

		if (success == NOERROR) {
			//MessageBoxW(NULL, L"[OK]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			MessageBoxW(NULL, L"[NG]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [NG]");
			exit(-1);
		}
    }
    else if (reason == DLL_PROCESS_DETACH)
    {
        byte_pattern::shutdown_log();
    }

    return TRUE;
}
