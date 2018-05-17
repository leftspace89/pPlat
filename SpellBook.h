#pragma once
class AIHeroClient;
class GameObject;
#include "Logging.hpp"
#pragma pack(push, 1)
//class String;
class
	DLLEXPORT SpellData
{
public:
	static SpellData* FindSpell(char* spellName);
	static SpellData* FindSpell(uint hash);
	static int HashSpell(char* spellName);

	DWORD* GetSDataArray()
	{
		return *reinterpret_cast<DWORD**>(reinterpret_cast<DWORD*>(this + 0x34)); //+0x4
	}

	//TODO:Yarým kaldý len mq
	char* GetNameFF()
	{
		IS_NULL_RETN(this, static_cast<int>(0x58), "Unknown");
	
		__try
		{

		

		char* castorig = reinterpret_cast<char*>(this + 0x58);
		if(strlen(castorig) <0x10)
			castorig = *reinterpret_cast<char**>(this + 0x58);


		return castorig;
		}
		__except (1)
		{
			return "except";
		}


		//std::string *sname = reinterpret_cast<std::string*>(this + 0x18);
	/*	if (sname->capacity()<=0)
		{
			return  reinterpret_cast<char*>(this + 0x18);
		}
		else
		{
			reinterpret_cast<char**>(this + 0x18);
		}*/

	}

	const char* GetNames()
	{
		if ((DWORD)this < 0x1000)
			return "";

		auto sname = *(std::string*)(this + 0x58);
		ENGINE_MSG("capacity : %d , %s\n", sname.capacity(), sname.c_str());
		return sname.c_str();
		/*return *reinterpret_cast<String*>(ptr);*/
	}

	//MAKE_GET(Name, std::string, 0x58); 
	MAKE_GET(castTime, float, 0x250);//8.9
	MAKE_GET(missileAccel, float, 0x474);
	MAKE_GET(missileSpeed, float, 0x42C);//8.9
	MAKE_GET(missileMaxSpeed, float, 0x480);
	MAKE_GET(missileMinSpeed, float, 0x484);
	MAKE_GET(missileWidth, float, 0x0460);//8.9
	MAKE_GET(castRange, float, 0x3C4);//8.9
	MAKE_GET(castRadius, float, 0x3C8);//8.9
	MAKE_GET(spellRadius, float, 0x104);//8.9


	MAKE_SDATA(Flags, int, 0x4);
	MAKE_SDATA(AffectsTypeFlags, int, 0x8);
	MAKE_SDATA(AffectsStatusFlags, int, 0xc);
	MAKE_SDATA(RequiredUnitTags, int, 0x10);
	MAKE_SDATA(ExcludedUnitTags, int, 0x28);
	MAKE_SDATA(PlatformSpellInfo, int, 0x4c);
	MAKE_SDATA(AlternateName, char*, 0x64);
	MAKE_SDATA(DisplayName, char*, 0x70);
	MAKE_SDATA(Description, char*, 0x7c);
	MAKE_SDATA(SpellTags, char*, 0x94);
	MAKE_SDATA(CastType, int, 0x43c); // cast type 


};

