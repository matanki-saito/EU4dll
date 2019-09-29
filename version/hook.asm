VERSION_EXPORTS STRUCT
	GetFileVersionInfoA	QWORD	?
	GetFileVersionInfoByHandle	QWORD	?
	GetFileVersionInfoExA	QWORD	?
	GetFileVersionInfoExW	QWORD	?
	GetFileVersionInfoSizeA	QWORD	?
	GetFileVersionInfoSizeExA	QWORD	?
	GetFileVersionInfoSizeExW	QWORD	?
	GetFileVersionInfoSizeW	QWORD	?
	GetFileVersionInfoW	QWORD	?
	VerFindFileA	QWORD	?
	VerFindFileW	QWORD	?
	VerInstallFileA	QWORD	?
	VerInstallFileW	QWORD	?
	VerLanguageNameA	QWORD	?
	VerLanguageNameW	QWORD	?
	VerQueryValueA	QWORD	?
	VerQueryValueW	QWORD	?
VERSION_EXPORTS ENDS

EXTERN version: STRUCT

.CODE
_GetFileVersionInfoA proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoA
_GetFileVersionInfoA endp

_GetFileVersionInfoByHandle proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoByHandle
_GetFileVersionInfoByHandle endp

_GetFileVersionInfoExA proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoExA
_GetFileVersionInfoExA endp

_GetFileVersionInfoExW proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoExW
_GetFileVersionInfoExW endp

_GetFileVersionInfoSizeA proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoSizeA
_GetFileVersionInfoSizeA endp

_GetFileVersionInfoSizeW proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoSizeW
_GetFileVersionInfoSizeW endp

_GetFileVersionInfoSizeExA proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoSizeExA
_GetFileVersionInfoSizeExA endp

_GetFileVersionInfoSizeExW proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoSizeExW
_GetFileVersionInfoSizeExW endp

_GetFileVersionInfoW proc
	jmp (VERSION_EXPORTS PTR version).GetFileVersionInfoW
_GetFileVersionInfoW endp

_VerFindFileA proc
	jmp (VERSION_EXPORTS PTR version).VerFindFileA
_VerFindFileA endp

_VerFindFileW proc
	jmp (VERSION_EXPORTS PTR version).VerFindFileW
_VerFindFileW endp

_VerInstallFileA proc
	jmp (VERSION_EXPORTS PTR version).VerInstallFileA
_VerInstallFileA endp

_VerInstallFileW proc
	jmp (VERSION_EXPORTS PTR version).VerInstallFileW
_VerInstallFileW endp

_VerLanguageNameA proc
	jmp (VERSION_EXPORTS PTR version).VerLanguageNameA
_VerLanguageNameA endp

_VerLanguageNameW proc
	jmp (VERSION_EXPORTS PTR version).VerLanguageNameW
_VerLanguageNameW endp

_VerQueryValueA proc
	jmp (VERSION_EXPORTS PTR version).VerQueryValueA
_VerQueryValueA endp

_VerQueryValueW proc
	jmp (VERSION_EXPORTS PTR version).VerQueryValueW
_VerQueryValueW endp
END