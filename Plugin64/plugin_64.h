#pragma once
#include "pch.h"

enum Eu4Version {
	UNDEFINED = 0,
	UNKNOWN = 1,
	v1_29_0_0 = 1290,
	v1_29_1_0 = 1291,
	v1_29_2_0 = 1292,
	v1_29_3_0 = 1293,
	v1_29_4_0 = 1294,
	v1_30_1_0 = 1301,
	v1_30_2_0 = 1302,
	v1_30_3_0 = 1303,
	v1_30_4_0 = 1304,
	v1_30_5_0 = 1305,
	v1_31_1_0 = 1311,
	v1_31_2_0 = 1312,
	v1_31_3_0 = 1313,
	v1_31_4_0 = 1314,
	v1_31_5_0 = 1315,
	v1_31_6_0 = 1316,
	v1_32_0_1 = 1321,
	v1_33_0_0 = 1330,
	v1_33_3_0 = 1333,
	v1_34_2_0 = 1342,
	v1_35_1_0 = 1351,
	v1_36_0_0 = 1360,
	v1_37_0_0 = 1370
};

typedef UINT64 DllErrorCode;

inline std::string BoolToString(bool b)
{
	return b ? "NG" : "OK";
}

#define PL( f ) BoolToString(f) + ":" +  #f + "\n"
#define P( f ) #f ":" + BoolToString(f)

struct DllError{
	union {
		DllErrorCode code;
		struct {
			bool timeout : 1;
			bool waitFailed : 1;
			bool proccessFaild : 1;
		};

