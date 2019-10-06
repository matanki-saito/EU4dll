#include "pch.h"
#include "escape_tool.h"

inline wchar_t UCS2ToCP1252(int cp) {
	wchar_t result = cp;
	switch (cp) {
	case 0x20AC: result = 0x80; break;
	case 0x201A: result = 0x82; break;
	case 0x0192: result = 0x83; break;
	case 0x201E: result = 0x84; break;
	case 0x2026: result = 0x85; break;
	case 0x2020: result = 0x86; break;
	case 0x2021: result = 0x87; break;
	case 0x02C6: result = 0x88; break;
	case 0x2030: result = 0x89; break;
	case 0x0160: result = 0x8A; break;
	case 0x2039: result = 0x8B; break;
	case 0x0152: result = 0x8C; break;
	case 0x017D: result = 0x8E; break;
	case 0x2018: result = 0x91; break;
	case 0x2019: result = 0x92; break;
	case 0x201C: result = 0x93; break;
	case 0x201D: result = 0x94; break;
	case 0x2022: result = 0x95; break;
	case 0x2013: result = 0x96; break;
	case 0x2014: result = 0x97; break;
	case 0x02DC: result = 0x98; break;
	case 0x2122: result = 0x99; break;
	case 0x0161: result = 0x9A; break;
	case 0x203A: result = 0x9B; break;
	case 0x0153: result = 0x9C; break;
	case 0x017E: result = 0x9E; break;
	case 0x0178: result = 0x9F; break;
	}

	return result;
}

inline wchar_t CP1252ToUCS2(char cp) {
	wchar_t result = cp;
	switch (cp) {
	case 0x20AC: result = 0x80; break;
	case 0x201A: result = 0x82; break;
	case 0x0192: result = 0x83; break;
	case 0x201E: result = 0x84; break;
	case 0x2026: result = 0x85; break;
	case 0x2020: result = 0x86; break;
	case 0x2021: result = 0x87; break;
	case 0x02C6: result = 0x88; break;
	case 0x2030: result = 0x89; break;
	case 0x0160: result = 0x8A; break;
	case 0x2039: result = 0x8B; break;
	case 0x0152: result = 0x8C; break;
	case 0x017D: result = 0x8E; break;
	case 0x2018: result = 0x91; break;
	case 0x2019: result = 0x92; break;
	case 0x201C: result = 0x93; break;
	case 0x201D: result = 0x94; break;
	case 0x2022: result = 0x95; break;
	case 0x2013: result = 0x96; break;
	case 0x2014: result = 0x97; break;
	case 0x02DC: result = 0x98; break;
	case 0x2122: result = 0x99; break;
	case 0x0161: result = 0x9A; break;
	case 0x203A: result = 0x9B; break;
	case 0x0153: result = 0x9C; break;
	case 0x017E: result = 0x9E; break;
	case 0x0178: result = 0x9F; break;
	}

	return result;
}


