#pragma once
#ifndef CLASSES
#define oUnderMouseObject 0x21D7A1C
#define pfnIssueOrder 0x1C9780
#define pfnMainLoop 0x73DF50
#define pfnAttackDelay  0x54CA90
#define pfnDrawCircle 0x5413A0
#define oLocalPlayer 0x2E31A7C
#define oObjectManager 0x2E30EA0 
#define oCursorPTR 0x1589A94 
#define oRenderer 0x2E5A448
#define oGetAttackCastDelay 0x54C980
#define oTotalAttackSpeed 0x021D6BEC
#define oCastSpell 0x548D90 // "League of Legends.exe"+60EE48 caller
#define MAKEPTR(ptr) (DWORD)GetModuleHandleA(0) + (DWORD)##ptr
// Created with ReClass.NET by KN4CK3R

class T3
{
public:
	char pad_0000[24]; //0x0000
	float AttackSpeedtotal; //0x0018
	char pad_001C[40]; //0x001C
}; //Size: 0x0044

class t2
{
public:
	char pad_0000[656]; //0x0000
	class T3* tt3; //0x0290
	char pad_0294[1456]; //0x0294
}; //Size: 0x0844

class T1
{
public:
	char pad_0000[120]; //0x0000
	class t2* tt2; //0x0078
	char pad_007C[968]; //0x007C
}; //Size: 0x0444

class baseattack
{
public:
	class T1* tt1; //0x0000
	char pad_0004[60]; //0x0004
}; //Size: 0x0040
   // Created with ReClass.NET by KN4CK3R

   // Created with ReClass.NET by KN4CK3R

class AIManagerClient
{
public:
	char pad_0000[16]; //0x0000
	D3DXVECTOR3 NextPathPos; //0x0010
	char pad_001C[384]; //0x001C
	float MoveSpeed; //0x019C
	bool isMoving; //0x01A0
	char pad_01A1[95]; //0x01A1
	D3DXVECTOR3 NavPos; //0x0200
	char pad_020C[212]; //0x020C
}; //Size: 0x02E0

class SpellInfo
{
public:
	char pad_0000[28]; //0x0000
	uint32_t Level; //0x001C
	char pad_0020[72]; //0x0020
	float CoolDown; //0x0068
	char pad_006C[128]; //0x006C
	float ActiveTime; //0x00EC
	char pad_00F0[1876]; //0x00F0
}; //Size: 0x0844

class pCharData
{
public:
	float PercentCooldownMod; //0x0000
	char pad_0004[12]; //0x0004
	float PercentCooldownCapMod; //0x0010
	char pad_0014[76]; //0x0014
	float FlatPhysicalDamageMod; //0x0060
	char pad_0064[28]; //0x0064
	float mBaseAbilityDamage; //0x0080
	char pad_0084[76]; //0x0084
	float AttackSpeedMod; //0x00D0
	char pad_00D4[12]; //0x00D4
	float BaseAttackDamage; //0x00E0
	char pad_00E4[108]; //0x00E4
	float Crit; //0x0150
	char pad_0154[108]; //0x0154
	float MoveSpeed; //0x01C0
}; //Size: 0x01C4
class buffName
{
public:
	char pad_0000[8]; //0x0000
	std::string name;
	


}; //Size: 0x004F

//bool IsValid()
//{
//	IS_NULL_RETN(this, 0x18, false);
//	IS_NULL_RETN(this, 0x1C, false);
//	IS_NULL_RETN(this, 0x4, false);
//	IS_NULL_RETN(this, 0x68, false);
//	IS_NULL_RETN(this, static_cast<int>(0x8), false);
//
//	return this != nullptr
//		&& *reinterpret_cast<DWORD*>(this + 0x18) != *reinterpret_cast<DWORD*>(this + 0x1C)
//		&& *reinterpret_cast<DWORD*>(this + 0x4) || *reinterpret_cast<BYTE*>(this + 0x68)
//		&& StartTime > 0; // Negative time on game reload?
//}
//bool IsPermanent()
//{
//	IS_NULL_RETN(this, static_cast<int>(0xC), false);
//
//	return EndTime > 20000.0;
//}
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
	 ScriptBaseBuff
{
public:
	VirtualScriptBaseBuff * GetVirtual()
	{
		return reinterpret_cast<VirtualScriptBaseBuff*>(this);
	}

	char* GetName()
	{
		IS_NULL_RETN(this, static_cast<int>(0x8), "Unknown");

		return reinterpret_cast<char*>(this + static_cast<int>(0x8));
	}

	
};
#ifdef clos
class BuffInstance
{
public:
	uint32_t type; //0x0000
	class buffName* buffName; //0x0004
	float StartTime; //0x0008
	float EndTime; //0x000C
	char pad_0010[96]; //0x0010
	uint8_t Index; //0x0070
	char pad_0071[1024]; //0x0071
	
	ScriptBaseBuff* GetScriptBaseBuff()
	{
		IS_NULL_RETN(this, 0, nullptr);
		IS_NULL_RETN(this, static_cast<int>(0x4), nullptr);
		if (reinterpret_cast<DWORD>(this) < 100)
			return nullptr;

		return *reinterpret_cast<ScriptBaseBuff**>(this + static_cast<int>(0x4));
	}
}; //Size: 0x0471

class BuffManagerArr
{
public:
	class BuffInstance* Buff; //0x0000
}; //Size: 0x0004

class BuffArrpTR
{
public:
	std::vector<BuffInstance*>BuffManager;
	//BuffManagerArr BuffManager[1]; //0x0000
	char pad_0004[64]; //0x0004
}; //Size: 0x0044
#endif


