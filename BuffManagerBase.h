#pragma once
#pragma pack(push, 1)
class BuffInstance;
struct BuffNode
{
	BuffInstance* buffInst;
	void* _unk;
};

class
	DLLEXPORT BuffManager
{
public:
	MAKE_GET(Begin, BuffNode*, Offsets::BuffManagerStruct::GetBegin);
	MAKE_GET(End, BuffNode*, Offsets::BuffManagerStruct::GetEnd);
};