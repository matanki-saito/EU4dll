#include "stdinc.h"
#include "byte_pattern.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
		byte_pattern::start_log(L"eu4jps");

		// versionを文字列から取得
		EU4Version version = Misc::getVersion();

		// オプションをiniファイルから取得
		RunOptions options = RunOptions();
		Misc::getOptionsByINI(&options);
		
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

		// 入力修正
		success |= Input::init(version);

		// IME修正
		success |= IME::init(version);

		// ツールチップとボタン
		success |= ButtonAndToolTip::init(version);

		// ツールチップ追加処理
		success |= ToolTipApx::init(version);

		// マップ上のポップアップ文字
		success |= PopupCharOnMap::init(version);

		// issue-19の修正
		success |= InputIssue19::init(version);

		// イベントダイアログの修正とマップ上の修正
		success |= EventDialog::init(version);

		// ファイルセーブ関連
		success |= FileSave::init(version);

		// DateFormat(issue-66)の修正
		success |= DateFormat::init(version);

		// Listの文字調整（issue-99）
		success |= ListChars::init(version);

		// 名前の順序(issue-98)
		success |= NameOrder::init(version);

		if (success == NOERROR && options.test == false) {
			//MessageBoxW(NULL, L"[OK]", L"Multibyte DLL", MB_OK);
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
//			const DWORD sysDefLcid = ::GetSystemDefaultLCID();
//			if (sysDefLcid == 1041) {
//				MessageBoxW(NULL, L"--> Go to https://paradoxian-japan-mod.com/ <--", L"Error", MB_OK);
//			}
//			else {
				MessageBoxW(NULL, L"[Multibyte DLL ERROR]\nThis game version is not supported by Multibyte DLL.\nPlease delete d3d9.dll and restart game.\nOr check new version dll.\n\nhttps://github.com/matanki-saito/EU4dll", L"Multibyte DLL", MB_OK);
//			}

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
