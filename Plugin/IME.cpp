#include "stdinc.h"
#include "byte_pattern.h"

namespace IME {

	/*-----------------------------------------------*/

	uintptr_t SDL_windowsevents_v125_end;
	uintptr_t SDL_windowsevents_v125_end2;
	__declspec(naked) void SDL_windowsevents_v125_start()
	{
		__asm {
			add esp, 0x14;
			test eax, eax;
			jnz ee_8;

			push SDL_windowsevents_v125_end;
			ret;

		ee_8:
			mov ecx, [ebp + 0x0C];
			mov ebx, [ebp + 0x10]; //hDrop

			push SDL_windowsevents_v125_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowsevents_hook(EU4Version version) {
		std::string desc = "SDL_windowsevents";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
		case v1_26_X:
		case v1_25_X:
			byte_pattern::temp_instance().find_pattern("83 C4 14 85 C0 0F 85 BF");
			if (byte_pattern::temp_instance().has_size(1, desc + " start")) {
				// add esp,0x14
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), SDL_windowsevents_v125_start);
				// mov ecx, [ebp + cch]
				SDL_windowsevents_v125_end = byte_pattern::temp_instance().get_first().address(0xB);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("FF 75 14 53 51 FF 75 08 FF 35");
			if (byte_pattern::temp_instance().has_size(1, desc + " end2")) {
				// push [ebp+hRawInput]; lParam
				SDL_windowsevents_v125_end2 = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	uintptr_t SDL_windowskeyboard_end;
	uintptr_t SDL_SetTextInputRect;
	uintptr_t SDL_windowskeyboard_end2;
	__declspec(naked) void SDL_windowskeyboard_start()
	{
		__asm {
			jz ee_2;

			push SDL_windowskeyboard_end;
			ret;

		ee_2:
			sub     esp, 8;
			mov     ecx, [ebp + 0x18];
			mov     edx, [ebp + 0x8];
			mov[ecx + 0x38], edx;
			mov     dword ptr[ebp - 0x14], 0;
			mov     dword ptr[ebp - 0x10], 0;
			lea     eax, [ebp - 0x14];
			push    eax;
			call    SDL_SetTextInputRect;
			add     esp, 0xC;

			push     SDL_windowskeyboard_end2;
			ret;
		}
	}

	/*-----------------------------------------------*/

	errno_t SDL_windowskeyboard_hook(EU4Version version) {
		std::string desc = "SDL_windowskeyboard";

		switch (version) {
		case v1_28_3:
		case v1_28_X:
		case v1_27_X:
		case v1_26_X:
		case v1_25_X:
			// WM_IME_STARTCOMPOSITION
			byte_pattern::temp_instance().find_pattern("0F 84 FA 01 00 00 83 E8");
			if (byte_pattern::temp_instance().has_size(1,desc + " start")) {
				// sub eax, 0xBC
				injector::MakeJMP(byte_pattern::temp_instance().get_first().address(), SDL_windowskeyboard_start);
				SDL_windowskeyboard_end = byte_pattern::temp_instance().get_first().address(0x6);
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("55 8B EC A1 ? ? ? ? 85 C0 74 13 8B");
			if (byte_pattern::temp_instance().has_size(1, desc + " SDL_SetTextInputRect")) {
				// push ebp
				SDL_SetTextInputRect = byte_pattern::temp_instance().get_first().address();
			}
			else return EU4_ERROR1;

			byte_pattern::temp_instance().find_pattern("5F BB 01 00 00 00 5E 8B");
			if (byte_pattern::temp_instance().has_size(2, desc + " end2")) {
				// pop edi
				SDL_windowskeyboard_end2 = byte_pattern::temp_instance().get(1).address();
			}
			else return EU4_ERROR1;

			// WM_IME_COMPOSITION
			byte_pattern::temp_instance().find_pattern("68 00 08 00 00 57");
			if (byte_pattern::temp_instance().has_size(1, desc + "skip code 1")) {
				// push 800h
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0x2), 0xEB, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(-0x1), 0x41, true);
			}
			else return EU4_ERROR1;

			// WM_IME_SETCONTEXT
			byte_pattern::temp_instance().find_pattern("8B 4D 14 89 19");
			if (byte_pattern::temp_instance().has_size(1, desc + "skip code 2")) {
				// mov ecx, [ebp+arg_C]
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x0), 0x90, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x1), 0x90, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x2), 0x90, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x3), 0x90, true);
				injector::WriteMemory<uint8_t>(byte_pattern::temp_instance().get_first().address(0x4), 0x90, true);
			}
			else return EU4_ERROR1;
			return NOERROR;
		}

		return EU4_ERROR1;
	}

	/*-----------------------------------------------*/

	errno_t init(EU4Version version) {
		errno_t result = 0;

		byte_pattern::temp_instance().debug_output2("IME fix");

		/* SDL_windowsevents.cの調整 */
		result |= SDL_windowsevents_hook(version);

		/* SDL_windowskeyboard.cの調整 */
		result |= SDL_windowskeyboard_hook(version);

		return result;
	}
}