class BuffInstance
{
public:
	//std::vector<BuffInstance*> GetBuffList(DWORD object);
	BuffInstance* GetBuffPtr();
	//DWORD object=0;
	

	bool IsPermanent()
	{
		IS_NULL_RETN(this, static_cast<int>(0xC), false);

		return *this->GetEndTime() > 20000.0;
	}
	bool IsValid()
	{
		IS_NULL_RETN(this, 0x18, false);
		IS_NULL_RETN(this, 0x1C, false);
		IS_NULL_RETN(this, 0x4, false);
		IS_NULL_RETN(this, 0x68, false);
		IS_NULL_RETN(this, static_cast<int>(0x8), false);

		return this != nullptr
			&& *reinterpret_cast<DWORD*>(this + 0x18) != *reinterpret_cast<DWORD*>(this + 0x1C)
			&& *reinterpret_cast<DWORD*>(this + 0x4) || *reinterpret_cast<BYTE*>(this + 0x68)
			&& *this->GetStartTime() > 0; // Negative time on game reload?
	}

	ScriptBaseBuff* GetScriptBaseBuff()
	{
		IS_NULL_RETN(this, 0, nullptr);
		IS_NULL_RETN(this, static_cast<int>(0x4), nullptr);

		return *reinterpret_cast<ScriptBaseBuff**>(this + static_cast<int>(0x4));
	}


	MAKE_GET(StartTime, float, 0x8);
	MAKE_GET(EndTime, float, 0xC);
	MAKE_GET(Type, uint32_t, 0x0);
	MAKE_GET(Index, byte, 0x70);

};

#pragma pack(push, 1)
struct BuffNode
{
	BuffInstance* buffInst;
	void* _unk;
};

class
	 BuffManager
{
public:
	MAKE_GET(Begin, BuffNode*, 24);
	MAKE_GET(End, BuffNode*, 28);
};


class LSLObject
{
public:
	char pad_0000[20]; //0x0000
	uint32_t ls_team; //0x0014
	char pad_0018[8]; //0x0018
	char* ls_username; //0x0020
	char pad_0024[216]; //0x0024
	D3DXVECTOR3 ls_Position; //0x00FC
	char pad_0108[1392]; //0x0108
	float CurrentHealth; //0x0678
	char pad_067C[12]; //0x067C
	float MaxHealth; //0x0688
	char pad_068C[308]; //0x068C
	char Name[4]; //0x07C0
	char pad_07C4[664]; //0x07C4
	float GetAttackDelay; //0x0A5C
	char pad_0A60[40]; //0x0A60
	float LS_Armor; //0x0A88
	char pad_0A8C[4]; //0x0A8C
	float LS_SpellArmor; //0x0A90
	char pad_0A94[12]; //0x0A94
	float LS_MoveSpeed; //0x0AA0
	char pad_0AA4[4]; //0x0AA4
	float LS_AttackRange; //0x0AA8
	char pad_0AAC[932]; //0x0AAC
	pCharData charData; //0x0E50
	char pad_1014[564]; //0x1014
	class AIManagerClient* AIManagerPtr; //0x1248
	float Gold; //0x124C
	char pad_1250[12]; //0x1250
	float TotalGold; //0x125C
	char pad_1260[56]; //0x1260
	class BuffArrpTR* BuffManagerStart; //0x1298
	uint32_t BuffManagerEnd; //0x129C
	char pad_12A0[10638]; //0x12A0
	uint32_t SpellBook; //0x3C2E
	char pad_3C32[28]; //0x3C32
	class SpellInfo* ActiveSpell; //0x3C4E
	char pad_3C52[4]; //0x3C52
	float Q_ManaCost; //0x3C56
	char pad_3C5A[12]; //0x3C5A
	float W_ManaCost; //0x3C66
	char pad_3C6A[12]; //0x3C6A
	float E_ManaCost; //0x3C76
	char pad_3C7A[12]; //0x3C7A
	float R_ManaCost; //0x3C86
	char pad_3C8A[1236]; //0x3C8A
	class SpellInfo* Q_Spell; //0x415E
	class SpellInfo* W_Spell; //0x4162
	class SpellInfo* E_Spell; //0x4166
	class SpellInfo* R_Spell; //0x416A
	char pad_416E[1412]; //0x416E
	uint32_t ls_Champ_len; //0x46F2
	char pad_46F6[8]; //0x46F6
	char ls_Champion_name[11]; //0x46FE
	char pad_4709[23465]; //0x4709
	MAKE_GET(networkid, uint32_t, 0x74); 
	MAKE_GET(Begin, BuffNode*, 0x1298);
	MAKE_GET(End, BuffNode*, 0x129C);
	//MAKE_GET(BuffManager, BuffManager, 0x1298);
}; //Size: 0xA2B2
class pObject
{
public:
	class LocalPlayer* ls_LocalPlayer; //0x0000
	char pad_0004[15420]; //0x0004
}; //Size: 0x3C40







class LSLCursor
{
public:
	char pad_0000[144]; //0x0000
	D3DXVECTOR3 CursorPosXYZ; //0x0090
	char pad_009C[176]; //0x009C
}; //Size: 0x014C

class LSLRenderer
{
public:
	char _0x0000[32];
	__int32 screenWidth; //0x0020 
	__int32 screenHeight; //0x0024 
	char _0x0028[100];
	D3DXMATRIX viewMatrix; //0x008C 
	D3DXMATRIX projectionMatrix; //0x00CC 

};
#define CLASSES
#endif