		std::string print() {
			return PL(timeout)
				+ PL(waitFailed)
				+ PL(proccessFaild);
		}
	} mod;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdDateProc1Injector : 1;
			bool versionDateProc1Injector : 1;
		};

		std::string print() {
			return PL(unmatchdDateProc1Injector)
				+ PL(versionDateProc1Injector);
		}
	} date;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdEventDialog1Injector : 1;
			bool versionEventDialog1Injector : 1;
			bool unmatchdEventDialog2Injector : 1;
			bool versionEventDialog2Injector : 1;
			bool unmatchdEventDialog3Injector : 1;
			bool versionEventDialog3Injector : 1;
		};

		std::string print() {
			return PL(unmatchdEventDialog1Injector)
				+ PL(versionEventDialog1Injector)
				+ PL(unmatchdEventDialog2Injector)
				+ PL(versionEventDialog2Injector)
				+ PL(versionEventDialog3Injector);
		}
	} eventDialog;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdFileSaveProc1Injector : 1;
			bool versionFileSaveProc1Injector : 1;
			bool unmatchdFileSaveProc2Injector : 1;
			bool versionFileSaveProc2Injector : 1;
			bool unmatchdFileSaveProc3Injector : 1;
			bool versionFileSaveProc3Injector : 1;
			bool unmatchdFileSaveProc4Injector : 1;
			bool versionFileSaveProc4Injector : 1;
			bool unmatchdFileSaveProc5Injector : 1;
			bool versionFileSaveProc5Injector : 1;
			bool unmatchdFileSaveProc6Injector : 1;
			bool versionFileSaveProc6Injector : 1;
			bool unmatchdFileSaveProc7Injector : 1;
			bool versionFileSaveProc7Injector : 1;
			bool unmatchdFileSaveProc8Injector : 1;
			bool versionFileSaveProc8Injector : 1;
			bool unmatchdFileSaveProc9Injector : 1;
			bool versionFileSaveProc9Injector : 1;
		};

		std::string print() {
			return PL(unmatchdFileSaveProc1Injector)
				+ PL(versionFileSaveProc1Injector)
				+ PL(unmatchdFileSaveProc2Injector)
				+ PL(versionFileSaveProc2Injector)
				+ PL(unmatchdFileSaveProc3Injector)
				+ PL(versionFileSaveProc3Injector)
				+ PL(unmatchdFileSaveProc4Injector)
				+ PL(versionFileSaveProc4Injector)
				+ PL(unmatchdFileSaveProc5Injector)
				+ PL(versionFileSaveProc5Injector)
				+ PL(unmatchdFileSaveProc6Injector)
				+ PL(versionFileSaveProc6Injector)
				+ PL(unmatchdFileSaveProc7Injector)
				+ PL(versionFileSaveProc7Injector)
				+ PL(unmatchdFileSaveProc8Injector)
				+ PL(versionFileSaveProc8Injector)
				+ PL(unmatchdFileSaveProc9Injector)
				+ PL(versionFileSaveProc9Injector);
		}
	} fileSave;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdCharCodePointLimiterPatchInjector : 1;
			bool versionCharCodePointLimiterPatchInjector : 1;
			bool unmatchdFontBufferHeapZeroClearInjector : 1;
			bool versionFontBufferHeapZeroClearInjector : 1;
			bool unmatchdFontBufferClear1Injector : 1;
			bool versionFontBufferClear1Injector : 1;
			bool unmatchdFontBufferClear2Injector : 1;
			bool versionFontBufferClear2Injector : 1;
			bool unmatchdFontBufferExpansionInjector : 1;
			bool versionFontBufferExpansionInjector : 1;
			bool unmatchdFontSizeLimitInjector : 1;
			bool versionFontSizeLimitInjector : 1;
		};

		std::string print() {
			return PL(unmatchdCharCodePointLimiterPatchInjector)
				+ PL(versionCharCodePointLimiterPatchInjector)
				+ PL(unmatchdFontBufferHeapZeroClearInjector)
				+ PL(versionFontBufferHeapZeroClearInjector)
				+ PL(unmatchdFontBufferClear1Injector)
				+ PL(versionFontBufferClear1Injector)
				+ PL(unmatchdFontBufferClear2Injector)
				+ PL(versionFontBufferClear2Injector)
				+ PL(unmatchdFontBufferExpansionInjector)
				+ PL(versionFontBufferExpansionInjector)
				+ PL(unmatchdFontSizeLimitInjector)
				+ PL(versionFontSizeLimitInjector);
		}
	} font;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdImeProc1Injector : 1;
			bool versionImeProc1Injector : 1;
			bool unmatchdImeProc2Injector : 1;
			bool versionImeProc2Injector : 1;
			bool unmatchdImeProc3Injector : 1;
			bool versionImeProc3Injector : 1;
		};

		std::string print() {
			return PL(unmatchdImeProc1Injector)
				+ PL(versionImeProc1Injector)
				+ PL(unmatchdImeProc2Injector)
				+ PL(versionImeProc2Injector)
				+ PL(unmatchdImeProc3Injector)
				+ PL(versionImeProc3Injector);
		}
	} ime;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdInputProc1Injector : 1;
			bool versionInputProc1Injector : 1;
			bool unmatchdInputProc2Injector : 1;
			bool versionInputProc2Injector : 1;
		};

		std::string print() {
			return PL(unmatchdInputProc1Injector)
				+ PL(versionInputProc1Injector)
				+ PL(unmatchdInputProc2Injector)
				+ PL(versionInputProc2Injector);
		}

	} input;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdListFieldAdjustmentProc1Injector : 1;
			bool versionListFieldAdjustmentProc1Injector : 1;
			bool unmatchdListFieldAdjustmentProc2Injector : 1;
			bool versionListFieldAdjustmentProc2Injector : 1;
			bool unmatchdListFieldAdjustmentProc3Injector : 1;
			bool versionListFieldAdjustmentProc3Injector : 1;
			bool unmatchdListFieldAdjustmentProc4Injector : 1;
			bool versionListFieldAdjustmentProc4Injector : 1;
		};

		std::string print() {
			return PL(unmatchdListFieldAdjustmentProc1Injector)
				+ PL(versionListFieldAdjustmentProc1Injector)
				+ PL(unmatchdListFieldAdjustmentProc2Injector)
				+ PL(versionListFieldAdjustmentProc2Injector)
				+ PL(unmatchdListFieldAdjustmentProc3Injector)
				+ PL(versionListFieldAdjustmentProc3Injector)
				+ PL(unmatchdListFieldAdjustmentProc4Injector)
				+ PL(versionListFieldAdjustmentProc4Injector);
		}

	} listFiledAdjustment;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdLocalizationProc1Injector : 1;
			bool versionLocalizationProc1Injector : 1;
			bool unmatchdLocalizationProc2Injector : 1;
			bool versionLocalizationProc2njector : 1;
			bool unmatchdLocalizationProc3Injector : 1;
			bool versionLocalizationProc3njector : 1;
			bool unmatchdLocalizationProc4Injector : 1;
			bool versionLocalizationProc4Injector : 1;
			bool unmatchdLocalizationProc5Injector : 1;
			bool versionLocalizationProc5Injector : 1;
			bool unmatchdLocalizationProc6Injector : 1;
			bool versionLocalizationProc6Injector : 1;
			bool unmatchdLocalizationProc7Injector : 1;
			bool versionLocalizationProc7Injector : 1;
			bool unmatchdLocalizationProc8Injector : 1;
			bool versionLocalizationProc8Injector : 1;
			bool unmatchdLocalizationProc9Injector : 1;
			bool versionLocalizationProc9Injector : 1;
		};

		std::string print() {
			return PL(unmatchdLocalizationProc1Injector)
				+ PL(versionLocalizationProc1Injector)
				+ PL(unmatchdLocalizationProc2Injector)
				+ PL(versionLocalizationProc2njector)
				+ PL(unmatchdLocalizationProc3Injector)
				+ PL(versionLocalizationProc3njector)
				+ PL(unmatchdLocalizationProc4Injector)
				+ PL(versionLocalizationProc4Injector)
				+ PL(unmatchdLocalizationProc5Injector)
				+ PL(versionLocalizationProc5Injector)
				+ PL(unmatchdLocalizationProc6Injector)
				+ PL(versionLocalizationProc6Injector)
				+ PL(unmatchdLocalizationProc7Injector)
				+ PL(versionLocalizationProc7Injector)
				+ PL(unmatchdLocalizationProc8Injector)
				+ PL(versionLocalizationProc8Injector)
				+ PL(unmatchdLocalizationProc9Injector)
				+ PL(versionLocalizationProc9Injector);
		}

	} localization;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMainTextProc1Injector : 1;
			bool versionMainTextProc1Injector : 1;
			bool unmatchdMainTextProc2Injector : 1;
			bool versionMainTextProc2Injector : 1;
			bool unmatchdMainTextProc3Injector : 1;
			bool versionMainTextProc3Injector : 1;
			bool unmatchdMainTextProc4Injector : 1;
			bool versionMainTextProc4Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMainTextProc1Injector)
				+ PL(versionMainTextProc1Injector)
				+ PL(unmatchdMainTextProc2Injector)
				+ PL(versionMainTextProc2Injector)
				+ PL(unmatchdMainTextProc3Injector)
				+ PL(versionMainTextProc3Injector)
				+ PL(unmatchdMainTextProc4Injector)
				+ PL(versionMainTextProc4Injector);
		}
	} mainText;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMapAdjustmentProc1Injector : 1;
			bool versionMapAdjustmentProc1Injector : 1;
			bool unmatchdMapAdjustmentProc2Injector : 1;
			bool versionMapAdjustmentProc2Injector : 1;
			bool unmatchdMapAdjustmentProc3Injector : 1;
			bool versionMapAdjustmentProc3Injector : 1;
			bool unmatchdMapAdjustmentProc4Injector : 1;
			bool versionMapAdjustmentProc4Injector : 1;
			bool unmatchdMapAdjustmentProc5Injector : 1;
			bool versionMapAdjustmentProc5Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMapAdjustmentProc1Injector)
				+ PL(versionMapAdjustmentProc1Injector)
				+ PL(unmatchdMapAdjustmentProc2Injector)
				+ PL(versionMapAdjustmentProc2Injector)
				+ PL(unmatchdMapAdjustmentProc3Injector)
				+ PL(versionMapAdjustmentProc3Injector)
				+ PL(unmatchdMapAdjustmentProc4Injector)
				+ PL(versionMapAdjustmentProc4Injector)
				+ PL(unmatchdMapAdjustmentProc5Injector)
				+ PL(versionMapAdjustmentProc5Injector);
		}
	} mapAdjustment;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMapJustifyProc1Injector : 1;
			bool versionMapJustifyProc1Injector : 1;
			bool unmatchdMapJustifyProc2Injector : 1;
			bool versionMapJustifyProc2Injector : 1;
			bool unmatchdMapJustifyProc3Injector : 1;
			bool versionMapJustifyProc3Injector : 1;
			bool unmatchdMapJustifyProc4Injector : 1;
			bool versionMapJustifyProc4Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMapJustifyProc1Injector)
				+ PL(versionMapJustifyProc1Injector)
				+ PL(unmatchdMapJustifyProc2Injector)
				+ PL(versionMapJustifyProc2Injector)
				+ PL(unmatchdMapJustifyProc3Injector)
				+ PL(versionMapJustifyProc3Injector)
				+ PL(unmatchdMapJustifyProc4Injector)
				+ PL(versionMapJustifyProc4Injector);
		}
	} mapJustify;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMapNudgeViewProc1Injector : 1;
			bool versionMapNudgeViewProc1Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMapNudgeViewProc1Injector)
				+ PL(versionMapNudgeViewProc1Injector);
		}
	} mapNudge;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMapPopupProc1Injector : 1;
			bool versionMapPopupProc1Injector : 1;
			bool unmatchdMapPopupProc2Injector : 1;
			bool versionMapPopupProc2Injector : 1;
			bool unmatchdMapPopupProc3Injector : 1;
			bool versionMapPopupProc3Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMapPopupProc1Injector)
				+ PL(versionMapPopupProc1Injector)
				+ PL(unmatchdMapPopupProc2Injector)
				+ PL(versionMapPopupProc2Injector)
				+ PL(unmatchdMapPopupProc3Injector)
				+ PL(versionMapPopupProc3Injector);
		}
	} mapPopup;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdMapViewProc1Injector : 1;
			bool versionMapViewProc1Injector : 1;
			bool unmatchdMapViewProc2Injector : 1;
			bool versionMapViewProc2Injector : 1;
			bool unmatchdMapViewProc3Injector : 1;
			bool versionMapViewProc3Injector : 1;
			bool unmatchdMapViewProc4Injector : 1;
			bool versionMapViewProc4Injector : 1;
		};

		std::string print() {
			return PL(unmatchdMapViewProc1Injector)
				+ PL(versionMapViewProc1Injector)
				+ PL(unmatchdMapViewProc2Injector)
				+ PL(versionMapViewProc2Injector)
				+ PL(unmatchdMapViewProc3Injector)
				+ PL(versionMapViewProc3Injector)
				+ PL(unmatchdMapViewProc4Injector)
				+ PL(versionMapViewProc4Injector);
		}

	} mapView;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdDebugProc1Injector : 1;
			bool versionDebugProc1Injector : 1;
		};

		std::string print() {
			return PL(unmatchdDebugProc1Injector)
				+ PL(versionDebugProc1Injector);
		}
	} debug;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdTooltipAndButtonProc1Injector : 1;
			bool versionTooltipAndButtonProc1Injector : 1;
			bool unmatchdTooltipAndButtonProc2Injector : 1;
			bool versionTooltipAndButtonProc2Injector : 1;
			bool unmatchdTooltipAndButtonProc3Injector : 1;
			bool versionTooltipAndButtonProc3Injector : 1;
			bool unmatchdTooltipAndButtonProc4Injector : 1;
			bool versionTooltipAndButtonProc4Injector : 1;
			bool unmatchdTooltipAndButtonProc5Injector : 1;
			bool versionTooltipAndButtonProc5Injector : 1;
			bool unmatchdTooltipAndButtonProc6Injector : 1;
			bool versionTooltipAndButtonProc6Injector : 1;
			bool unmatchdTooltipAndButtonProc7Injector : 1;
			bool versionTooltipAndButtonProc7Injector : 1;
			bool unmatchdTooltipAndButtonProc8Injector : 1;
			bool versionTooltipAndButtonProc8Injector : 1;
			bool unmatchdTooltipAndButtonProc9Injector : 1;
			bool versionTooltipAndButtonProc9Injector : 1;
			bool unmatchdTooltipAndButtonProc10Injector : 1;
			bool versionTooltipAndButtonProc10Injector : 1;
		};

		std::string print() {
			return PL(unmatchdTooltipAndButtonProc1Injector)
				+ PL(versionTooltipAndButtonProc1Injector)
				+ PL(unmatchdTooltipAndButtonProc2Injector)
				+ PL(versionTooltipAndButtonProc2Injector)
				+ PL(unmatchdTooltipAndButtonProc3Injector)
				+ PL(versionTooltipAndButtonProc3Injector)
				+ PL(unmatchdTooltipAndButtonProc4Injector)
				+ PL(versionTooltipAndButtonProc4Injector)
				+ PL(unmatchdTooltipAndButtonProc5Injector)
				+ PL(versionTooltipAndButtonProc5Injector)
				+ PL(unmatchdTooltipAndButtonProc6Injector)
				+ PL(versionTooltipAndButtonProc6Injector)
				+ PL(unmatchdTooltipAndButtonProc7Injector)
				+ PL(versionTooltipAndButtonProc7Injector)
				+ PL(unmatchdTooltipAndButtonProc8Injector)
				+ PL(versionTooltipAndButtonProc8Injector)
				+ PL(unmatchdTooltipAndButtonProc9Injector)
				+ PL(versionTooltipAndButtonProc9Injector)
				+ PL(unmatchdTooltipAndButtonProc10Injector)
				+ PL(versionTooltipAndButtonProc10Injector);
		}
	} tooltipAndButton;

	union {
		DllErrorCode code;
		struct {
			bool unmatchdCBitmapFontProc1Injector : 1;
			bool versionCBitmapFontProc1Injector : 1;
			bool unmatchdCBitmapFontProc2Injector : 1;
			bool versionCBitmapFontProc2Injector : 1;
		};

		std::string print() {
			return PL(unmatchdCBitmapFontProc1Injector)
				 + PL(versionCBitmapFontProc1Injector)
				 + PL(unmatchdCBitmapFontProc2Injector)
			 	 + PL(versionCBitmapFontProc2Injector);
		}
	} cBitmapFont;

	void operator |= (DllError e)
	{
		this->mod.code |= e.mod.code;
		this->date.code |= e.date.code;
		this->eventDialog.code |= e.eventDialog.code;
		this->fileSave.code |= e.fileSave.code;
		this->font.code |= e.font.code;
		this->ime.code |= e.ime.code;
		this->input.code |= e.input.code;
		this->listFiledAdjustment.code |= e.listFiledAdjustment.code;
		this->localization.code |= e.localization.code;
		this->mainText.code |= e.mainText.code;
		this->mapAdjustment.code |= e.mapAdjustment.code;
		this->mapJustify.code |= e.mapJustify.code;
		this->mapNudge.code |= e.mapNudge.code;
		this->mapPopup.code |= e.mapPopup.code;
		this->mapView.code |= e.mapView.code;
		this->tooltipAndButton.code |= e.tooltipAndButton.code;
		this->debug.code |= e.debug.code;
		this->cBitmapFont.code |= e.cBitmapFont.code;
	}

	bool errorCheck() {
		return this->mod.code > 0
			|| this->date.code > 0
			|| this->eventDialog.code > 0
			|| this->fileSave.code > 0
			|| this->font.code > 0
			|| this->ime.code > 0
			|| this->input.code > 0
			|| this->listFiledAdjustment.code > 0
			|| this->localization.code > 0
			|| this->mainText.code > 0
			|| this->mapAdjustment.code > 0
			|| this->mapJustify.code > 0
			|| this->mapNudge.code > 0
			|| this->mapPopup.code > 0
			|| this->mapView.code > 0
			|| this->tooltipAndButton.code > 0
			|| this->debug.code > 0
			|| this->cBitmapFont.code > 0;
	}

	std::string print() {
		return this->tooltipAndButton.print()
			+ "--------------\n"
			+ this->mapView.print()
			+ "--------------\n"
			+ this->debug.print()
			+ "--------------\n"
			+ this->mapPopup.print()
			+ "--------------\n"
			+ this->mapNudge.print()
			+ "--------------\n"
			+ this->mapJustify.print()
			+ "--------------\n"
			+ this->mapAdjustment.print()
			+ "--------------\n"
			+ this->mainText.print()
			+ "--------------\n"
			+ this->localization.print()
			+ "--------------\n"
			+ this->listFiledAdjustment.print()
			+ "--------------\n"
			+ this->input.print()
			+ "--------------\n"
			+ this->ime.print()
			+ "--------------\n"
			+ this->font.print()
			+ "--------------\n"
			+ this->fileSave.print()
			+ "--------------\n"
			+ this->eventDialog.print()
			+ "--------------\n"
			+ this->date.print()
			+ "--------------\n"
			+ this->mod.print()
			+ "--------------\n"
			+ this->cBitmapFont.print();
	}

	template <typename ... Args>
	std::string format(const std::string& fmt, Args ... args)
	{
		size_t len = std::snprintf(nullptr, 0, fmt.c_str(), args ...);
		std::vector<char> buf(len + 1);
		std::snprintf(&buf[0], len + 1, fmt.c_str(), args ...);
		return std::string(&buf[0], &buf[0] + len);
	}
};

