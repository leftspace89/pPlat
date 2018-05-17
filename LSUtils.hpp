#pragma once
#ifndef LSUtils
#define LSUtils
namespace LSUtils
{
	DWORD curtickkey;
	bool Mask(const BYTE * pData, const BYTE * bMask, const char * szMask)
	{
		for (; *szMask; ++szMask, ++pData, ++bMask)
			if (*szMask == 'x' && *pData != *bMask)
				return false;
		return (*szMask) == NULL;
	}
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE * bMask, char * szMask)
	{
		for (DWORD i = 0; i < dwLen; i++)
			if (Mask((BYTE*)(dwAddress + i), bMask, szMask))
				return (DWORD)(dwAddress + i);
		return 0;
	}

	DWORD CreateThreadA(void*ptr)
	{
		DWORD tid = 0;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ptr, 0, 0, &tid);
		return tid;
	}

	bool GetKeyPressed(int vKey)
	{
		bool isPressed = GetAsyncKeyState(vKey) & 0x8000 && GetTickCount() - curtickkey  > 300;
		if (isPressed)
		{
			curtickkey = GetTickCount();
		}
		return isPressed;
	}
}
#endif