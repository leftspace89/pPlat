#pragma once
#include "LBuffInstance.h"
#define MAKE_INFO(NUM) NUM*0x4
#define MAKE_BLOB(NUM)  (0xE48 + ##NUM)

class
	DLLEXPORT CharDataInfo
{
public:

	MAKE_GET(PercentCooldownMod, float, 0x0);
	MAKE_GET(PercentCooldownCapMod, float, 0x10);
	MAKE_GET(PassiveCooldownEndTime, float, 0x20);
	MAKE_GET(PassiveCooldownTotalTime, float, 0x30);
	MAKE_GET(BonusAttackDamage, float, 0x40);
	MAKE_GET(FlatPhysicalDamageMod, float, 0x60);
	MAKE_GET(PercentPhysicalDamageMod, float, 0x70);
	MAKE_GET(FlatMagicDamageMod, float, 0x80);
	MAKE_GET(PercentMagicDamageMod, float, 0x90);
	MAKE_GET(FlatMagicReduction, float, 0xA0);
	MAKE_GET(PercentMagicReduction, float, 0xB0);
	MAKE_GET(FlatCastRangeMod, float, 0xC0);
	MAKE_GET(AttackSpeedMod, float, 0xD0);
	MAKE_GET(BaseAttackDamage, float, 0xE0);
	MAKE_GET(BaseAttackDamageSansPercentScale, float, 0xF0);
	MAKE_GET(FlatBaseAttackDamageMod, float, 0x100);
	MAKE_GET(PercentBaseAttackDamageMod, float, 0x110);
	MAKE_GET(BaseAbilityDamage, float, 0x120);
	MAKE_GET(ScaleSkinCoef, float, 0x130);
	MAKE_GET(Dodge, float, 0x140);
	MAKE_GET(Crit, float, 0x150);
	MAKE_GET(Armor, float, 0x160);
	MAKE_GET(BonusArmor, float, 0x170);
	MAKE_GET(SpellBlock, float, 0x180);
	MAKE_GET(BonusSpellBlock, float, 0x190);
	MAKE_GET(HPRegenRate, float, 0x1A0);
	MAKE_GET(BaseHPRegenRate, float, 0x1B0);
	MAKE_GET(MoveSpeed, float, 0x1C0);
	MAKE_GET(AttackRangeR, float, 0x1E0);
	MAKE_GET(FlatBubbleRadiusMod, float, 0x1F0);
	MAKE_GET(PercentBubbleRadiusMod, float, 0x200);
	MAKE_GET(FlatArmorPenetration, float, 0x210);
	MAKE_GET(PhysicalLethality, float, 0x220);
	MAKE_GET(PercentArmorPenetration, float, 0x230);
	MAKE_GET(PercentBonusArmorPenetration, float, 0x240);
	MAKE_GET(PercentCritBonusArmorPenetration, float, 0x250);
	MAKE_GET(PercentCritTotalArmorPenetration, float, 0x260);
	MAKE_GET(FlatMagicPenetration, float, 0x270);
	MAKE_GET(MagicLethality, float, 0x280);
	MAKE_GET(PercentMagicPenetration, float, 0x290);
	MAKE_GET(PercentBonusMagicPenetration, float, 0x2A0);
	MAKE_GET(PercentLifeStealMod, float, 0x2B0);
	MAKE_GET(PercentSpellVampMod, float, 0x2C0);
	MAKE_GET(PathfindingRadiusMod, float, 0x2D0);
	MAKE_GET(PercentCCReduction, float, 0x2E0);
	MAKE_GET(PercentEXPBonus, float, 0x2F0);
	MAKE_GET(PARRegenRate, float, 0x300);
	MAKE_GET(PrimaryARBaseRegenRateRep, float, 0x310);
	MAKE_GET(SecondaryARRegenRateRep, float, 0x320);
	
};

enum class GameObjectOrder
{
	HoldPosition = 1,
	MoveTo,
	AttackUnit,
	AutoAttackPet,
	AutoAttack,
	MovePet,
	AttackTo,
	Stop = 10
};
class MeshArray
{
public:
	RVector3 PathStart; //0x0000
	RVector3 PathEnd; //0x000C
}; //Size: 0x0018

class NavMesh
{
public:
	MeshArray ArrayMesh[5]; //0x0000
	char pad_0078[84]; //0x0078
}; //Size: 0x00CC
class
	DLLEXPORT Actor_Common
{
private:
public:
	static bool ApplyHooks();

	//bool CreatePath(GameObject* unit, const RVector3& destination, const NavigationPath& pathOut);
	//bool CreatePath(const RVector3& start, const RVector3& destination, const NavigationPath& pathOut);
	//void SmoothPath(NavigationPath* path);

	//int* GetNavMesh();
	bool GetHasNavPath()
	{
		return *reinterpret_cast<byte*>(this + static_cast<int>(Offsets::ActorCommonStruct::HasNavPath)) == 1;
	}
	MAKE_GET(ServerPosition, RVector3, Offsets::ActorCommonStruct::CurrentPosition);
	MAKE_GET(ClickedPosition, RVector3, Offsets::ActorCommonStruct::AINavPath);
	MAKE_GET(NavMesh, NavMesh*, Offsets::ActorCommonStruct::NavMesh);

	MAKE_GET(NavBegin, RVector3*, Offsets::ActorCommonStruct::NavBegin);//NAV ARRAY BEGIN
	MAKE_GET(NavEnd, RVector3*, Offsets::ActorCommonStruct::NavEnd);//NAV ARRAY BEGIN
	
	MAKE_GET(Velocity, RVector3, Offsets::ActorCommonStruct::Velocity);//NAV ARRAY BEGIN


};
//83 ec ? 56 8b f1 57 8b be ? ? ? ? 85 ff 74 ? 8b 8e
// create nav path
class
	DLLEXPORT AIManager_Client : public Actor_Common
{
public:
	Actor_Common * GetActor()
	{
		return *reinterpret_cast<Actor_Common**>(this + static_cast<int>(Offsets::Obj_AIBase::Actor_Common));
	}

	/*NavigationPath* GetNavPath()
	{
		return reinterpret_cast<NavigationPath*>(this + static_cast<int>(Offsets::ActorCommonStruct::AINavPath));
	}*/
};
class Obj_Hero;
class Obj_AI_Base : public AttackableUnit
{
public:
	static bool ApplyHooks();
	bool IssueOrder(RVector3* pos, GameObject*, GameObjectOrder order);
	float GetAttackCastDelay()
	{
		__try
		{
			auto returnValue = 0.0f;

			reinterpret_cast<float(__fastcall*)(void*, int)>
				(MAKE_RVA(0x55F630))
				(this, 64);

			__asm
			{
				movss returnValue, xmm2
			}

			return returnValue;
		}
		__except (1) { return 0; }
	}

