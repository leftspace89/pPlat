#pragma once
class
	DLLEXPORT ChildScriptBuff
{
public:
	MAKE_GET(SourceName, char, 0x1C);
};

class VirtualScriptBaseBuff
{
public:
	virtual ~VirtualScriptBaseBuff()
	{
	}

	virtual void Function0() = 0; //0
	virtual void Function1() = 0; //4
	virtual void Function2() = 0; //8
	virtual void Function3() = 0; //C
	virtual void Function4() = 0; //10
	virtual void Function5() = 0; //14
	virtual void Function6() = 0; //18
	virtual void Function7() = 0; //1C
	virtual void Function8() = 0; //20
	virtual void Function9() = 0; //24
	virtual void Function10() = 0; //28
	virtual void Function11() = 0; //2C
	virtual char* GetDisplayName() = 0; //30
};

class
	DLLEXPORT ScriptBaseBuff
{
public:
	VirtualScriptBaseBuff * GetVirtual()
	{
		return reinterpret_cast<VirtualScriptBaseBuff*>(this);
	}


	char *namechar()
	{

		IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetScriptBaseBuff::Name), "Unknown");
		__try
		{
			return (char*)reinterpret_cast<String*>(this + static_cast<int>(Offsets::OffsetScriptBaseBuff::Name));
		}
		__except (1)
		{
			return "except";
		}
	}

	std::string GetName()
	{
		std::string ss(namechar());

		return ss;

		//return *reinterpret_cast<String*>(this + static_cast<int>(Offsets::oGameObject::Name));


	}

	//std::string GetName()
	//{
	//	IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetScriptBaseBuff::Name), "Unknown");

	//	return *reinterpret_cast<String*>(this + static_cast<int>(Offsets::OffsetScriptBaseBuff::Name));
	//}

	ChildScriptBuff* GetChildScriptBuff()
	{
		__try
		{
			return *reinterpret_cast<ChildScriptBuff**>(this + static_cast<int>(Offsets::OffsetScriptBaseBuff::ChildScriptBuff));
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return nullptr;
		}
	}
};
class
	DLLEXPORT BuffInstance
{
public:
	//BuffInstance * GetBuffPtr(uint netid);
	//static BuffInstance * GetBuffPtr(uint netid);
	static std::vector<BuffInstance*> GetBuffList(GameObject*ptr);
	BuffInstance() {};
	bool IsPositive()
	{
	
		return false;
	}

	bool IsActive()
	{
		return false;
	}

	bool IsValid()
	{
		IS_NULL_RETN(this, 0x18, false);
		IS_NULL_RETN(this, 0x1C, false);
		IS_NULL_RETN(this, 0x4, false);
		IS_NULL_RETN(this, 0x68, false);
		IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetBuffInstance::StartTime), false);

		return this != nullptr
			&& *reinterpret_cast<DWORD*>(this + 0x18) != *reinterpret_cast<DWORD*>(this + 0x1C)
			&& *reinterpret_cast<DWORD*>(this + 0x4) || *reinterpret_cast<BYTE*>(this + 0x68)
			&& *this->GetStartTime() > 0; // Negative time on game reload?
	}

	bool IsPermanent()
	{
		IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetBuffInstance::EndTime), false);

		return *this->GetEndTime() > 20000.0;
	}

	ScriptBaseBuff* GetScriptBaseBuff()
	{
		IS_NULL_RETN(this, 0, nullptr);
		IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetBuffInstance::ScriptBaseBuff), nullptr);

		return *reinterpret_cast<ScriptBaseBuff**>(this + static_cast<int>(Offsets::OffsetBuffInstance::ScriptBaseBuff));
	}


	int GetCount()
	{
		IS_NULL_RETN(this, static_cast<int>(Offsets::OffsetBuffInstance::Count), 0);
		IS_NULL_RETN(this, 0x1C, 0);
		IS_NULL_RETN(this, 0x18, 0);

		if ((1 << *reinterpret_cast<DWORD *>(this)) & 0x4100000)
			return *reinterpret_cast<DWORD*>(this + static_cast<int>(Offsets::OffsetBuffInstance::Count));

		return (*reinterpret_cast<DWORD *>(this + 0x1C) - *reinterpret_cast<DWORD *>(this + 0x18)) >> 3;
	}

	int GetCountAlt()
	{
		IS_NULL_RETN(this, 0x20, 0);
		IS_NULL_RETN(this, 0x1C, 0);

		return (*reinterpret_cast<DWORD *>(this + 0x20) - *reinterpret_cast<DWORD *>(this + 0x1C)) >> 3;
	}


	//MAKE_GET( Count, int, Offsets::BuffInstance::Count );
	MAKE_GET(StartTime, float, Offsets::OffsetBuffInstance::StartTime);
	MAKE_GET(EndTime, float, Offsets::OffsetBuffInstance::EndTime);
	MAKE_GET(Type, uint, Offsets::OffsetBuffInstance::Type);

	MAKE_GET(Index, byte, Offsets::OffsetBuffInstance::Index);
	MAKE_GET(IsVisible, bool, Offsets::OffsetBuffInstance::IsVisible);
};