// same std::basic_string<char>
typedef struct _ParadoxTextObject {
	union {
		char text[0x10];
		char* p;
	} t;
	UINT64 len;
	UINT64 len2;

	std::string getString() {
		if (len2 >= 0x10) {
			return std::string(t.p);
		}
		else {
			return std::string(t.text);
		}
	}

	void setString(std::string *src) {

		if (len2 >= 0x10) {
			auto hHeap = GetProcessHeap();
			HeapFree(hHeap, NULL, t.p);
		}

		len2 = src->capacity();
		len = src->length();

		if (len >= 0x10) {
 			len2 = 0xFF;
			auto hHeap = GetProcessHeap();
			auto p = (char*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY,  0xFF);
			if (p != NULL) {
				memcpy(p, src->c_str(), len+1);
				t.p = p;
			}
		}
		else {
			memcpy(t.text, src->c_str(), len+1);
		}
	}

} ParadoxTextObject;

typedef struct _RunOptions {
	Eu4Version version;
	bool test;
	bool reversingWordsBattleOfArea;
	int separateCharacterCodePoint;
	int lineBreakBufferWidth;
} RunOptions;

namespace Version {
	void GetVersionFromExe(RunOptions *option);
}

namespace Ini {
	void GetOptionsFromIni(RunOptions *option);
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

namespace MapView {
	DllError Init(RunOptions option);
}

namespace MapAdjustment {
	DllError Init(RunOptions option);
}

namespace MapJustify {
	DllError Init(RunOptions option);
}

namespace EventDialog {
	DllError Init(RunOptions option);
}

namespace MapPopup {
	DllError Init(RunOptions option);
}

namespace ListFieldAdjustment {
	DllError Init(RunOptions option);
}

namespace Validator {
	void Validate(DllError dllError, RunOptions options);
	bool ValidateVersion(DllError dllError, RunOptions options);
}

namespace FileSave {
	DllError Init(RunOptions option);
}

namespace Date {
	DllError Init(RunOptions option);
}

namespace MapNudgeView {
	DllError Init(RunOptions option);
}

namespace Ime {
	DllError Init(RunOptions option);
}

namespace Input {
	DllError Init(RunOptions option);
}

namespace Localization {
	DllError Init(RunOptions option);
}

namespace CBitmapFont {
	DllError Init(RunOptions option);
}