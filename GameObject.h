#pragma once

#ifndef GAMEOBJECT
#define GAMEOBJECT
class GameObjectVTable;

class GameObjectVTable
{
public:
	virtual ~GameObjectVTable() {}
	char pad_0004[64]; //0x0004

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
	virtual void Function10();
	virtual void Function11();
	virtual void Function12();
	virtual void Function13();
	virtual void Function14();
	virtual void Function15();
	virtual void Function16();
	virtual void Function17();
	virtual void Function18();
	virtual void Function19();
	virtual void Function20();
	virtual void Function21();
	virtual void Function22();
	virtual void Function23();
	virtual void Function24();
	virtual void Function25();
	virtual void Function26();
	virtual void Function27();
	virtual void Function28();
	virtual void Function29();
	virtual void Function30();
	virtual void Function31();
	virtual void Function32();
	virtual void Function33();
	virtual void Function34();
	virtual void Function35();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void Function40();
	virtual float BoundingGet();

}; //Size: 0x0044

#pragma pack(push, 1)
struct BBox
{
	float MinimumX;
	float MinimumY;
	float MinimumZ;
	float MaximumX;
	float MaximumY;
	float MaximumZ;
};

enum class UnitType
{
	NeutralMinionCamp,
	FollowerObject,
	FollowerObjectWithLerpMovement,
	AIHeroClient,
	AIMarker,
	AIMinionClient,
	AIMinionCommon,
	LevelPropAI,
	AITurretClient,
	AITurretCommon,
	obj_GeneralParticleEmitter,
	MissileClient,
	DrawFX,
	UnrevealedTarget,
	obj_Barracks,
	obj_BarracksDampener,
	obj_Lake,
	obj_AnimatedBuilding,
	Building,
	obj_Levelsizer,
	obj_NavPoint,
	obj_SpawnPoint,
	obj_LampBulb,
	GrassObject,
	HQ,
	obj_InfoPoint,
	BasicLevelProp,
	LevelPropGameObject,
	LevelPropSpawnerPoint,
	obj_Shop,
	obj_Turret,
	Unknown
};



class
	DLLEXPORT GameObject
{
public:
	GameObjectVTable * GetVirtual();

	UnitType GetType();
	byte* GetTypeByte();
	short* GetIndex();
	uint* GetNetworkId();

	MAKE_GET(LocalIndex, int, 0x8);

	RVector3 GetPosition()
	{
		if (this == nullptr)
		{
			return RVector3(0, 0, 0);
		}

		auto vec = reinterpret_cast<RVector3*>(this + static_cast<int>(Offsets::oGameObject::Position));
		if (vec == nullptr)
		{
			return RVector3(0, 0, 0);
		}

		return RVector3(vec->x, vec->y,vec->z);
	}

	RVector3 GetServerPosition()
	{
		if (this == nullptr)
		{
			return RVector3(0, 0, 0);
		}

		auto vec = reinterpret_cast<RVector3*>(this + static_cast<int>(Offsets::oGameObject::ServerPosition));
		if (vec == nullptr)
		{
			return RVector3(0, 0, 0);
		}

		return RVector3(vec->x, vec->y, vec->z);
	}

	float Distance(RVector3 vec)
	{
		return this->GetServerPosition().Distance(vec);
	}


	std::string GetName();
	char *namechar();
	void SetName(std::wstring);

	bool* GetIsDead()
	{
		return reinterpret_cast<bool*>(this + static_cast<int>(Offsets::oGameObject::IsDead));
	}

	
	MAKE_GET(Team, uint, Offsets::oGameObject::Team);
	MAKE_GET(BBox, BBox, Offsets::oGameObject::BBox);
	MAKE_GET(HeroName, String, 0x1738);
	MAKE_GET(Visible, bool, 0x02B0);
	MAKE_GET(IsInvulnerable, bool, 0x0394);

	//Lua API
	
};
#endif GAMEOBJECT