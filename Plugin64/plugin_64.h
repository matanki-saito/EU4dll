#pragma once
#include "pch.h"

enum Eu4Version {
	UNKNOWN = 0,
	v1_29_0_0 = 1290,
	v1_29_1_0 = 1291
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
	errno_t Init(RunOptions option);
}

namespace Font {
	errno_t Init(RunOptions option);
}