#pragma once

#include "plugin_64.h"

char* utf8ToEscapedStr(char* from);
ParadoxTextObject* utf8ToEscapedStr2(ParadoxTextObject* from);
ParadoxTextObject* escapedStrToUtf8(ParadoxTextObject* from);