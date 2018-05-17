#pragma once
#undef PlaySound
#ifndef OFFSETS
#define OFFSETS
class Offsets
{
public:
     #include "ObjectsTR.h"

	enum class Game
	{
		Hud_OnDisconnect = 0x00f5c3e0,// Possible mismatch
		Hud_OnAfk = 0x03595e53,// Possible mismatch
		ClientMainLoop = 0x73DF50,
		DispatchEvent = 0x00c680bf,// Possible mismatch

		BuildDate = 0x0159D6D0,// Possible mismatch
		BuildTime = BuildDate,
		BuildVersion = BuildTime + 0xC,
		BuildType = BuildVersion + 0xC,

		MovementCheck = 0x00000000,// Possible mismatch
		IsWindowFocused = 0x00000000,// Possible mismatch

		OnWndProc = 0x00000000,// Possible mismatch
		CRepl32InfoUpdatePacket = 0x00000000,// Possible mismatch

		PingNOP1 = 0x00000000,// Possible mismatch
		PingNOP2 = 0x00000000,// Possible mismatch
	};

	enum class MissionInfo
	{
		MissionInfoInst = 0x016720AC,//nupd
		DrawTurretRange = 0x0063e3f0,//nupd
	};

	enum class RiotClock
	{
		RiotClockInst = 0x03309e0c,//nupd
	};

	/*
	* Object related
	*/

	//localplayer 8b 0d ? ? ? ? d8 81 +1
	//objectlist 68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 0f b7 ? 3b 0d ? ? ? ? 7d ? a1 ? ? ? ? 8b 0c ? 89 4c
	//ALE-DFB7B379

	enum class ObjectManager
	{
		LocalPlayer = 0x2E1EAC4, //8.9
		ObjectList = 0x2E1C290,//8.9
		UnderMouseObj = 0x21C2BE4,//8.9
	};


	enum class GameObjectFunctions
	{
		OnDamage = 0x0,
		IssueOrder = 0x1C7820,//8.9 81 ec ? ? ? ? 53 8b d9 c7 44 24 08
	};


	enum class SpellHelper
	{
		ComputeCharacterAttackCastDelay = 0x54C7D0, //8.9 83 ec ? 53 8b 5c ? ? 8b cb 56 -  57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ? index 2
		ComputeCharacterAttackDelay = 0x54C770, // 8.9 57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ? index 1
		GetBasicAttack = 0x0,//nupd
	};
	


	/*
	* BuffManager
	*/

	


	/*
	* Spellbook
	*/
	//["CastSpell", "ERROR: Client Tried to cast a spell from an invalid slot:", 3],
	enum class Spellbook
	{
		//Functions
		SpellbookInst = 0x1C80,//8.9 // 8d 88 ? ? ? ? e8 ? ? ? ? 80 3f
		Client_DoCastSpell = 0x5464C0,//8.9 // 83 ec ? 53 55 56 8b 74 ? ? 8b e9 57 83 be 1c 01 00 00
		Client_GetSpellstate = 0x53BD30, //8.9 8b 44 ? ? 83 ec ? 53 8b 5c ? ? c6 00
		Client_OnProcessSpell=0x5478C0, //8.9 57 8B 7C 24 08 8B 17 85 - 57 8b 7c ? ? 8b 17 85 d2
	};


	//6a ? 8b f0 e8 ? ? ? ? 8b 0d
	enum class r3dRenderer
	{
		r3dRendererInstance = 0x2E42DBC,//8.9  68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 89 06 8b 0d ? ? ? ? e8 ? ? ? ? 5e
		DrawCircularRangeIndicator = 0x53DB90,//8.9 e8 ? ? ? ? 83 c4 ? 80 7e 41 ? 74
		r3dScreenTo3D = 0,//nupd
		r3dProjectToScreen = 0,//nupd
		LOLCursor=0x1574C20, // 8.9 a1 ? ? ? ? 8b 40 ? 85 c0 - 0f 84 ? ? ? ? a1 ? ? ? ? 8b 40 ? 85 c0
	};


	enum class BuffHost
	{
		BuffAddRemove = 0,//nupd
	};


	enum class Experience
	{
		XPToNextLevel = 0x00e27510,//nupd
		XPToCurrentLevel = 0x0094F4D0,//nupd
	};
};
#endif 