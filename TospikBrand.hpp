#pragma once
#ifndef TOSPIKBRAND
#define TOSPIKBRAND
#include "LBuffInstance.h"
class TospikBrand : public pComponent
{
public:
	bool bEnabled = true, bAutoQ = true;
	bool bInited = false;
	float sDelay = 0.1f, sSpeed = 0.25f;
	Obj_AI_Base*localplayer = nullptr;
	TospikBrand() { strcpy(classname, "TospikBrand"); strcpy(Heroname, "Brand"); strcpy(version, "0.0.1"); };
	~TospikBrand() {};
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

	
	bool LogicQuse(Obj_AI_Base *t)
	{

		auto _E = localplayer->GetSpellbook()->GetSpell(static_cast<uint>(SpellSlot::E));
		auto _W = localplayer->GetSpellbook()->GetSpell(static_cast<uint>(SpellSlot::W));
		auto _Q = localplayer->GetSpellbook()->GetSpell(static_cast<uint>(SpellSlot::Q));

		float gTime = (float)GetTickCount() / 1000;

		if (t->HasBuff("brandablaze",false))
			return true;
		else if (*_E->GetCooldownExpires() - gTime + 2 >= *_Q->GetCooldown() && *_W->GetCooldownExpires() - gTime + 2 >= *_Q->GetCooldown())
			return true;
		else
			return false;
	}

	void onRender()
	{
		if (!bInited)
			return;

		if (!bEnabled)
			return;

		if (!localplayer)
			return;
	/*	if (GetAsyncKeyState(VK_LSHIFT))
		{
			auto _Q = localplayer->GetSpellbook()->GetSpell(static_cast<uint>(SpellSlot::Q));
			ENGINE_MSG("Q %p", _Q);
		}*/
		if (bAutoQ)
		{
			if (targetselector->target != nullptr && GetAsyncKeyState(VK_SPACE))
			{

				/*W */
				auto W_Pred = new Prediction(new CirclePrediction());
				RVector3 Predict_W = W_Pred->CircPred->Calculate(targetselector->target, 900, 1800, 250, 0.850);
				if (Predict_W != RVector3(0, 0, 0))
					localplayer->GetSpellbook()->CastSpell(SpellSlot::W, RVector3(0, 0, 0), Predict_W);

				/*W */

				/*Q */
				auto Q_Pred = new Prediction(new LinePrediction());
				RVector3 Predict_Q = Q_Pred->LinePred->Calculate(targetselector->target, 1100, 1600, 0.250);
				if (!Q_Pred->IsCollisioned(Prediction::CollisionType::Minion, targetselector->target->GetPosition(), 100))
				{
					if (Predict_Q != RVector3(0, 0, 0))
						localplayer->GetSpellbook()->CastSpell(SpellSlot::Q, RVector3(0, 0, 0), Predict_Q);

				}
				/*Q */
				

			}

		}
	}
	void onMenu()
	{
		if (!bInited)
			return;

		if (ImGui::TreeNode("Brand"))
		{
			ui::Checkbox("Enabled", &bEnabled);
			ui::Checkbox("Auto Combo", &bAutoQ);
			ImGui::TreePop();
		}
	}
};
#endif