#include "pch.h"
#include "plugin_64.h"

// 1.28.3,1.29.3時点でSDLのversionは2.0.4 hg-10001:e12c38730512
namespace Ime {
	extern "C" {
		void imeProc1();
		void imeProc1V137();
		void imeProc2();
		void imeProc3();
		uintptr_t imeProc1ReturnAddress1;
		uintptr_t imeProc1ReturnAddress2;
		uintptr_t imeProc1CallAddress;
		uintptr_t imeProc2CallAddress;
		uintptr_t imeProc2ReturnAddress1;
		uintptr_t imeProc2ReturnAddress2;
		uintptr_t imeProc2ReturnAddress3;
		uintptr_t rectAddress;
		uintptr_t imeProc3ReturnAddress;
		uintptr_t imeProc3CallAddress1;
		uintptr_t imeProc3CallAddress2;
		uintptr_t imeProc3CallAddress3;
		uintptr_t imeProc3CallAddress4;
		uintptr_t imeProc3CallAddress5;
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
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
			// mov     edx, r13d
			BytePattern::temp_instance().find_pattern("41 8B D5 49 8B CC E8 ? ? ? ? 85 C0 0F 85");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowsevents.cの修正")) {
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
				e.ime.unmatchdImeProc1Injector = true;
			}
			break;
		case v1_35_1_0:
		case v1_36_0_0:
			// mov     edx, r13d
			BytePattern::temp_instance().find_pattern("41 8B D5 49 8B CC E8 ? ? ? ? 85 C0 0F 85 F1");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowsevents.cの修正")) {
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
				e.ime.unmatchdImeProc1Injector = true;
			}
			break;
		case v1_37_0_0:
			// mov     edx, edi
			BytePattern::temp_instance().find_pattern("8B D7 49 8B CC E8 ? ? ? ? 85 C0 0F 85 5B");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowsevents.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx}
				imeProc1CallAddress = Injector::GetBranchDestination(address + 0x5).as_int();

				//  cmp     edi, 0FFh
				imeProc1ReturnAddress1 = address + 0x12;

				// jz {xxxxx}
				imeProc1ReturnAddress2 = address - 0x3A;

				Injector::MakeJMP(address, imeProc1V137, true);
			}
			else {
				e.ime.unmatchdImeProc1Injector = true;
			}
			break;
		default:
			e.ime.versionImeProc1Injector = true;
		}

		return e;
	}

	// CompositionやCandidateが表示されるようにする
	// SDL_windowkeyboard.c#IME_HandleMessageにある処理を修正している
	// 以下のTwitterだと最初の`return SDL_FALSE`をキャンセルしているがwin32のコードから確認できなかった
	// https://twitter.com/matanki_saito/status/1006954448583704576
	// これはISSUE19の対応時に復活させていた
	// https://github.com/matanki-saito/EU4dll/issues/19#issuecomment-423940649
	DllError imeProc2Injector(RunOptions options) {
		DllError e = {};
		HMODULE handle = NULL;

		switch (options.version) {
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			rectAddress = (uintptr_t)&rect;

			// SDL_SetTextInputRectの関数を見つける
			BytePattern::temp_instance().find_pattern("48 8B D1 48 8B ? ? ? ? 00 48 85 C9 74 0F"); // mov     rdx, rcx
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				imeProc2CallAddress = BytePattern::temp_instance().get_first().address();
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_STARTCOMPOSITIONでSDL_SetTextInputRectする
			BytePattern::temp_instance().find_pattern("81 EA BC 00 00 00 0F 84 2B 02 00 00"); // sub     edx, 0BCh
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz {loc_xxxxx}
				imeProc2ReturnAddress1 = Injector::GetBranchDestination(address + 0x6).as_int();

				// jnz loc_xxxxx
				imeProc2ReturnAddress2 = address + 15;

				Injector::MakeJMP(address, imeProc2, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_SETCONTEXTで*lParam = 0;をコメントアウトする（nopで埋める）
			// mov     [r9], r15
			BytePattern::temp_instance().find_pattern("4D 89 39 48 8B 74 24 40");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<uint8_t>(address, 0x90, true);
				Injector::WriteMemory<uint8_t>(address+1, 0x90, true);
				Injector::WriteMemory<uint8_t>(address+2, 0x90, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_COMPOSITIONのif文のIME_GetCompositionStringとIME_SendInputEventをコメントアウト（jmpさせる）
			//  mov     r8d, 800h
			// 二つ目のif文もスキップさせる
			// https://github.com/matanki-saito/EU4dll/issues/19#issuecomment-423940364
			BytePattern::temp_instance().find_pattern("41 B8 00 08 00 00 48 8B D6 48 8B CF");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				// jz xxx -> jmp xxx
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<uint8_t>(address - 2, 0xEB, true);
				Injector::WriteMemory<uint8_t>(address - 1, 0x49, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}
			break;
		case v1_37_0_0:
			rectAddress = (uintptr_t)&rect;

			// SDL_SetTextInputRectの関数を見つける
			//  add     rsp, 20h
			handle = GetModuleHandle(NULL);
			imeProc2CallAddress = (uintptr_t)GetProcAddress(handle, "SDL_SetTextInputRect");

			if (imeProc2CallAddress == NULL) {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_STARTCOMPOSITIONでSDL_SetTextInputRectする
			BytePattern::temp_instance().find_pattern("81 EA BC 00 00 00 0F 84 C3 02 00 00"); // sub     edx, 0BCh
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// jz {loc_xxxxx}
				imeProc2ReturnAddress1 = Injector::GetBranchDestination(address + 0x6).as_int();

				// jnz loc_xxxxx
				imeProc2ReturnAddress2 = address + 0xF;

				Injector::MakeJMP(address, imeProc2, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_SETCONTEXTで*lParam = 0;をコメントアウトする（nopで埋める）
			// mov     [r9], r13
			BytePattern::temp_instance().find_pattern("4D 89 29 48 8B 5C 24 50");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();
				Injector::WriteMemory<uint8_t>(address, 0x90, true);
				Injector::WriteMemory<uint8_t>(address + 1, 0x90, true);
				Injector::WriteMemory<uint8_t>(address + 2, 0x90, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			// WM_IME_COMPOSITIONのif文のIME_GetCompositionStringとIME_SendInputEventをコメントアウト（jmpさせる）
			// mov     r8d, 800h
			// 二つ目のif文もスキップさせる
			// https://github.com/matanki-saito/EU4dll/issues/19#issuecomment-423940364
			BytePattern::temp_instance().find_pattern("41 B8 00 08 00 00 48 89 7C 24 58");
			if (BytePattern::temp_instance().has_size(1, u8"SDL_windowskeyboard.cの修正")) {
				// jnb     short loc_1417613D8
				uintptr_t address = BytePattern::temp_instance().get_first().address(-2);
				Injector::MakeJMP(address, address + 0x9D, true);
			}
			else {
				e.ime.unmatchdImeProc2Injector = true;
			}

			break;
		default:
			e.ime.unmatchdImeProc2Injector = true;
		}

		return e;
	}

	// コンポジション入力中のバックスペースや矢印キーのイベントをキャンセルする
	// WM_KEYDOWNのみの修正で、WM_KEYUPの修正は入れていない。おそらくそれでも問題ない
	// https://github.com/matanki-saito/EU4dll/issues/19
	DllError imeProc3Injector(RunOptions options) {
		DllError e = {};

		switch (options.version) {
		case v1_29_3_0:
		case v1_29_4_0:
		case v1_30_1_0:
		case v1_30_2_0:
		case v1_30_3_0:
		case v1_30_4_0:
		case v1_30_5_0:
		case v1_31_1_0:
		case v1_31_2_0:
		case v1_31_3_0:
		case v1_31_4_0:
		case v1_31_5_0:
		case v1_31_6_0:
		case v1_32_0_1:
		case v1_33_0_0:
		case v1_33_3_0:
		case v1_34_2_0:
		case v1_35_1_0:
		case v1_36_0_0:
			// 直前の部分でjmpに使う14byteを確保することができなかった。
			// そのためWM_KEYDOWNのコードをすべて移植した
			// mov     rcx, [rbp+0C0h+hRawInput]
			BytePattern::temp_instance().find_pattern("48 8B 8D E8 ? ? ? ? 8B D6 E8 ? ? ? ? 33");
			if (BytePattern::temp_instance().has_size(2, u8"SDL_windowsevents.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx} / WindowsScanCodeToSDLScanCode
				imeProc3CallAddress1 = Injector::GetBranchDestination(address + 0xA).as_int();

				// call {sub_xxxxx} / SDL_GetKeyboardState
				imeProc3CallAddress2 = Injector::GetBranchDestination(address + 0x13).as_int();

				// call {sub_xxxxx} / ShouldGenerateWindowCloseOnAltF4
				imeProc3CallAddress3 = Injector::GetBranchDestination(address + 0x36).as_int();

				// call {sub_xxxxx} / SDL_SendWindowEvent
				imeProc3CallAddress4 = Injector::GetBranchDestination(address + 0x50).as_int();

				// call {sub_xxxxx} / SDL_SendKeyboardKey
				imeProc3CallAddress5 = Injector::GetBranchDestination(address + 0x61).as_int();

				// xor     edi, edi
				imeProc3ReturnAddress = address + 0x66;

				Injector::MakeJMP(address, imeProc3, true);
			}
			else {
				e.ime.unmatchdImeProc3Injector = true;
			}
			break;
		case v1_37_0_0:
			// 直前の部分でjmpに使う14byteを確保することができなかった。
			// そのためWM_KEYDOWNのコードをすべて移植した
			// mov     rcx, [rbp+0C0h+hRawInput]
			BytePattern::temp_instance().find_pattern("48 8B 8D E8 ? ? ? ? 8B D6 E8 ? ? ? ? 33");
			if (BytePattern::temp_instance().has_size(2, u8"SDL_windowsevents.cの修正")) {
				uintptr_t address = BytePattern::temp_instance().get_first().address();

				// call {sub_xxxxx} / WindowsScanCodeToSDLScanCode
				imeProc3CallAddress1 = Injector::GetBranchDestination(address + 0xA).as_int();

				// call {sub_xxxxx} / SDL_GetKeyboardState
				imeProc3CallAddress2 = Injector::GetBranchDestination(address + 0x13).as_int();

				// call {sub_xxxxx} / ShouldGenerateWindowCloseOnAltF4
				imeProc3CallAddress3 = Injector::GetBranchDestination(address + 0x36).as_int();

				// call {sub_xxxxx} / SDL_SendWindowEvent
				imeProc3CallAddress4 = Injector::GetBranchDestination(address + 0x50).as_int();

				// call {sub_xxxxx} / SDL_SendKeyboardKey
				imeProc3CallAddress5 = Injector::GetBranchDestination(address + 0x61).as_int();

				// xor     edi, edi
				imeProc3ReturnAddress = address + 0x66;

				Injector::MakeJMP(address, imeProc3, true);
			}
			else {
				e.ime.unmatchdImeProc3Injector = true;
			}
			break;
		default:
			e.ime.versionImeProc3Injector = true;
		}

		return e;
	}

	DllError Init(RunOptions options) {
		DllError result = {};

		result |= imeProc1Injector(options);
		result |= imeProc2Injector(options);
		//result |= imeProc3Injector(options);

		return result;
	}
}