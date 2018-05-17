#pragma once
#define CLASSES

//-----------GAMEOBJECT-----------//

enum class oGameObject //8.9
{
	Type = 0x4,
	Team = 0x14,
	Name = 0x1C,
	Position = 0xF4,
	ServerPosition = 0xF4,
	BoundingRadius = 0x90,
	BBox = 0x94,
	IsDead = 0x118,
	VisibleOnScreen = 0xDC,
	NetworkId = 0x6C,
};

//-----------ATTACKABLEUNIT-----------//

enum class oAttackableUnit
{
	Health = 0x670,
	MaxHealth = Health + 0x10,
	Mana = 0x20c,
	MaxMana = Mana + 0x10,

	IsBot = 0x1170,
	HasBotAI = IsBot + 0x1,

	IsInVulnerable = 0x2D0,
	IsPhysicalImmune = IsInVulnerable + 0x10,
	MagicImmune = IsPhysicalImmune + 0x10,
	IsLifestealImmune = MagicImmune + 0x10,

	IsZombie = 0x12,

	ArmorMaterial = 0x330,
	WeaponMaterial = 0x348,

	AllShield = 0x194,
	AttackShield = 0x0A88,
	MagicShield = 0x0A90,

	OverrideCollisionRadius = 0x3a8, //dword ptr [edi+3C4h]
	OverrideCollisionHeight = OverrideCollisionRadius + 0x4, //dword ptr [edi+3C0h]
	PathfindingCollisionRadius = OverrideCollisionHeight + 0x4,

	Direction = 0x2BA0,
	IsTargetable = 0x1E8,
	IsTargetableToTeamFlags = 0x1F8,
};

//-----------AI_BASE-----------//

enum class Obj_AIBase
{
	ResourceName = 0x240,

	Gold = 0x1210,//8.9
	GoldTotal = Gold + 0x10,

	EvolvePoints = 0x35EC,
	PlayerControlled = 0x93C,

	//SpellCastBlockingAI = 0, //deprecated
	//AI_LastPetSpawnedID = 0, //deprecated
	//PetReturnRadius = 0, //deprecated
	//EnemyId = 0, //deprecated
	//TauntTargetId = EnemyId + 0x4,
	//FearLeashPoint = TauntTargetId + 0x4,

	//LastPausePosition = 0, //deprecated
	//DeathDuration = 0, //deprecated

	ExpGiveRadius = 0x934,
	AutoAttackTargettingFlags = 0x33B8,

	CharacterState = 0x95C + 0x4, //IssueOrder
	CharacterActionState = CharacterState + 0x4,
	CharacterIntermediate = 0x9b8,

	CombatType = 0x2E80,
	SkinName = 0x8d0, //INGAME

					  //AIManager, Actor_Common
					  AIManager = 0x175C,//8.9
					  Actor_Common = 0x4, // 8.9

					  //SetSkin
					  CharacterDataStack = 0x33E8,

					  //UserComponent
					  UserComponent = 0x2ED0, //Capture

											  //CharData
											  CharData = 0xE18, //8.9

																 // 6.1
																 mPercentDamageToBarracksMinionMod = 0xE68,
																 mFlatDamageReductionFromBarracks = 0xE78,
};

//-----------MINION-----------//

enum class Obj_AIMinion
{
	RoamState = 0x35D8,
	OriginalState = RoamState + 0x4,
	CampNumber = OriginalState + 0x4,
	MinionLevel = 0x3664,
	LeashedPosition = 0x35E8
};

//-----------AIHEROCLIENT-----------//

enum class Obj_AIHero
{
	Experience = 0x362C,

	ChampionName = 0x46FE,
	Avatar = 0x5898,
	Level = Experience + 0x10,
	NumNeutralMinionsKilled = 0x37D0,
};

//-----------UnitInfoComponent-----------//

enum class UnitInfoComponent
{
	InfoComponent = 0x1160
};

//-----------Obj_BarracksDampener-----------//

enum class Obj_BarracksDampener
{
	DampenerState = 0x720
};

//-----------SPELLMISSILE-----------//

