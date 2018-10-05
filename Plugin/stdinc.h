#pragma once

#define NOMINMAX

#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <fstream>
#include <utility>
#include <unordered_map>
#include <string>
#include <iterator>
#include <algorithm>
#include <utility>
#include <cstring>
#include <filesystem>
#include <boost/utility/string_view.hpp>
#include "../include/injector/hooking.hpp"
#include "../include/injector/calling.hpp"
#include "../include/injector/assembly.hpp"

#define VALIDATE_SIZE(type,size) static_assert(sizeof(type)==size, "Type size error.");

struct IncompleteClass
{
    template <typename T, std::uintptr_t offset>
    T *field()
    {
        return (T *)(reinterpret_cast<std::uintptr_t>(this) + offset);
    }

    template <typename T, std::uintptr_t offset>
    T get_field()
    {
        return *(T *)(reinterpret_cast<std::uintptr_t>(this) + offset);
    }
};

#define ESCAPE_SEQ_1 0x10
#define ESCAPE_SEQ_2 0x11
#define ESCAPE_SEQ_3 0x12
#define ESCAPE_SEQ_4 0x13

#define LOW_SHIFT 0x0E
#define HIGH_SHIFT 0x9

#define SHIFT_2 LOW_SHIFT
#define SHIFT_3 0x900
#define SHIFT_4 0x8F2

#define NO_FONT 0x98F
#define NOT_DEF 0x2026

#define EU4_ERROR1 0x10000

enum EU4Version {
	UNKNOWN=0,
	v1_25_X=125,
	v1_26_X=126,
	v1_27_X=127
};

namespace Font
{
	errno_t init(EU4Version version);
}

namespace MapJustify
{
	errno_t init(EU4Version version);
}

namespace MapAdj
{
	errno_t init(EU4Version version);
}

namespace MapView
{
	errno_t init(EU4Version version);
}

namespace Misc
{
	EU4Version getVersion();
	std::string versionString(EU4Version version);
	errno_t init(EU4Version version);
}

namespace TextView
{
	errno_t init(EU4Version version);
}

namespace Input
{
	errno_t init(EU4Version version);
}

namespace IME
{
	errno_t init(EU4Version version);
}

namespace ButtonAndToolTip
{
	errno_t init(EU4Version version);
}