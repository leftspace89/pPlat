const std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M", &tstruct);

	return buf;
}
void ENGINE_MSG(const char* format, ...)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
	std::string xd;
	xd += "[" + currentDateTime() + "] ";
	printf(xd.c_str());
	SetConsoleTextAttribute(hStdOut, FOREGROUND_WHITE);
	va_list list;
	va_start(list, format);
	vprintf(format, list);
	va_end(list);
}