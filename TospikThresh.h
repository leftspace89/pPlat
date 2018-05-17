#pragma once
#ifndef TOSPIKTHRESH
#define TOSPIKTHRESH
#include "LBuffInstance.h"
class TospikThresh : public pComponent
{
public:
	bool bEnabled = true, bAutoQ = true,bAutoW=true;
	bool bInited = false;
	float sDelay = 0.1f, sSpeed = 0.25f;
	Obj_AI_Base*localplayer=nullptr;
	TospikThresh() { strcpy(classname, "TospikThresh"); strcpy(Heroname, "Thresh");   strcpy(version, "0.0.1"); };
	~TospikThresh() {};
	void onProcessSpell(SpellData*spelldata, SpellCastInfo*spellcastinfo)
	{

	}
	void onStart()
	{
		localplayer = ObjectManager::GetPlayer();
		std::string name = *localplayer->GetHeroName();

		if (localplayer)
			if (!strcmp(name.c_str(), Heroname) == 0)
				return;

		bInited = true;
		ENGINE_MSG("Loaded Component: %s Hero :  %s  : Version: %s\n", classname, Heroname, version);

	}

	void onUpdate()
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		localplayer = ObjectManager::GetPlayer();

		if (bAutoW)
			autoWLogic();
	}

	void autoWLogic()
	{
		auto xdrkek = ObjectManager::GetHeroes(ObjectManager::Allies, 950);

		for (auto teamheroobj : xdrkek)
		{
			auto enemies = ObjectManager::GetHeroes(ObjectManager::Enemies, 700, (Obj_AI_Base*)teamheroobj);
			if (enemies.size() <= 0)
				continue;

			auto hero = (Obj_Hero*)teamheroobj;
			if (hero->IsValidTarget(950) && hero->GetHealthPercent() < 35 )
			{
				localplayer->GetSpellbook()->CastSpell(SpellSlot::W, RVector3(0, 0, 0), hero->GetPosition());
				break;
			}
		}
	}
	void onRender()
	{
		if (!bInited)
			return;
		if (!bEnabled)
			return;

		if (bAutoQ)
		{
			
		
			if (targetselector->target != nullptr   && GetAsyncKeyState(VK_SPACE))
			{

				


				D3DCOLOR predcolor = D3DCOLOR_ARGB(255, 255, 255, 255);
				auto pred = new Prediction(new LinePrediction());
				RVector3 Predict = pred->LinePred->Calculate(targetselector->target,1100,1900,0.500);//FastPrediction(localplayer->GetPosition(),target,sDelay,sSpeed);
				if (!pred->IsCollisioned(Prediction::CollisionType::Minion, targetselector->target->GetPosition(), 100))
				{
					predcolor = D3DCOLOR_ARGB(255, 0, 255, 0);
					

					if (Predict != RVector3(0, 0, 0))
						if (targetselector->target->IsValidTarget(1100))
							localplayer->GetSpellbook()->CastSpell(SpellSlot::Q, RVector3(0, 0, 0), Predict);

						if (targetselector->target->HasBuff("threshq", true))
						{
							localplayer->GetSpellbook()->CastSpell(SpellSlot::Q);
						}
				}
				if (targetselector->target->IsValidTarget(400) && !targetselector->target->HasBuff("threshq", true))
				{
					auto pred = new Prediction(new LinePrediction());
					auto kaciyor = localplayer->Distance(targetselector->target->GetPosition()) < targetselector->target->Distance(*Game::Cursor()->GetPosition());
				
					RVector3 Predict = pred->LinePred->Calculate(targetselector->target,400, 1800, 0.550);
					auto x = localplayer->GetPosition().x - targetselector->target->GetPosition().x;
					auto y = localplayer->GetPosition().z - targetselector->target->GetPosition().z;

					RVector3 vec = RVector3(localplayer->GetPosition().x + x, localplayer->GetPosition().y , localplayer->GetPosition().z +y);
					if(Predict != RVector3(0, 0, 0))
					if (kaciyor) {
						localplayer->GetSpellbook()->CastSpell(SpellSlot::E, RVector3(0, 0, 0), vec);
					}
					else {
						localplayer->GetSpellbook()->CastSpell(SpellSlot::E, RVector3(0, 0, 0), Predict);
					}

				}
				if (targetselector->target->HasBuff("threshq", true)) {
					//Bütün takým arkadaþlarýmý çek
					for (auto teamheroobj : ObjectManager::GetHeroes(ObjectManager::Allies))
					{
						auto hero = (Obj_Hero*)teamheroobj;
						if (hero->IsValidTarget(950) && hero->GetPosition().Distance(localplayer->GetPosition()) > 300)
						{
							localplayer->GetSpellbook()->CastSpell(SpellSlot::W, RVector3(0, 0, 0), hero->GetPosition());
							break;
						}
					}
				}
				if (localplayer->GetHealthPercent() < 50) {
					localplayer->GetSpellbook()->CastSpell(SpellSlot::W, RVector3(0, 0, 0), localplayer->GetPosition());
				}

			} // q end




		}
	}
	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::TreeNode("Thresh"))
		{
			ui::Checkbox("Enabled", &bEnabled);
			ui::Checkbox("Auto Combo", &bAutoQ);
			ui::Checkbox("Auto W", &bAutoW);
			ImGui::TreePop();
		}
	}
};
#endif