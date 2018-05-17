#pragma once
#ifndef TOSPIKCAIT
#define TOSPIKCAIT
#include "LBuffInstance.h"
class TospikCait : public pComponent
{
public:
	bool bEnabled = true, bAutoQ = true;
	bool bInited = false;
	float sDelay = 0.1f, sSpeed = 0.25f;
	Obj_AI_Base*localplayer = nullptr;
	TospikCait() { strcpy(classname, "TospikCait"); strcpy(Heroname, "Caitlyn");  strcpy(version, "0.0.1"); };
	~TospikCait() {};
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
	}

	
	void onRender()
	{
		if (!bInited)
			return;
		if (!bEnabled)
			return;

		if (bAutoQ)
		{

			if (targetselector->target != nullptr  && GetAsyncKeyState(VK_SPACE))
			{
				D3DCOLOR predcolor = D3DCOLOR_ARGB(255, 255, 255, 255);
				auto pred = new Prediction(new LinePrediction());
				RVector3 Predict = pred->LinePred->Calculate(targetselector->target,600,1600,0.150);//FastPrediction(localplayer->GetPosition(),target,sDelay,sSpeed);
				if (!pred->IsCollisioned(Prediction::CollisionType::Minion, targetselector->target->GetPosition(), 100))
				{
					predcolor = D3DCOLOR_ARGB(255, 0, 255, 0);


					if (targetselector->target->IsValidTarget(600))
						if (Predict != RVector3(0, 0, 0))
						localplayer->GetSpellbook()->CastSpell(SpellSlot::E, RVector3(0, 0, 0), Predict);

				}

				if (targetselector->target->IsValidTarget(1250))
				{

					auto pred = new Prediction(new LinePrediction());
				

					RVector3 Predict = pred->LinePred->Calculate(targetselector->target,1250,2200,0.555f);
					if (Predict != RVector3(0, 0, 0))
					localplayer->GetSpellbook()->CastSpell(SpellSlot::Q, RVector3(0, 0, 0), Predict);
				}
				if (targetselector->target->IsValidTarget(800))
				{
					auto pred = new Prediction(new LinePrediction());
					auto kaciyor = localplayer->Distance(targetselector->target->GetPosition()) < targetselector->target->Distance(*Game::Cursor()->GetPosition());

					RVector3 Predict = pred->LinePred->Calculate(targetselector->target,800,1600,0.625);
					if(Predict != RVector3(0, 0, 0))
					localplayer->GetSpellbook()->CastSpell(SpellSlot::W, RVector3(0, 0, 0), Predict);
				}

				if (targetselector->target->IsValidTarget(2000) && *targetselector->target->GetHealth() <=350)
				{

					localplayer->GetSpellbook()->CastSpell(SpellSlot::R, targetselector->target);
				}

			} // q end




		}
	}
	void onMenu()
	{
		if (!bInited)
			return;
		if (ImGui::TreeNode("Caitlyn"))
		{
			ui::Checkbox("Enabled", &bEnabled);
			ui::Checkbox("Auto Combo", &bAutoQ);
			ImGui::TreePop();
		}
	}
};
#endif