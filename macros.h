#pragma once
/*From EB*/
#define IS_NULL_RETN(OBJECT, ADDR, RETN) if ((DWORD*)(OBJECT + ADDR) == nullptr) { return RETN; }

#define MAKE_GET(NAME, TYPE, OFFSET) \
TYPE##* Get##NAME##() { \
	if(this==nullptr) {DWORD TT = 0; printf("MAKE_GET ERROR %p\n",OFFSET); return reinterpret_cast<TYPE*>(&TT); } \
	DWORD Address = (DWORD)this + static_cast<__int32>(OFFSET); \
	DWORD tmp; \
	SIZE_T numread;\
	if (ReadProcessMemory((HANDLE)-1, (LPVOID)Address, &tmp, sizeof(DWORD), &numread) == FALSE)\
	{\
		printf("MAKE_GET ERROR %p\n",Address);\
		DWORD TT = 0; return reinterpret_cast<TYPE*>(&TT);\
	}\
    return reinterpret_cast<TYPE*>((DWORD) this + static_cast<__int32>(OFFSET)); \
}

#define MAKE_SDATA(NAME, TYPE, OFFSET) \
__forceinline TYPE##* Get##NAME##() { \
	return (TYPE*)((DWORD) this->GetSDataArray() + static_cast<__int32>(OFFSET)); \
}

#define MAKE_GET_SET(NAME, TYPE, OFFSET) TYPE*## Get##NAME##() { return (TYPE*)(this + static_cast<__int32>(OFFSET)); } \
void Set##NAME##(TYPE value) { *Get##NAME() = value; }

#define MAKE_BOOL(NAME, OFFSET, SHIFT) inline bool Get##NAME##() { return (*(byte*)(this + static_cast<__int32>(OFFSET)) ##SHIFT) == 1; }

#ifndef DLLEXPORT
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT __declspec(dllexport)
//#define DLLEXPORT __declspec(dllimport)
#endif

#define MAKE_RVA(ADDRESS) ( (DWORD)GetModuleHandleA(0) + (DWORD)##ADDRESS )
#define MAKEPTR(ptr) *(DWORD*)((DWORD)GetModuleHandleA(0) + (DWORD)##ptr)