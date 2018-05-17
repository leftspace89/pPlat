#include "stdafx.h"
#include "SpellBook.h"
typedef void(__thiscall* fnCastSpell)(void* spellbook, SpellDataInst* a2, signed int spell_slot, RVector3* target_position, RVector3* startPos, int target_network_id);
fnCastSpell pCastSpell;
void __fastcall spellHook(void* spellbook,void*unk,void*unk1, SpellDataInst* sdataInst, signed int spellSlot, RVector3* dstVector, RVector3* srcVector, int targetNetId)
{
#ifdef _DEBUG1
	ENGINE_MSG("CastSpell () - SDataInst: %08x Spellslot: %d, Source: %g %g %g, Dst: %g %g %g, TargetNetId: %d, Spellbook: %08x",
		sdataInst,
		spellSlot,
		srcVector->x, srcVector->y, srcVector->z,
		dstVector->x, dstVector->y, dstVector->z,
		targetNetId,
		spellbook
	);
#endif
	pCastSpell(spellbook, sdataInst, spellSlot, dstVector, srcVector, targetNetId);
}
SpellState Spellbook::CanUseSpell(SpellSlot slot)
{

	return
		reinterpret_cast<SpellState(__thiscall*)(void*, const uint, const DWORD &)>
		MAKE_RVA(Offsets::Spellbook::Client_GetSpellstate)
		(this, static_cast<uint>(slot), NULL);
}

bool Spellbook::CastSpell(SpellSlot slot, RVector3 srcVector, RVector3 dstVector, DWORD targetNetworkId,bool triggerFuck) // en son base spell bu 
{
	if (this->CanUseSpell(slot) == SpellState::Ready)
	{
		RVector3 finalDstVector = dstVector, finalSrcVector = srcVector;
		pCastSpell = (fnCastSpell)MAKE_RVA(Offsets::Spellbook::Client_DoCastSpell);
		pCastSpell(this, this->GetSpell(static_cast<uint>(slot)), static_cast<signed int>(slot), &finalDstVector, &finalSrcVector, targetNetworkId);
		return true;
	}
	return false;
}

bool Spellbook::CastSpell(SpellSlot slot, bool triggerEvent)
{
	return this->CastSpell(slot, RVector3(0, 0, 0), RVector3(0, 0, 0), *ObjectManager::GetPlayer()->GetNetworkId());
}

bool Spellbook::CastSpell(SpellSlot slot, GameObject* target, bool triggerEvent)
{
	return this->CastSpell(slot, RVector3(0, 0, 0), target->GetPosition(), *target->GetNetworkId(), triggerEvent);
}

bool Spellbook::CastSpell(SpellSlot slot, RVector3 position, bool triggerEvent)
{
	return this->CastSpell(slot, RVector3(0, 0, 0), position, 0, triggerEvent);
}

bool Spellbook::CastSpell(SpellSlot slot, RVector3 srcPosition, RVector3 dstPosition, bool triggerEvent)
{
	return this->CastSpell(slot, srcPosition, dstPosition, 0, triggerEvent);
}



// DEFINE
typedef void(__thiscall* _OnProcessSpell)(void* SpellBook, SpellCastInfo* castinfo);
_OnProcessSpell pOnProcessSpell;

void __fastcall hk_OnProcessSpell(void* SpellBook, void* edx, SpellCastInfo* castinfo)
{

	
	auto param3 = (SpellData*)*(DWORD *)(*(DWORD *)castinfo + 0x34);
	auto param1 = *(DWORD *)(castinfo + 0x494);
	auto param4 = *(BYTE *)(castinfo + 0x48D);
	auto param5 = *(BYTE *)(castinfo + 0x48E);

	for (DWORD pPtr : pComponents)
	{
		pComponent*component = reinterpret_cast<pComponent*>(pPtr);
		auto spelldata = (SpellData*)*(DWORD *)(*(DWORD *)castinfo + 0x34);
		component->onProcessSpell(spelldata, castinfo);
	}

	//ENGINE_MSG("Param 1 : %p param 3 : %p  param 4 : %p param 5 : %p param 6 : %p  ,  pos : %f %f %f,name :%s \n" ,param1,param3,param4,param5, castinfo,castinfo->GetEnd()->x, castinfo->GetEnd()->y, castinfo->GetEnd()->z, param3->GetNameFF());
	return pOnProcessSpell(SpellBook, castinfo);
}
bool Spellbook::ApplyHooks()
{

	pOnProcessSpell = (_OnProcessSpell)DetourFunction((PBYTE)MAKE_RVA(Offsets::Spellbook::Client_OnProcessSpell), (PBYTE)hk_OnProcessSpell);


	//pCastSpell = (fnCastSpell)DetourFunction((PBYTE)MAKE_RVA(Offsets::Spellbook::Client_DoCastSpell), (PBYTE)spellHook);
	
	//fnCastSpell spell = reinterpret_cast<fnCastSpell>(MAKEPTR(oCastSpell));

	return false;
}

