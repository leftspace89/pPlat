#pragma once
#ifndef TARGETSELECTOR
#define TARGETSELECTOR
#include "LBuffInstance.h"
class TargetSelector : public pComponent
{
public:
	bool bEnabled = true;
	bool bInited = false;
	 Obj_AI_Base * target=nullptr;
     Obj_AI_Base * forcetarget=nullptr;
	Obj_AI_Base*localplayer = nullptr;
	TargetSelector() { strcpy(classname, "TargetSelector");  strcpy(version, "0.0.1"); };
	~TargetSelector() {};
	void onProcessSpell(SpellData*spelldata, SpellCastInfo*spellcastinfo)
	{

	}
	void onStart()
	{
		target = nullptr;
		forcetarget = nullptr;
		bInited = true;
		ENGINE_MSG("Loaded Component: %s  : Version: %s\n", classname, version);
	}

	void onUpdate()
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		localplayer = ObjectManager::GetPlayer();

		if (forcetarget != nullptr)
			if (!forcetarget->isValid() || !*forcetarget->GetVisible())
				forcetarget = nullptr; // seçilmiþ hedef ölüyse veya visible deðilse nulle 

		if (target != nullptr)
			if (!target->isValid() || !*target->GetVisible())
				target = nullptr; // seçilmiþ hedef ölüyse veya visible deðilse nulle 
	}



	void onRender()
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		if (!localplayer)
			return;


	


		auto ttr = (Obj_AI_Base*)ObjectManager::GetNearMouseTarget();
		if (ttr != nullptr && forcetarget == nullptr)
			target = ttr;
		else
			target = nullptr;


		if (forcetarget != nullptr)
		{
			target = forcetarget;
		}

			

		if (GetAsyncKeyState(0x1))
		{
			auto obj = ObjectManager::GetUnderMouseObj();
			if (obj)
			{
				if(reinterpret_cast<Obj_AI_Base*>(obj)->isValid() && *reinterpret_cast<Obj_AI_Base*>(obj)->GetVisible())
				forcetarget = (Obj_AI_Base*)obj;
			}
			
		}
		else if (GetAsyncKeyState(VK_CAPITAL))
		{
			forcetarget = nullptr;
		}

		

	}
	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::TreeNode("TargetSelector"))
		{
			ui::Checkbox("Enabled", &bEnabled);
			ImGui::TreePop();
		}
	}
};
#endif