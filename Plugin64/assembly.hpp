/*
 *  Injectors - Useful Assembly Stuff
 *
 *  Copyright (C) 2012-2014 LINK/2012 <dma_2012@hotmail.com>
 *
 *  This software is provided 'as-is', without any express or implied
 *  warranty. In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *     1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *
 *     2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *
 *     3. This notice may not be removed or altered from any source
 *     distribution.
 *
 */
#pragma once

 // This header is very restrict about compiler and architecture
#ifndef _MSC_VER    // MSVC is much more flexible when we're talking about inline assembly
#error  Cannot use this header in another compiler other than MSVC
#endif
#ifndef _M_X64
#error  "Supported only in x64"
#endif

#include "pch.h"

extern "C" {
	void inline_make_reg_pack_and_call();
}

namespace Injector
{
	//helpers
	union general_register
	{
		uint64_t i;
		void* p;

		template <typename T>
		operator T* () const
		{
			return (T*)p;
		}
	};

	// http://www.zombie-hunting-club.com/entry/2017/10/15/220724?amp=1#4-%E3%83%95%E3%83%A9%E3%82%B0%E3%83%AC%E3%82%B8%E3%82%B9%E3%82%BF
	struct flags_register
	{
		bool carry_flag : 1;
		bool flag1 : 1;
		bool parity_flag : 1;
		bool flag3 : 1;
		bool adjust_flag : 1;
		bool flag5 : 1;
		bool zero_flag : 1;
		bool sign_flag : 1;
		bool flag8 : 1;
		bool flag9 : 1;
		bool direction_flag : 1;
		bool overflow_flag : 1;
		bool flag12 : 1;
		bool flag13 : 1;
		bool flag14 : 1;
		bool flag15 : 1;
		bool flag16 : 1;
		bool flag17 : 1;
		bool flag18 : 1;
		bool flag19 : 1;
		bool flag20 : 1;
		bool flag21 : 1;
		bool flag22 : 1;
		bool flag23 : 1;
		bool flag24 : 1;
		bool flag25 : 1;
		bool flag26 : 1;
		bool flag27 : 1;
		bool flag28 : 1;
		bool flag29 : 1;
		bool flag30 : 1;
		bool flag31 : 1;
		bool flag32 : 1;
		bool flag33 : 1;
		bool flag34 : 1;
		bool flag35 : 1;
		bool flag36 : 1;
		bool flag37 : 1;
		bool flag38 : 1;
		bool flag39 : 1;
		bool flag40 : 1;
		bool flag41 : 1;
		bool flag42 : 1;
		bool flag43 : 1;
		bool flag44 : 1;
		bool flag45 : 1;
		bool flag46 : 1;
		bool flag47 : 1;
		bool flag48 : 1;
		bool flag49 : 1;
		bool flag50 : 1;
		bool flag51 : 1;
		bool flag52 : 1;
		bool flag53 : 1;
		bool flag54 : 1;
		bool flag55 : 1;
		bool flag56 : 1;
		bool flag57 : 1;
		bool flag58 : 1;
		bool flag59 : 1;
		bool flag60 : 1;
		bool flag61 : 1;
		bool flag62 : 1;
		bool flag63 : 1;
	};
	static_assert(sizeof(general_register) == 8, "Type size error.");
	static_assert(sizeof(flags_register) == 8, "Type size error.");


	struct reg_pack
	{
		// TODO: これはないのでどうするか考える
		// http://left404.com/2011/01/04/moving-x86-assembly-to-64-bit-x86-64/

		// The ordering is very important, don't change
		// The first field is the last to be pushed and first to be poped

		// PUSHAD/POPAD -- must be the lastest fields (because of esp)
		union
		{
			general_register arr[16];
			struct {
				general_register
					rdi, rsi, rbp, rsp, rbx, rdx, rcx, rax,
					r8, r9, r10, r11, r12, r13, r14, r15;
			};
		};
		// PUSHFQをつかう
		// https://www.felixcloutier.com/x86/pushf:pushfd:pushfq
		// PUSHFD / POPFD
		flags_register ef;
	};

	// Lowest level stuff (actual assembly) goes on the following namespace
	// PRIVATE! Skip this, not interesting for you.
	namespace injector_asm
	{
		// Wrapper functor, so the assembly can use some templating
		template<class T>
		struct wrapper
		{
			static void call(reg_pack* regs)
			{
				T fun;
				fun(*regs);
			}
		};

		// Constructs a reg_pack and calls the wrapper functor
		template<class W>   // where W is of type wrapper
		void w_make_reg_pack_and_call()
		{
			// dummy code
			printf("dummy1");
			printf("dummy2");
		}
	};

	typedef struct {
		BYTE binary[25];
	} INJECT_ASM;

	typedef struct {
		BYTE binary[20];
	} INJECT_ASM2;