	float GetAttackDelay()
	{
		__try
		{
			auto returnValue = 0.0f;

			reinterpret_cast<float(__fastcall*)(void*, int)>
				(MAKE_RVA(0x55F740))
				(this, 64);

			__asm
			{
				movss returnValue, xmm0
			}

			return returnValue;
		}
		__except (1) { return 0; }
	}

	bool HasBuff(char*buffname,bool isEqual)
	{
		for (auto buff : BuffInstance::GetBuffList(reinterpret_cast<GameObject*>(this)))
		{
			auto base = buff->GetScriptBaseBuff();

			if (base != nullptr)
			{
				auto name = std::string(buff->GetScriptBaseBuff()->GetName());
				for (size_t i = 0; i < name.length(); i++)
				{
					name[i] = tolower(name[i]);
				}
				
				if (isEqual)
				{
					if (strcmp(name.c_str(), buffname) == 0)
						return true;
				}
				else
				{
					if (!strstr(name.c_str(), buffname) == 0)
						return true;
				}
					
			}
		}
		return false;
	}
	double CalcAttackTime()
	{
		typedef float(__cdecl* fnGetAttackDelay)(GameObject* pObj, int index);
		fnGetAttackDelay stGet = reinterpret_cast<fnGetAttackDelay>(MAKE_RVA(Offsets::SpellHelper::ComputeCharacterAttackDelay)); // 1. ÝNDEX 57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ?
		float delay = stGet(this, 64);
		float ChampionBaseAttackSpeed = 1 / delay;
		float retn  = 1 / ChampionBaseAttackSpeed;
		//ENGINE_MSG("Retn %f baseattackspeed %f\n", retn, ChampionBaseAttackSpeed);
		return retn;
	}
	
	static std::vector<RVector3*> GetPathList(Obj_AI_Base*ptrin);
	std::vector<RVector3*> GetPathList();
	bool IsAttacking()
	{
		return HasBuff("attack", false);
	}
	bool IsMoving()
	{
		return GetPathList().size() > 2;
	}

	float GetPhysicalAttackDamage()
	{
		auto chardata = GetCharData();
		return *chardata->GetBaseAttackDamage() + *chardata->GetFlatPhysicalDamageMod();	
	}

	bool Obj_AI_Base::IsValidTarget()
	{
		if (this == nullptr)
			return false;

		if (*GetHealth() > 0 && this->GetServerPosition().Distance(ObjectManager::GetPlayer()->GetServerPosition()) < ObjectManager::GetPlayer()->GetAttackRange())
			return true;
		return false;
	}
	bool Obj_AI_Base::IsValidTarget(float range)
	{
		if (this == nullptr)
			return false;

		if (*GetHealth() > 0 && this->GetServerPosition().Distance(ObjectManager::GetPlayer()->GetServerPosition()) < range)
			return true;

		return false;
	}
	bool Obj_AI_Base::isValid()
	{
		if (this == nullptr)
			return false;

		if (*GetHealth() > 0)
			return true;

		return false;
	}
	static Obj_AI_Base*GetTargetByRange(float range)
	{
		float LastDist = FLT_MAX;
		Obj_AI_Base*target = nullptr;
		auto local = ObjectManager::GetPlayer();
		for (auto objptr : ObjectManager::GetHeroes(ObjectManager::ObjectTeam::Enemies))
		{
			auto curobj = (Obj_AI_Base*)objptr;
			if (!curobj->isValid())
				continue;
			auto localpos = local->GetPosition();
			float tmpdist = localpos.Distance(local->GetPosition());
			if (tmpdist < LastDist)
			{
				LastDist = tmpdist;
				target = curobj;
			}
		}
		return (Obj_AI_Base*)target;
	}
	float GetAttackRange()
	{
		return *GetCharData()->GetAttackRangeR() + 75.0f;
	}
	MAKE_GET(AIManager_Client, AIManager_Client*, Offsets::Obj_AIBase::AIManager);
	MAKE_GET(BuffManager, BuffManager, Offsets::BuffManagerStruct::GetBegin);
	MAKE_GET(Gold, float, Offsets::Obj_AIBase::Gold);
	MAKE_GET(GoldTotal, float, Offsets::Obj_AIBase::GoldTotal);
	MAKE_GET(Spellbook, Spellbook, Offsets::Spellbook::SpellbookInst);
	MAKE_GET(CharData, CharDataInfo, Offsets::Obj_AIBase::CharData);
	MAKE_GET(Begin, BuffNode*, Offsets::BuffManagerStruct::GetBegin);// objectin içinde oldugu için buraya alýyorum 
	MAKE_GET(End, BuffNode*, Offsets::BuffManagerStruct::GetEnd); 
};