errno_t convertWideTextToEscapedText(const wchar_t* from, char** to) {

	errno_t success = 0;
	int toIndex = 0;
	UINT64 size = 0;

	/* */
	if (from == NULL) {
		success = 1;
		goto A;
	}

	/* */
	size = wcslen(from);

	/* 全部エスケープしても３倍を超えることはない。１０はバッファ*/
	*to = (char*)calloc(size * 3 * 2 + 10, sizeof(char));

	if (*to == NULL) {
		success = 2;
		goto A;
	}

	/* */
	toIndex = 0;
	for (unsigned int fromIndex = 0; fromIndex < size; fromIndex++) {
		wchar_t cp = from[fromIndex];

		/* */
		if (UCS2ToCP1252(cp) != cp) {
			(*to)[toIndex++] = (BYTE)cp;
			continue;
		}

		/* ずらす */
		if (cp > 0x100 && cp < 0xA00) {
			cp = cp + 0xE000;
		}

		/* 上位バイト */
		BYTE high = (cp >> 8) & 0x000000FF;

		/* 下位バイト */
		BYTE low = cp & 0x000000FF;

		BYTE escapeChr = 0x10;

		/* 2byteじゃない */
		if (high == 0) {
			(*to)[toIndex++] = (BYTE)cp;
			continue;
		}

		/* high byteより決定 */
		switch (high) {
		case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
		case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
		case 0x80:case 0x7E:case 0x2F:case 0x5F:case 0xBD:case 0x3B:case 0x5D:
		case 0x3D:case 0x23:case 0x3F:case 0x3A:case 0x3C:case 0x3E:case 0x2A:
		case 0x7C:
			escapeChr += 2;
			break;
		default:
			break;
		}

		/* low byteより決定 */
		switch (low) {
		case 0xA4:case 0xA3:case 0xA7:case 0x24:case 0x5B:case 0x00:case 0x5C:
		case 0x20:case 0x0D:case 0x0A:case 0x22:case 0x7B:case 0x7D:case 0x40:
		case 0x80:case 0x7E:case 0x2F:case 0x5F:case 0xBD:case 0x3B:case 0x5D:
		case 0x3D:case 0x23:case 0x3F:case 0x3A:case 0x3C:case 0x3E:case 0x2A:
		case 0x7C:
			escapeChr++;
			break;
		default:
			break;
		}

		switch (escapeChr) {
		case 0x11:
			low += 14;
			break;
		case 0x12:
			high -= 9;
			break;
		case 0x13:
			low += 14;
			high -= 9;
			break;
		case 0x10:
		default:
			break;
		}

		(*to)[toIndex++] = escapeChr;
		(*to)[toIndex++] = low;
		(*to)[toIndex++] = high;
	}

A:
	return success;
}

errno_t convertEscapedTextToWideText(const std::string *from, std::wstring *to) {

	errno_t success = 0;
	int toIndex = 0;
	UINT64 size = 0;

	/* */
	toIndex = 0;
	for (unsigned int fromIndex = 0; fromIndex < size; fromIndex++) {
		char cp = from->at(fromIndex);
		int sp = 0;

		switch (cp) {
		case 0x10:
			sp = from->at(++fromIndex) | (from->at(++fromIndex) << 16);
			break;
		case 0x11:
			sp = (from->at(++fromIndex) | (from->at(++fromIndex) << 16)) - 0xE;
			break;
		case 0x12:
			sp = (from->at(++fromIndex) | (from->at(++fromIndex) << 16)) + 0x900;
			break;
		case 0x13:
			sp = (from->at(++fromIndex) | (from->at(++fromIndex) << 16)) + 0x8F2;
			break;
		default:
			sp = UCS2ToCP1252(cp);
		}

		if (sp > 0xFFFF || sp < 0x98F) {
			sp = 0x2026;
		}

		to->append((wchar_t)sp, 1);
	}

	return success;
}

errno_t convertTextToWideText(const char* from, wchar_t** to) {

	errno_t success = 0;
	unsigned int err = 0;
	unsigned int wideTextSize = 0;

	/* */
	if (from == NULL) {
		success = 1;
		goto A;
	}

	/* */
	wideTextSize = MultiByteToWideChar(
		CP_UTF8,
		NULL,
		from,
		-1,
		NULL,
		NULL);

	if (wideTextSize == NULL) {
		success = GetLastError();
		goto A;
	}

	/* */
	*to = (wchar_t*)calloc(wideTextSize, sizeof(wchar_t));

	if (*to == NULL) {
		success = 3;
		goto A;
	}

	/* */
	err = MultiByteToWideChar(
		CP_UTF8,
		NULL,
		from,
		-1,
		*to,
		wideTextSize);

	if (err == NULL) {
		success = 4;
		goto B;
	}

	goto A;

B:
	free(*to);
A:
	return success;
}

