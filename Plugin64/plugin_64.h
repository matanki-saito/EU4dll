#pragma once
#include "pch.h"

enum Eu4Version {
	UNKNOWN = 0,
	v1_29_0_0 = 1290,
	v1_29_1_0 = 1291
};

typedef UINT64 DllErrorCode;

struct DllError{
	union {
		DllErrorCode code1;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
		};
	} version;

	union {
		DllErrorCode code2;
		struct {
			bool fontBufferExpansionInjector : 1;
			bool fontSizeLimitInjector : 1;
			bool fontBufferHeapZeroClearInjector : 1;
			bool debugProc1Injector : 1;
			bool fontBufferClearInjector : 1;
			bool mainTextProc1Injector : 1;
			bool mainTextProc2Injector : 1;
			bool mainTextProc3Injector : 1;
			bool mainTextProc3Injector2 : 1;
			bool mainTextProc4Injector : 1;
			bool tooltipAndButtonProc1Injector : 1;
			bool tooltipAndButtonProc2Injector : 1;
			bool tooltipAndButtonProc3Injector : 1;
			bool tooltipAndButtonProc4Injector : 1;
			bool tooltipAndButtonProc5Injector : 1;
		};
	} unmatch;

	void operator |= (DllError e)
	{
		this->version.code1 |= e.version.code1;
		this->unmatch.code2 |= e.unmatch.code2;
	}
};

union T {
	char text[0x10];
	char* p;
};

typedef struct {
	union T t;
	int len;
	int len2;
} V;

typedef struct {
	Eu4Version version;
} RunOptions;

namespace Version {
	Eu4Version GetVersion();
}

namespace Debug {
	DllError Init(RunOptions option);
}

namespace Font {
	DllError Init(RunOptions option);
}

namespace MainText {
	DllError Init(RunOptions option);
}

namespace TooltipAndButton {
	DllError Init(RunOptions option);
}