	/*
	 *  MakeInline
	 *      Makes inline assembly (but not assembly, an actual functor of type FuncT) at address
	 *      assembly ref: https://defuse.ca/online-x86-assembler.htm#disassembly
	 */
	template<class FuncT>
	void MakeInline(memory_pointer_tr at)
	{
		typedef injector_asm::wrapper<FuncT> functor;
		if (false) functor::call(nullptr);   // To instantiate the template, if not done _asm will fail

		memory_pointer_raw funcAddress = functor::call;
		memory_pointer_raw injectorAddress = injector_asm::w_make_reg_pack_and_call<functor>;
		memory_pointer_raw jmpAddress = GetBranchDestination(injectorAddress);

		auto cursor = WriteMemory<INJECT_ASM>(jmpAddress, { {
				0x9c, // pushrq
				0x41, 0x57, // push r15
				0x41, 0x56, // push r14
				0x41, 0x55, // push r13
				0x41, 0x54, // push r12
				0x41, 0x53, // push r11
				0x41, 0x52, // push r10
				0x41, 0x51, // push r9
				0x41, 0x50, // push r8
				0x50, // push rax
				0x51, // push rcx
				0x52, // push rdx
				0x53, // push rbx
				0x54, // push rsp
				0x55, // push rbp
				0x56, // push rsi
				0x57, // push rdi
			} }, true
			);

		// mov rcx, rsp
		cursor = WriteMemory<char>(cursor, 0x48, true);
		cursor = WriteMemory<char>(cursor, 0x89, true);
		cursor = WriteMemory<char>(cursor, 0xE1, true);

		// push rsp
		cursor = WriteMemory<char>(cursor, 0x54, true);

		cursor = MakeCALL2(cursor, funcAddress);

		// add rsp,8
		cursor = WriteMemory<char>(cursor, 0x48, true);
		cursor = WriteMemory<char>(cursor, 0x83, true);
		cursor = WriteMemory<char>(cursor, 0xC4, true);
		cursor = WriteMemory<char>(cursor, 0x08, true);

		cursor = WriteMemory<INJECT_ASM>(cursor, { {
				0x5f, // pop rdi
				0x5e, // pop rsi
				0x5d, // pop rbp
				0x5c, // pop rsp
				0x5b, // pop rbx
				0x5a, // pop rdx
				0x59, // pop rcx
				0x58, // pop rax
				0x41, 0x58, // pop r8
				0x41, 0x59, // pop r9
				0x41, 0x5A, // pop r10
				0x41, 0x5B, // pop r11
				0x41, 0x5C, // pop r12
				0x41, 0x5D, // pop r13
				0x41, 0x5E, // pop r14
				0x41, 0x5F, // pop r15
				0x9d, // popfq
			} }, true
			);

		//xchg rax, [rsp];
		//add rax, 8;
		//xchg[rsp], rax;
		cursor = WriteMemory<INJECT_ASM2>(cursor, { {
				0x48,0x87,0x84,0x24,0x00,0x00,0x00, // xchg   QWORD PTR [rsp+0x0],rax
				0x00,
				0x48,0x83,0xC0,0x08, // add    rax,0x8
				0x48,0x87,0x84,0x24,0x00,0x00,0x00, // xchg   QWORD PTR [rsp+0x0],rax
				0x00
		} }, true);

		// ret
		cursor = WriteMemory<char>(cursor, 0xc3, true);

		MakeCALL(at, injectorAddress);
	}

	/*
	 *  MakeInline
	 *      Same as above, but it NOPs everything between at and end (exclusive), then performs MakeInline
	 */
	template<class FuncT>
	void MakeInline(memory_pointer_tr at, memory_pointer_tr end)
	{
		MakeRangedNOP(at, end);
		MakeInline<FuncT>(at);
	}

	/*
	 *  MakeInline
	 *      Same as above, but (at,end) are template parameters.
	 *      On this case the functor can be passed as argument since there will be one func instance for each at,end not just for each FuncT
	 */
	template<uintptr_t at, uintptr_t end, class FuncT>
	void MakeInline(FuncT func)
	{
		static std::unique_ptr<FuncT> static_func;
		static_func.reset(new FuncT(std::move(func)));

		// Encapsulates the call to static_func
		struct Caps
		{
			void operator()(reg_pack& regs)
			{
				(*static_func)(regs);
			}
		};

		// Does the actual MakeInline
		return MakeInline<Caps>(lazy_pointer<at>::get(), lazy_pointer<end>::get());
	}

	/*
	 *  MakeInline
	 *      Same as above, but (end) is calculated by the length of a call instruction
	 */
	template<uintptr_t at, class FuncT>
	void MakeInline(FuncT func)
	{
		return MakeInline<at, at + 5, FuncT>(func);
	}
};
