#pragma once
#ifndef TYPEDEFS
//using fnGetAttackCastDelay = double(__cdecl*)(LSLObject* pEntity, int iAaId);
//fnGetAttackCastDelay GetAttackCastDelay;
namespace lol
{
	extern MAKE_CALL<static_cast<DWORD>(Offsets::r3dRenderer::DrawCircularRangeIndicator), convention_type::cdecl_t, void*, RVector3 */*pos*/, float /*radius*/, int */*color*/, int/**/, float /*0*/, int /*0*/, float /*Default 1*/ >r3dDrawCircle;
	//extern MAKE_CALL<static_cast<DWORD>(Offsets::GameObjectFunctions::IssueOrder), convention_type::thiscall_r, void, GameObject */*Player*/, int /*Mode*/, RVector3* /*Pos*/, GameObject */*target*/, int /*a4*/, int /*a5*/, char /*a7*/ >r3dIssueOrder;
	//extern MAKE_CALL<oGetAttackCastDelay, convention_type::cdecl_t, double, LSLObject* /*pEntity*/, int /*iAaId*/>r3dGetAttackCastDelay;
}

#define TYPEDEFS
#endif