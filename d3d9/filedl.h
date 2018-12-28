#pragma once

#if defined(UNICODE)
#define NhT2W	NhW2W
#define NhT2M	NhW2M
#define NhW2T	NhW2W
#define NhM2T	NhM2W
#else
#define NhT2W	NhM2W
#define NhT2M	NhM2M
#define NhW2T	NhW2M
#define NhA2T	NhA2M
#endif

#include <windows.h>
#include <conio.h>
#include <stdio.h>

int initFileDl();