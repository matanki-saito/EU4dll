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

		//MapAdj::init(version);
		//MapJustify::init(version);
		//MapView::init(version);
		//Misc::init(version);

		if (success == NOERROR) {
			byte_pattern::temp_instance().debug_output2("DLL [OK]");
		}
		else {
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