class
	DLLEXPORT SpellCastInfo
{
public:
	MAKE_GET(Counter, int, Offsets::oSpellCastInfo::Counter);
	MAKE_GET(Start, RVector3, 0x38);
	MAKE_GET(End, RVector3, 0x44);
	MAKE_GET(SpellSlot, int, Offsets::oSpellCastInfo::Slot);
	MAKE_GET(SenderIndex, WORD, 0x20);

	inline short GetLocalId()
	{
		__try
		{
			return (*reinterpret_cast<short*>(this + 0x58)) & 0xFFFF;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return 0;
		}
	}

	inline int GetLevel()
	{
		return (*reinterpret_cast<int*>(this + static_cast<int>(Offsets::oSpellCastInfo::Level))) + 1;
	}

	inline std::string* GetMissileName()
	{
		auto sdata = *reinterpret_cast<DWORD**>(this + static_cast<int>(Offsets::oSpellCastInfo::SpellData));
		return reinterpret_cast<std::string*>(sdata + 0x6);
	}

	inline SpellData* __stdcall GetSpellData()
	{
		return *reinterpret_cast<SpellData**>(this);
	}

	bool GetIsValid()
	{
		//Fuck me :S?

		__try
		{
			return *reinterpret_cast<DWORD*>(this + 0x60) == NULL
				&& *reinterpret_cast<DWORD*>(this + 0x64) == NULL
				&& *reinterpret_cast<DWORD*>(this + 0x68) == NULL
				&& *reinterpret_cast<DWORD*>(this + 0x6C) == NULL
				&& *reinterpret_cast<DWORD*>(this + 0x80) == NULL;
		}
		__except (1)
		{
			return false;
		}
	}
};
#pragma pack(push, 1)
class
	DLLEXPORT SpellDataInst
{
public:
	MAKE_GET(Level, int, Offsets::oSpellDataInst::Level);
	MAKE_GET(CooldownExpires, float, Offsets::oSpellDataInst::CooldownExpires);
	MAKE_GET(Ammo, int, Offsets::oSpellDataInst::Ammo);
	MAKE_GET(AmmoRechargeStart, int, Offsets::oSpellDataInst::AmmoRechargeStart);
	MAKE_GET(ToggleState, int, Offsets::oSpellDataInst::ToggleState);
	MAKE_GET(Cooldown, float, Offsets::oSpellDataInst::Cooldown);

	//SpellData* __stdcall SpellDataInst::GetSData()
	//{
	//	//return *(SpellData**) 
	//	//	(DWORD*) ((DWORD) *(DWORD**) ((DWORD) this + (int) Offsets::SpellDataInst::SpellData) + 0x34) + 0x10;

	//	return *reinterpret_cast<SpellData**>(this + static_cast<int>(Offsets::oSpellDataInst::SpellData));
	//}

	SpellData* __stdcall SpellDataInst::GetSData()
	{
		//auto sp = reinterpret_cast<SpellData*>(*reinterpret_cast<DWORD**>(this + static_cast<int>(Offsets::oSpellDataInst::SpellData)) + 0x34);
		__try
		{ 
		auto o11c = *(DWORD*)(this + static_cast<int>(Offsets::oSpellDataInst::SpellData));
		if (o11c < 0x12c)
			return 0;

		auto o34 = *(DWORD*)(o11c+0x34);
		return reinterpret_cast<SpellData*>(o34);
		}
		__except(1)
		{

		}
		//ENGINE_MSG("%p , %p\n", o11c,o34);
		return 0;
	}

	/*std::string* GetName()
	{
		return this->GetSData()->GetName();
	}*/
};
enum class SpellState // patlamþtýr mk kesin
{
	//Possible flags

	Ready = 0,
	NotAvailable = 4,
	Surpressed = 8,
	NotLearned = 12,
	Cooldown = 32, // done xd
	NoMana = 64, // xd
	Unknown
};
enum class SpellSlot
{
	Unknown = -1,
	Q = 0,
	W = 1,
	E = 2,
	R = 3,
	Summoner1 = 4,
	Summoner2 = 5,
	Item1 = 6,
	Item2 = 7,
	Item3 = 8,
	Item4 = 9,
	Item5 = 10,
	Item6 = 11,
	Trinket = 12,
	Recall = 13
};
class
	DLLEXPORT Spellbook
{
	static Spellbook* m_spellBook;

public:
	static bool ApplyHooks();
	SpellState CanUseSpell(SpellSlot);

	bool CastSpell(SpellSlot slot, RVector3 srcVector, RVector3 dstVector, DWORD target, bool triggerEvent);
	bool CastSpell(SpellSlot slot, bool triggerEvent = false);
	bool CastSpell(SpellSlot slot, GameObject* target, bool triggerEvent = false);
	bool CastSpell(SpellSlot slot, RVector3 pos, bool triggerEvent = false);
	bool CastSpell(SpellSlot slot, RVector3 srcPosition, RVector3 dstPosition, bool triggerEvent = false);
	//bool UpdateChargeableSpell(SpellSlot slot, Vector3f pos, bool releaseCast, bool triggerEvent = false);

	//bool EvolveSpell(SpellSlot slot);
	//bool LevelSpell(SpellSlot slot);
	//bool SpellSlotCanBeUpgraded(SpellSlot slot) const;
	SpellDataInst** Spellbook::GetSpells()
	{
		return reinterpret_cast<SpellDataInst**>(this + static_cast<int>(Offsets::SpellbookStruct::GetSpell));
	}
	SpellDataInst* Spellbook::GetSpell(uint slot)
	{
		return this->GetSpells()[static_cast<int>(slot)];
	}

	//static GameObject* GetOwner(Spellbook* spellbook);

	//MAKE_GET(ActiveSpellSlot, uint, Offsets::SpellbookStruct::ActiveSpellSlot);
	//MAKE_GET(SelectedSpellSlot, SpellSlot, Offsets::SpellbookStruct::TargetType);
	//MAKE_GET(SpellCaster, SpellCaster_Client*, Offsets::SpellbookStruct::SpellCaster_Client);
};