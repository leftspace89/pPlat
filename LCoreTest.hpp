#pragma once
#ifndef LCORETEST
#define LCORETEST

class LCoreTest : public pComponent
{
public:
	bool bEnabled = false;
	bool bInited = false;
	Obj_AI_Base*localplayer = nullptr;
	LCoreTest() { strcpy(classname, "LCoreTest"); strcpy(classname, "Brand"); strcpy(version, "0.0.2"); };
	~LCoreTest() {};


	void onStart()
	{
		localplayer = ObjectManager::GetPlayer();
		if (localplayer == nullptr)
			return;

		std::string name = *localplayer->GetHeroName();

		if (localplayer)
		if (!strcmp(name.c_str(), Heroname) == 0)
		  return;
		
		bInited = true;

		ENGINE_MSG("Loaded Component: %s Hero :  %s Version: %s\n", classname,Heroname, version);
		
	}
	void onUpdate()
	{
		localplayer = ObjectManager::GetPlayer();
		if (localplayer == nullptr)
			return;
	}
	RVector3 lastspell;
	void onProcessSpell(SpellData*spelldata, SpellCastInfo*spellcastinfo)
	{
		return;
		if (spelldata != nullptr && spellcastinfo)
		{
		
			auto endPos = *spellcastinfo->GetEnd();
			auto startPos = *spellcastinfo->GetStart();
			lastspell = endPos;
			ENGINE_MSG("Core Spell : %f %f %f\n", lastspell.x, lastspell.y, lastspell.z);
			
		}
	}

	void onRender()
	{
		if (bEnabled)
		{
	
			if (lastspell !=RVector3(0,0,0))
			{

				RVector3 ScreenS,local2d;
				if (render.r3dWorldToScreen(&ObjectManager::GetPlayer()->GetPosition(), &local2d))
				if (render.r3dWorldToScreen(&lastspell, &ScreenS))
				{
					render.DrawLine(local2d.x, local2d.y, ScreenS.x, ScreenS.y, 10, D3DCOLOR_ARGB(255, 255, 0, 0));
				}
			}

#ifndef localplayerexample
			auto player = ObjectManager::GetPlayer();
			if (player)
			{
				RVector3 Screen;
				if (render.r3dWorldToScreen(&player->GetPosition(), &Screen))
				{
					std::string name = *player->GetHeroName();
					render.DrawString(Screen.x, Screen.y, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "LocalPlayer  : %s", name.c_str());
				}
			}
#endif

			for (GameObject*minion : ObjectManager::GetMinions(ObjectManager::ObjectTeam::All))
			{


				auto base = (Obj_AI_Base*)minion;
				auto basecord = base->GetPosition();//LinePred->Calculate(base);

				//RVector3 predict2;
				//render.r3dWorldToScreen(&ObjectManager::GetPlayer()->GetPosition(), &predict2);
				//render.DrawString(predict2.x, predict2.y + (buffin * 10) + 50, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "Buff : %s", name.c_str());
			
			}

			
#ifdef buffList
			int buffin = 0;
			for (auto buff : BuffInstance::GetBuffList(reinterpret_cast<GameObject*>(ObjectManager::GetPlayer())))
			{
				auto base = buff->GetScriptBaseBuff();

				if (base != nullptr)
				{
					auto name = std::string(buff->GetScriptBaseBuff()->GetName());
					for (size_t i = 0; i < name.length(); i++)
					{
						name[i] = tolower(name[i]);
					}

					RVector3 predict2;
					render.r3dWorldToScreen(&ObjectManager::GetPlayer()->GetPosition(), &predict2);
					render.DrawString(predict2.x, predict2.y+(buffin*10)+50, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "Buff : %s",name.c_str());
					buffin++;
				}
			}
#endif

		


			RVector3 Screen;

			if (targetselector->target !=nullptr)
			{
				if (render.r3dWorldToScreen(&targetselector->target->GetPosition(), &Screen))
				{
					render.DrawString(Screen.x, Screen.y + 50, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "Target");
				}
			}
			


			if (GetAsyncKeyState(VK_LSHIFT))
			{
				//ObjectManager::GetPlayer()->GetSpellbook()->CastSpell(SpellSlot::Q, RVector3(0, 0, 0), RVector3(0,0,0));
				auto aim = *ObjectManager::GetPlayer()->GetAIManager_Client();
				auto comm = aim->GetActor();
				auto veloc = *comm->GetVelocity();
				ENGINE_MSG("Aimanagerclient : %p , common : %p , %f %f %f\n", aim, comm,veloc.x,veloc.y,veloc.z);
			}
		


		}
	}
	void onMenu()
	{
		if (ImGui::TreeNode("Core Test"))
		{
			ui::Checkbox("Enabled", &bEnabled);

			ImGui::TreePop();
		}
	}
	

};
#endif