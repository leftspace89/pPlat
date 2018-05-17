#pragma once
class String
{
	char        _content[0x10];
	int         _contentLength = 0;
	int         _maxContentLength = 0;

public:

	operator const char*(void);
	operator std::string(void);

private:
	char* Get(void);
};