errno_t convertWideTextToUtf8(const std::wstring *from, std::string* to) {

	errno_t success = 0;
	unsigned int err = 0;

	/* */
	unsigned int textSize = WideCharToMultiByte(
		CP_UTF8,
		NULL,
		from->c_str(),
		-1,
		NULL,
		0,
		NULL,
		NULL);

	if (textSize == NULL) {
		success = GetLastError();
		goto A;
	}

	/* */
	char* buffer = (char*)calloc(textSize, sizeof(char));

	if (to == NULL) {
		success = 3;
		goto A;
	}

	/* */
	err = WideCharToMultiByte(
		CP_UTF8,
		NULL,
		from->c_str(),
		-1,
		buffer,
		textSize,
		NULL,
		NULL
	);

	if (err == NULL) {
		success = 4;
		goto B;
	}

	to->copy(buffer, textSize);

B:
	free(to);

A:
	return success;
}


ParadoxTextObject* tmpParadoxTextObject = NULL;
char* utf8ToEscapedStr(char* from) {

	if (tmpParadoxTextObject != NULL) {
		if (tmpParadoxTextObject->len > 0x10) {
			free(tmpParadoxTextObject->t.p);
		}
		delete tmpParadoxTextObject;
	}

	tmpParadoxTextObject = new ParadoxTextObject();

	wchar_t* tmp1 = NULL;
	char* tmp2 = NULL;

	char* src = NULL;

	if (*(from + 0x10) >= 0x10) {
		src = (char*)(*((uintptr_t*)from));
	}
	else {
		src = from;
	}

	//UTF-8 -> wide char (ucs2)
	convertTextToWideText(src, &tmp1);

	//wide char (ucs2) -> Escaped Text
	convertWideTextToEscapedText(tmp1, &tmp2);

	free(tmp1);

	UINT64 len = strlen(tmp2);
	tmpParadoxTextObject->len = len;
	tmpParadoxTextObject->len2 = len;

	if (len >= 0x10) {
		tmpParadoxTextObject->t.p = tmp2;
	}
	else {
		memcpy(tmpParadoxTextObject->t.text, tmp2, len);
	}

	return (char*)tmpParadoxTextObject;
}

ParadoxTextObject* tmpZV2 = NULL;
ParadoxTextObject* utf8ToEscapedStr2(ParadoxTextObject* from) {

	if (tmpZV2 != NULL) {
		if (tmpZV2->len > 0x10) {
			free(tmpZV2->t.p);
		}
		delete tmpZV2;
	}
	tmpZV2 = new ParadoxTextObject();

	wchar_t* tmp = NULL;
	char* tmp2 = NULL;

	char* src = NULL;

	if (from->len >= 0x10) {
		src = from->t.p;
	}
	else {
		src = from->t.text;
	}

	//UTF-8 -> wide char (ucs2)
	convertTextToWideText(src, &tmp);

	//wide char (ucs2) -> Escaped Text
	convertWideTextToEscapedText(tmp, &tmp2);

	free(tmp);

	UINT64 len = strlen(tmp2);
	tmpZV2->len = len;
	tmpZV2->len2 = len;

	if (len >= 0x10) {
		tmpZV2->t.p = tmp2;
	}
	else {
		memcpy(tmpZV2->t.text, tmp2, len);
	}

	return tmpZV2;
}

ParadoxTextObject* tmpParadoxTextObject2 = NULL;
ParadoxTextObject* escapedStrToUtf8(ParadoxTextObject* from) {

	if (tmpParadoxTextObject2 != NULL) {
		if (tmpParadoxTextObject2->len > 0x10) {
			free(tmpParadoxTextObject2->t.p);
		}
		delete tmpParadoxTextObject2;
	}
	tmpParadoxTextObject2 = new ParadoxTextObject();

	std::wstring* buffer = new std::wstring();
	std::string* dest = new std::string();
	std::string src = tmpParadoxTextObject2->getString();

	// Escaped Text -> wide char (ucs2)
	convertEscapedTextToWideText(&src, buffer);

	// wide char (ucs2) ->  UTF-8
	convertWideTextToUtf8(buffer, dest);

	from->setString(dest);

	delete &src;
	delete buffer;
	delete dest;

	return tmpParadoxTextObject2;
}