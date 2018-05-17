#pragma once
#ifndef LOGGING


#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)


extern void ENGINE_MSG(const char* format, ...);
#define LOGGING
#endif // !LOGGING
