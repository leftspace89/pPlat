#include "stdafx.h"
#include "Obj_AI_Base.h"

MAKE_HOOK<convention_type::stdcall_t, void, GameObjectOrder, RVector3*, GameObject*, DWORD, DWORD, DWORD> EventIssueOrder;
typedef void(__thiscall* tIssueOrder)(void*thiss, int Mode, RVector3* Pos, GameObject *target, int a4, int a5, char a7);
tIssueOrder issueP;
void __fastcall issueOrderHook(void *thiss,void *Unknown, int mode, RVector3* start, GameObject *target, int isAttackMove, int a5, char a7)
{
#ifdef _DEBUG1
	ENGINE_MSG("OnIssueOrder() Sender: %08x - Order: %08x - Start: %g %g %g - GameObj Target: %08x - a1: %08x - a2: %08x - a3: %08x", thiss, mode, start->x, start->y, start->z, target, isAttackMove, a5, a7);
	printf("========================\r\n\r\n");
#endif

	return issueP(thiss,mode, start, target, isAttackMove, a5, a7);
}

bool Obj_AI_Base::ApplyHooks()
{
	issueP = (tIssueOrder)DetourFunction((PBYTE)MAKE_RVA(Offsets::GameObjectFunctions::IssueOrder), (PBYTE)issueOrderHook);
	return true;	
}
bool Obj_AI_Base::IssueOrder(RVector3* position, GameObject* unit, GameObjectOrder order)
{

	static auto humanizer = Humanizer(40, 100);

	if (!humanizer.CanExecute(static_cast<byte>(order)))
	{
		return false;
	}


	if (position == nullptr || this == nullptr)
	{
		return false;
	}

	if (order == GameObjectOrder::AttackUnit
		&& unit == nullptr)
	{
		return false;
	}

	auto issueOrderFlags1 = 0x0000000;
	auto issueOrderFlags2 = 0x0000000;

	switch (order)
	{
	case GameObjectOrder::HoldPosition:
		issueP(this,static_cast<int>(GameObjectOrder::Stop), position, nullptr, 0, 0, 0x0000001);

		issueOrderFlags1 = 0x0000000;
		issueOrderFlags2 = 0x0000001;
		break;
	case GameObjectOrder::MoveTo:
	case GameObjectOrder::AttackTo:
	case GameObjectOrder::AttackUnit:
	case GameObjectOrder::AutoAttack:
	case GameObjectOrder::AutoAttackPet:
		issueOrderFlags1 = 0xffffff00;
		break;
	case GameObjectOrder::Stop:
		issueOrderFlags2 = 0x0000001;
		break;
	case GameObjectOrder::MovePet:
		break;
	}

	/*__asm
	{
		mov ecx, this;
	}*/

	issueP(this, static_cast<int>(order), position, unit, 0, issueOrderFlags1, issueOrderFlags2);

	return true;
}