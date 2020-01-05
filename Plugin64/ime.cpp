#include "pch.h"
#include "plugin_64.h"

// 1.28.3,1.29.3時点でSDLのversionは2.0.4 hg-10001:e12c38730512
namespace Ime {
	extern "C" {
		void imeProc1();
		void imeProc2();
		uintptr_t imeProc1ReturnAddress1;
		uintptr_t imeProc1ReturnAddress2;
		uintptr_t imeProc1CallAddress;
		uintptr_t imeProc2CallAddress;
		uintptr_t imeProc2ReturnAddress1;
		uintptr_t imeProc2ReturnAddress2;
		uintptr_t rectAddress;
	}

	typedef struct SDL_Rect
	{
		int x, y;
		int w, h;
	} SDL_Rect;

	SDL_Rect rect = { 0,0,0,0 };

	// CompositionやCandidateが表示されるようにする
	// SDL_windowsevents.c#WIN_WindowProcでIME_HandleMessageのif文で`return 0`するのが問題なので、
	// 関数の一番下にある` if (data->wndproc)`までつなげる
	// https://twitter.com/matanki_saito/status/1006954440736235521
	DllError imeProc1Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0:
			// mov     edx, r13d
			BytePattern::temp_instance().find_pattern("41 8B D5 49 8B CC E8 ? ? ? ? 85 C0 0F 85");
			if (BytePattern::temp_instance().has_size(1, "SDL_windowsevents.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				imeProc1CallAddress = Injector::GetBranchDestination(address + 0x6).as_int();

				// cmp     r13d, 0FFh
				imeProc1ReturnAddress1 = address + 0x13;

				// jz {xxxxx}
				imeProc1ReturnAddress2 = Injector::GetBranchDestination(address - 0x19).as_int();

				Injector::MakeJMP(address, imeProc1, true);
			}
			else {
				e.unmatch.imeProc1Injector = true;
			}
			break;
		default:
			e.version.imeProc1Injector = true;
		}

		return e;
	}

	// CompositionやCandidateが表示されるようにする
	// SDL_windowkeyboard.c#IME_HandleMessageにある処理を修正している
	// 以下のTwitterだと最初の`return SDL_FALSE`をキャンセルしているがwin32のコードから確認できなかったのでいらない？
	// https://twitter.com/matanki_saito/status/1006954448583704576
	DllError imeProc2Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0: 
			rectAddress = (uintptr_t)&rect;

			// SDL_SetTextInputRectの関数を見つける
			BytePattern::temp_instance().find_pattern("48 8B D1 48 8B ? ? ? ? 00 48 85 C9 74 0F"); // mov     rdx, rcx
			if (BytePattern::temp_instance().has_size(1, "SDL_windowskeyboard.cの修正")) {
				imeProc2CallAddress = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.unmatch.imeProc2Injector = true;
			}

			// WM_IME_STARTCOMPOSITIONでSDL_SetTextInputRectする
			BytePattern::temp_instance().find_pattern("81 EA BC 00 00 00 0F 84 2B 02 00 00"); // sub     edx, 0BCh
			if (BytePattern::temp_instance().has_size(1, "SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz {loc_xxxxx}
				imeProc2ReturnAddress1 = Injector::GetBranchDestination(address + 0x6).as_int();

				// jnz loc_xxxxx
				imeProc2ReturnAddress2 = address + 15;

				Injector::MakeJMP(address, imeProc2, true);
			}
			else {
				e.unmatch.imeProc2Injector = true;
			}

			// WM_IME_SETCONTEXTで*lParam = 0;をコメントアウトする（nopで埋める）
			// mov     [r9], r15
			BytePattern::temp_instance().find_pattern("4D 89 39 48 8B 74 24 40");
			if (BytePattern::temp_instance().has_size(1, "SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<uint8_t>(address, 0x90, true);
				Injector::WriteMemory<uint8_t>(address+1, 0x90, true);
				Injector::WriteMemory<uint8_t>(address+2, 0x90, true);
			}
			else {
				e.unmatch.imeProc2Injector = true;
			}

			// WM_IME_COMPOSITIONのif文のIME_GetCompositionStringとIME_SendInputEventをコメントアウト（jmpさせる）
			//  mov     r8d, 800h
			BytePattern::temp_instance().find_pattern("41 B8 00 08 00 00 48 8B D6 48 8B CF");
			if (BytePattern::temp_instance().has_size(1, "SDL_windowskeyboard.cの修正")) {
				// jz xxx -> jmp xxx
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<uint8_t>(address - 2, 0xEB, true);
				Injector::WriteMemory<uint8_t>(address - 1, 0x49, true);
			}
			else {
				e.unmatch.imeProc2Injector = true;
			}
			break;
		default:
			e.version.imeProc2Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= imeProc1Injector(options);
		result |= imeProc2Injector(options);

		return result;
	}
}