enum class Obj_SpellMissile
{
	SpellCaster = 0x150,
	LaunchPos = 0x150,
	DestPos = 0x15C,
	MissileData = 0x11C,
	SData = 0x13C,
	TargetId = 0x180,
	Path = 0x0
};

enum class SpellMissileData
{
	SpellCaster = 0x0,
	SData = 0xD8,
	CastInfo = 0x0
};

//-----------HEROINVENTORY-----------//

enum class InventorySlot
{
	Stacks = 0x4,
	Charges = 0x8,
	PurchaseTime = 0xC,
	ItemInfo = 0xC
};

enum class ItemNode
{
	BuffScript = 0x18,
	Slot = 0x10,
	Name = 0x0,
	ItemId = 0x70,
	MaxStacks = ItemId + 0x4,
	ItemCost = 0x98,
	RecipeItemIds = 0xB0
};

//-----------BUFFINSTANCE-----------//

enum class OffsetBuffInstance
{
	StartTime = 0x8,
	EndTime = 0xC,
	Type = 0x0,
	Index = 0x70,
	Count = 0x6C,
	IsVisible = 0xA8,

	ScriptBaseBuff = 0x4,
	BuffScriptInfo = 0x1C
};

enum class OffsetScriptBaseBuff
{
	Name = 0x8,
	DisplayName = 0x34,
	ChildScriptBuff = 0x48
};

//-----------SPELLBOOK-----------//

enum class SpellbookStruct
{
	ActiveSpellSlot = 0xC,
	CastTime = 0x28,
	CastEndTime = 0x2C,
	TargetType = 0x8,
	Owner = 0x1C,
	SpellCaster_Client = 0x20,
	GetSpell = 0x530, //8.9

	SBookInst = 0x14
};

enum class oSpellCastInfo
{
	SpellData = 0x0,
	Counter = 0x4,
	Level = 0x8, //+1
	TargetIndex = 0x4,
	Start = 0x30,
	End = 0x3C,
	Slot = 0x3b8
};

enum class MissileClient
{
	MissileClientData = 0x120,
	SpellCaster = 0x130,
	TargetId = 0x178,
};


//83 bd 1c 01 00 00 ? 0f 84 ? ? ? ? 8b 5c // SPELLDATA OFFSET 11C EASYXDXDXD NEXT TIME RITO I WILL FUCK YOU
enum class oSpellDataInst
{
	Level = 0x1C,
	CooldownExpires = 0x14,
	Ammo = 0x18,
	AmmoRechargeStart = 0x24,
	ToggleState = 0x28,
	Cooldown = 0x68,
	SpellData = 0x11C, //8.9 83 ec ? 53 55 56 8b 74 ? ? 8b e9 57 83 be 1c 01 00 00
	IsSealed = 0x84
};

//-----------DAMAGEINFO-----------//

enum class DamageInfo
{
	Damage = 0x24,
	DamageType = 0x54,
	DamageHitType = 0x248
};

//-----------ActorCommon-----------//

enum class ActorCommonStruct //8.8
{
	NavMesh = 0x1BC, //navmesh array
	CurrentPosition = 0x2BC,
	HasNavPath = 0x19c,
	AINavPath = 0x0010,
	NavBegin = 0x1BC,
	NavEnd = 0x1C0,
	Velocity=0x2C8
};




//-----------r3dRenderer-----------//

enum class r3dRendererStruct
{
	View = 0x8C, //w2s
	Projection = 0xCC,
	ClientWidth = 0x20,
	ClientHeight = 0x24,
};


//-----------Experience-----------//

enum class ExperienceStruct
{
	NumExperience = 0x0,
	Level = 0x10,
	SpellTrainingPoints = 0x34,
};

//-----------BuffManager-----------//

enum class BuffManagerStruct
{
	GetBegin = 0x1258,//8.9
	GetEnd = 0x125c // 8.9
};

//-----------RiotClock-----------//

enum class RiotClockStruct
{
	GameTime = 0x4, //Virtual
	Time = 0x2C,
	Delta = 0x14,
};

//-----------MissionInfo-----------//

enum class MissionInfoStruct
{
	GameType = 0x0,
	MapId = 0x4,
	GameMode = 0x8,
	GameId = 0x54
};
