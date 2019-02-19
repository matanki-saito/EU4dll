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
					"このバージョンはまだ日本語化対応していません\n"
					"d3d9.dllを削除してゲームを再起動してください。\n"
					"\n"
					"プロジェクトページ：\n"
					"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_CHINESE_SIMPLIFIED, SUBLANG_CHINESE_SIMPLIFIED):
				caption = L"错误";
				message = L""
					"此版本尚不支持\n"
					"请删除d3d9.dll并重启游戏\n"
					"\n"
					"项目页面:\n"
					"https://github.com/matanki-saito/EU4dll";
				break;


			case MAKELANGID(LANG_CHINESE_TRADITIONAL, SUBLANG_CHINESE_TRADITIONAL):
				caption = L"錯誤";
				message = L""
					"此版本尚不支持\n"
					"請刪除d3d9.dll並重啟遊戲\n"
					"\n"
					"項目頁面:\n"
					"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_KOREAN, SUBLANG_KOREAN):
				caption = L"오류";
				message = L""
					"이 버전은 아직 지원하지 않습니다.\n"
					"d3d9.dll을 삭제하고 게임을 다시 시작하십시오. \n"
					"\n"
					"프로젝트 페이지\n"
					"https://github.com/matanki-saito/EU4dll";
				break;

			case MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US):
			default:
				caption = L"ERROR";
				message = L""
					"This game version is not supported.\n"
					"Please delete d3d9.dll and restart game.\n"
					"\n"
					"Project Page:\n"
					"https://github.com/matanki-saito/EU4dll";
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
