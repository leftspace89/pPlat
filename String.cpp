#include "stdafx.h"
#include "String.h"


String::operator const char*(void)
{
	return Get();
}

String::operator std::string(void)
{
	return std::string(Get());
}

char* String::Get(void)
{
	if (DWORD(this) <= 0x1000)
		return "";

	return _maxContentLength >= 0x10
		? *reinterpret_cast< char** >(_content)
		: _content;
}