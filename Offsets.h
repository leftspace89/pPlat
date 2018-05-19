#pragma once
#undef PlaySound
#ifndef OFFSETS
#define OFFSETS
class Offsets
{
public:
     #include "ObjectsTR.h"


	// NOTE : nupd = means not updated not used..............
	enum class Game
	{
		Hud_OnDisconnect = 0x00f5c3e0,// Possible mismatch nupd
		Hud_OnAfk = 0x03595e53,// Possible mismatch nupd
		ClientMainLoop = 0x73DF50,
		DispatchEvent = 0x00c680bf,// Possible mismatch nupd 

		BuildDate = 0x0159D6D0,// Possible mismatch nupd
		BuildTime = BuildDate,// nupd
		BuildVersion = BuildTime + 0xC,// nupd
		BuildType = BuildVersion + 0xC,// nupd

		MovementCheck = 0x00000000,// Possible mismatch // nupd
		IsWindowFocused = 0x00000000,// Possible mismatch // nupd

		OnWndProc = 0x00000000,// Possible mismatch // nupd
		CRepl32InfoUpdatePacket = 0x00000000,// Possible mismatch // nupd

		PingNOP1 = 0x00000000,// Possible mismatch // nupd
		PingNOP2 = 0x00000000,// Possible mismatch // nupd
	};

	enum class MissionInfo
	{
		MissionInfoInst = 0x0,//nupd
		DrawTurretRange = 0x0,//nupd
	};

	enum class RiotClock
	{
		RiotClockInst = 0x0,//nupd
	};

	/*
	* Object related
	*/

	//localplayer 8b 0d ? ? ? ? d8 81 +1
	//objectlist 68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 0f b7 ? 3b 0d ? ? ? ? 7d ? a1 ? ? ? ? 8b 0c ? 89 4c
	//ALE-DFB7B379

	enum class ObjectManager
	{
		LocalPlayer = 0x2E2FEF8, //8.10
		ObjectList = 0x2E2D658,//8.10
		UnderMouseObj = 0x21D3DE4,//8.10
	};

	enum class GameObjectFunctions
	{
		OnDamage = 0x0,
		IssueOrder = 0x1C9EA0,//8.10 - 81 ec ? ? ? ? 53 8b d9 c7 44 24 08
	};


	enum class SpellHelper
	{
		
		ComputeCharacterAttackCastDelay = 0x546A40, //8.10 - 83 ec ? 53 8b 5c ? ? 8b cb 56 -  57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ? index 2
		ComputeCharacterAttackDelay = 0x546BB0, // 8.10 - 57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ? index 1
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
		SpellbookInst = 0x1CA0,//8.10 // 8d 88 ? ? ? ? e8 ? ? ? ? 80 3f
		Client_DoCastSpell = 0x540720,//8.10 // ERROR: Client Tried to cast a spell from an invalid slot:
		Client_GetSpellstate = 0x536080, //8.10 8b 44 ? ? 83 ec ? 53 8b 5c ? ? c6 00
		Client_OnProcessSpell=0x541B50, //8.10 57 8B 7C 24 08 8B 17 85 - 57 8b 7c ? ? 8b 17 85 d2
	};

	// castspell 540720 0x60C6A0


	//6a ? 8b f0 e8 ? ? ? ? 8b 0d
	enum class r3dRenderer
	{
		r3dRendererInstance = 0x2E54250,//8.10  68 ? ? ? ? e8 ? ? ? ? 83 c4 ? 89 06 8b 0d ? ? ? ? e8 ? ? ? ? 5e
		DrawCircularRangeIndicator = 0x537E90,//8.10 e8 ? ? ? ? 83 c4 ? 80 7e 41 ? 74
		r3dScreenTo3D = 0,//nupd
		r3dProjectToScreen = 0,//nupd
		LOLCursor=0x1585E18, // 8.10 a1 ? ? ? ? 8b 40 ? 85 c0 - 0f 84 ? ? ? ? a1 ? ? ? ? 8b 40 ? 85 c0
	};


	enum class BuffHost
	{
		BuffAddRemove = 0,//nupd
	};


	enum class Experience
	{
		XPToNextLevel = 0x0,//nupd
		XPToCurrentLevel = 0x0,//nupd
	};
};
#endif 