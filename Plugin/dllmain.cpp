#include "stdinc.h"
#include "byte_pattern.h"
#include "moddl.h"

BOOL WINAPI DllMain(HMODULE module, DWORD reason, void *reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
		// moddownload
		wchar_t myDocumentPath[MAX_PATH];
		SHGetSpecialFolderPath(NULL, myDocumentPath, CSIDL_PERSONAL, 0);

		const path gameDirPath = path{ myDocumentPath } / L"Paradox Interactive" / L"Europa Universalis IV";
		if (!InitAutoUpdate(gameDirPath)) exit(-1);

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
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
			const DWORD sysDefLcid = ::GetSystemDefaultLCID();

			WCHAR* message;
			WCHAR* caption;

			switch (sysDefLcid) {
			case MAKELANGID(LANG_JAPANESE, SUBLANG_JAPANESE_JAPAN):
				caption = L"エラー";
				message = L""
					L"このバージョンはまだ日本語化に対応していないため起動できません。\n"
					L"将来、日本語化に対応した際には自動的に起動できるようになります。\n"
					L"\n"
					L"以前のバージョンに戻す方法は下記サイトをご覧ください。\n"
					L"https://paradoxian-japan-mod.com/version";
				break;

			case MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED):
				caption = L"错误";
				message = L""
					L"Multibyte DLL 尚未支持此游戏版本。\n"
					L"当我发布新的时，它会自动更新。\n"
					L"\n"
					L"DLL宣布页面:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;


			case MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_TRADITIONAL):
				caption = L"錯誤";
				message = L""
					L"Multibyte DLL 尚未支持此遊戲版本。\n"
					L"當我發布新的時，它會自動更新。\n"
					L"\n"
					L"DLL宣布頁面:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN):
				caption = L"오류";
				message = L""
					L"멀티 바이트 DLL은 아직이 게임 버전을 지원하지 않습니다.\n"
					L"새 게시물을 게시하면 자동으로 업데이트됩니다.\n"
					L"\n"
					L"DLL 공지 페이지:\n"
					L"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"ERROR";
				message = L""
					L"Multibyte DLL hasn't supported this game version yet.\n"
					L"It will be updated automatically, when I publish new one.\n"
					L"\n"
					L"DLL announce page:\n"
					L"https://github.com/matanki-saito/EU4dll";
			}

			MessageBoxW(NULL, message, caption, MB_OK);

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
