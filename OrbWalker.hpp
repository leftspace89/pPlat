#pragma once
#ifndef ORBWALKER
#define ORBWALKER

class OrbWalker : public pComponent
{
public:
	bool bDrawADRange = true,bKite = true,bOrbWalker=true,bHumanizer=false,bRightClick=false,bEvade=true;
	float evadeMultipler = 5.0f;
	float HoldRadius = 100;
	float totaldmg = 0;
	int combokey = VK_SPACE, laneclearkey = 0x56, lasthitkey = 0x58, resetkey = VK_CAPITAL;

	OrbWalker() { strcpy(classname, "OrbWalker"); strcpy(version, "0.0.3"); };
	~OrbWalker() {};
	DWORD movetimer, attacktimer;
	float ClickerDelay = 10.0f;
	float pWindMultipler = 1.1f;
	bool attackmove = true;
	Obj_AI_Base*localplayer = nullptr;
	bool EvadeWalkerDisable = false;

	void RightClick()
	{
		if (EvadeWalkerDisable)
			return;
		
		auto cursorpos = *Game::Cursor()->GetPosition();
		if (cursorpos.Distance(ObjectManager::GetPlayer()->GetPosition())< HoldRadius)
			return;

		if (bRightClick)
		{
			POINT CurPos;
			GetCursorPos(&CurPos);
			int X = CurPos.x;
			int Y = CurPos.y;
			mouse_event(MOUSEEVENTF_RIGHTDOWN, X, Y, 0, 0);
			Sleep(10);
			mouse_event(MOUSEEVENTF_RIGHTUP, X, Y, 0, 0);
		}
		else
		{
			if (ObjectManager::GetPlayer()->IssueOrder(Game::Cursor()->GetPosition(),nullptr, GameObjectOrder::MoveTo))
			{

			}
		}


	}
	void ResetMoveTimer()
	{
		movetimer = clock();
	}
	void ResetAttackTimer()
	{
		attacktimer = clock();
	}
	double CalcWindup()
	{
		typedef float(__cdecl* fnGetAttackDelay)(GameObject* pObj, int index);
		fnGetAttackDelay stGet = reinterpret_cast<fnGetAttackDelay>(MAKE_RVA(Offsets::SpellHelper::ComputeCharacterAttackCastDelay)); // 83 ec ? 53 8b 5c ? ? 8b cb 56 ---- 2. ÝNDEX 57 8B 7C 24 08 8B 87 ? ? ? ? 8D 8F ? ? ? ?
		float delay = stGet((GameObject*)ObjectManager::GetPlayer(), 1);
		float pDelay = delay * 2.0f;
		//ENGINE_MSG("Windup  %f , pDelay : %f\n", delay, pDelay);
		return pDelay;
	}
	double CalcMoveDelay()
	{
		return (clock() - movetimer) / (double)CLOCKS_PER_SEC;
	}
	double CalcAttackDelay()
	{
		return (clock() - attacktimer) / (double)CLOCKS_PER_SEC;
	}

	bool MoveReady()
	{
		auto x = CalcMoveDelay();
		if (x > ClickerDelay)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool AttackReady()
	{
		if (CalcAttackDelay() > (ObjectManager::GetPlayer()->CalcAttackTime()*pWindMultipler))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	Obj_Minion *GetClosestMinion()
	{
		float LastDist = FLT_MAX;
		Obj_Minion*target = nullptr;
		auto local = ObjectManager::GetPlayer();
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies))
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->IsValidTarget())
				continue;


			float tmpdist = curobj->GetPosition().Distance(local->GetPosition());
			if (tmpdist < LastDist)
			{
				LastDist = tmpdist;
				target = curobj;
			}
		}
		return target;
	}

	Obj_Minion *GetClosestTeamMinion()
	{
		float LastDist = FLT_MAX;
		Obj_Minion*target = nullptr;
		auto local = ObjectManager::GetPlayer();
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Allies))
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->isValid())
				continue;
			float tmpdist = curobj->GetPosition().Distance(local->GetPosition());
			if (tmpdist < LastDist)
			{
				LastDist = tmpdist;
				target = curobj;
			}
		}
		return target;
	}


	Obj_Hero *GetMouseNearHero()
	{
		float LastDist = FLT_MAX;
		Obj_Hero*target = nullptr;
		auto local = ObjectManager::GetPlayer();
		for (auto objptr : ObjectManager::GetHeroes(ObjectManager::ObjectTeam::Enemies))
		{
			auto curobj = (Obj_Hero*)objptr;
			if (!curobj->IsValidTarget())
				continue;
			auto cursorpos = *Game::Cursor()->GetPosition();
			float tmpdist = cursorpos.Distance(local->GetPosition());
			if (tmpdist < LastDist)
			{
				LastDist = tmpdist;
				target = curobj;
			}
		}

		return target;
	}
	Obj_Minion *GetLowestHPMinion()
	{
		float lasthealth = FLT_MAX;
		Obj_Minion*target = nullptr;
		auto local = ObjectManager::GetPlayer();
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies))
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->IsValidTarget())
				continue;
			float HP = *curobj->GetHealth();
			
			if (reinterpret_cast<Obj_Minion*>(curobj)->IsLastHitable())
			{
				lasthealth = HP;
				target = curobj;
				break;
			}
				

			if (HP < lasthealth )
			{
				lasthealth = HP;
				target = curobj;
			}
		}
		return target;
	}

	bool HaveNearAllyMinion()
	{
		auto min = GetClosestTeamMinion();
		auto dist = min->GetPosition().Distance(ObjectManager::GetPlayer()->GetPosition());
		return dist < 250;
	}
	bool HaveNearAllyTurret()
	{
		return false;
		/*
		auto min = GetClosestTeamTurret();
		auto dist = min->GetPosition().Distance(ObjectManager::GetPlayer()->GetPosition());
		
		return dist < 430;
		*/
	}
	void Orbwalk(Obj_AI_Base* object, bool LastHit)
	{
		if (EvadeWalkerDisable)
			return;
		if (object == nullptr)
		{
			RightClick();
			return;
		}
		auto local = ObjectManager::GetPlayer();
		if (!object->IsValidTarget())
		{
			RightClick();
			return;
		}
		if (AttackReady())
		{

			if (local->IssueOrder(&object->GetPosition(),object, GameObjectOrder::AttackUnit))
			{
				//ENGINE_MSG("ATTACK\n");
				ResetAttackTimer();
				ResetMoveTimer();
				attackmove = true;
			}

		}
		if (!AttackReady())
		{
			if (CalcAttackDelay() > CalcWindup())
			{
				if (attackmove)
				{
					//ENGINE_MSG("rig\n");
					RightClick();
					ResetMoveTimer();
					attackmove = false;
				}
				else
				{
					if (MoveReady())
					{
						//ENGINE_MSG("rig\n");
						RightClick();
						ResetMoveTimer();
						attackmove = false;
					}
				}
			}
		}
		if (MoveReady())
		{
			//ENGINE_MSG("rig\n");
			RightClick();
			ResetMoveTimer();
			attackmove = false;
		}


	}

	struct TargetInfo_t
	{
	public:
		bool success;
		GameObject *target;
	};

	TargetInfo_t GetLaneClearTarget()
	{

		auto lowestHpMinion = GetLowestHPMinion();
		if (lowestHpMinion != nullptr)
		{
		
			return TargetInfo_t{ true, lowestHpMinion };
		}

	
		return TargetInfo_t{ false, nullptr };
	}



	TargetInfo_t GetLastHitTarget()
	{
		
			float lasthealth = FLT_MAX;
			Obj_Minion*target = nullptr;
			auto local = ObjectManager::GetPlayer();
			for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies))
			{
				auto curobj = (Obj_Minion*)objptr;
				if (!curobj->IsValidTarget())
					continue;

				if (curobj->IsLastHitable())
				{
					return TargetInfo_t{ true,curobj};
				}
				else
				{
					ENGINE_MSG("Not LastHit : %f , dmg : %f \n", *curobj->GetHealth(),curobj->GetAttackDamageOnThis());
				}
			
			}
		

		return TargetInfo_t{ false,nullptr };
	}
	enum class SpellSlot
	{
		Unknown = -1,
		Q = 0,
		W = 1,
		E = 2,
		R = 3,
		Summoner1 = 4,
		Summoner2 = 5,
		Item1 = 6,
		Item2 = 7,
		Item3 = 8,
		Item4 = 9,
		Item5 = 10,
		Item6 = 11,
		Trinket = 12,
		Recall = 13
	};
	/*bool Spellbook::CastSpell(SpellSlot slot, bool triggerEvent)
	{
		return this->CastSpell(slot, Vector3f(0, 0, 0), Vector3f(0, 0, 0), ObjectManager::GetPlayer()->GetNetworkId());
	}*/

	
	

	virtual void onStart()
	{
		ENGINE_MSG("Loaded Component: %s Version: %s\n", classname, version);

		localplayer = ObjectManager::GetPlayer();
	}

	virtual void onUpdate()
	{
		if (!bOrbWalker)
			return;

		localplayer = ObjectManager::GetPlayer();
		if (localplayer == nullptr)
			return;

		if (bKite)
		{
			LastHitLogic();

			if (GetAsyncKeyState(combokey) < 0)
			{
			
				if (targetselector->target !=nullptr)
				{
						Orbwalk(targetselector->target, false);
				}
				else
				{
					Orbwalk(nullptr, false); // hedef yoksa düz yürü
				}
			}

	
			if (GetAsyncKeyState(laneclearkey))//V tusu
			{
				auto target = GetLaneClearTarget();
				if (target.success)
				{
					Orbwalk((Obj_AI_Base*)target.target, false);
				}
				else {
					Orbwalk(nullptr, false);
				}
			}
		}
	}
	float LastAATick=0, Tick2=0;
	bool Attacking = false;
	float lasttick=0, lastmovetick=0;
	struct LSpellInfo
	{
	
		RVector3 startPos;
		RVector3 endPos;
		float castTime;
		float missileSpeed;
		float missileWidth;
		float castRange;
		float castRadius;
		float spellRadius;
		DWORD pushedTime;
		Obj_AI_Base*sender;
	};
	std::vector<LSpellInfo*>ProcessedSpells;

	RVector3 getSpellPosition(LSpellInfo*sinfo,float extraspeed)
	{
		float timeTraveled = (((float)GetTickCount() - (float)sinfo->pushedTime) - (sinfo->castTime / 2)) / 1000 * extraspeed;
		if (timeTraveled < 0)
			timeTraveled = 0;

		float speed = sinfo->missileSpeed;
		RVector3 orientation = RVector3(sinfo->endPos - sinfo->startPos).Normalize();

		//ENGINE_MSG("Speed : %f , orient : %f %f %f  timetravel: %f\n", speed, orientation.x, orientation.y, orientation.z, timeTraveled);

		return sinfo->startPos + timeTraveled * speed * orientation + sinfo->missileWidth * orientation;
	}
	Obj_AI_Base*minionLastHittable()
	{
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies)) // get all enemy minions
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->IsValidTarget()) // check is valid range.
				continue;

			RVector3 pos2d, spell2d, spellStart2d;
			render.r3dWorldToScreen(&curobj->GetPosition(), &pos2d);

			float hpPred = *curobj->GetHealth();
			for (auto mInfo : ProcessedSpells) // get all casted Spells
			{
				if (mInfo->sender == nullptr)
					continue;
				if (*mInfo->sender->GetTeam() == *curobj->GetTeam())
					continue;

				auto EndPos = mInfo->endPos;
				auto startPos = mInfo->startPos;
				RVector3 spos = getSpellPosition(mInfo,5.0f);
				render.r3dWorldToScreen(&spos, &spell2d); // missile cur pos
				render.r3dWorldToScreen(&startPos, &spellStart2d);// missile startpos
				if (EndPos.Distance(curobj->GetPosition())<50)// if target spell or whatever will hit our minion 
				{
					float incomingdmg = *mInfo->sender->GetCharData()->GetBaseAttackDamage() + *mInfo->sender->GetCharData()->GetBonusAttackDamage(); // minion dmg but We need Sender Damage.
					hpPred -= incomingdmg; // decrease our minion health by incoming damage
					render.DrawLine(spellStart2d.x, spellStart2d.y, spell2d.x, spell2d.y, 10, D3DCOLOR_ARGB(255, 0, 0, 255));
				}

			}

			if (hpPred <= 0 || curobj->IsLastHitable()) // can I Last Hit that Health ? 
				render.DrawString(pos2d.x, pos2d.y + 10, D3DCOLOR_ARGB(255, 0, 255, 0), DT_LEFT, 15, "Health: %.f\n HP Pred %.f", *curobj->GetHealth(), hpPred);
			else
				render.DrawString(pos2d.x, pos2d.y + 10, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "Health: %.f\n HP Pred %.f", *curobj->GetHealth(), hpPred);

			if (hpPred <= 0 || curobj->IsLastHitable()) // can I Last Hit that Health ? 
				return curobj;

		}
		return nullptr;
	}

	Obj_AI_Base*GetLaneClearMinionEx()
	{
		float lastHealth = FLT_MAX;
		Obj_AI_Base*target = nullptr;
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies)) // get all enemy minions
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->IsValidTarget()) // check is valid range.
				continue;

			if (curobj->IsLastHitable()) // can I Last Hit that Health ? 
				return curobj;

			if (*curobj->GetHealth() <= lastHealth)
			{
				target = curobj;
				lastHealth = *curobj->GetHealth();
			}

		}
		return target;
	}
	Obj_AI_Base*GetLastHitMinionEx()
	{
		for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies)) // get all enemy minions
		{
			auto curobj = (Obj_Minion*)objptr;
			if (!curobj->IsValidTarget()) // check is valid range.
				continue;

			if ( curobj->IsLastHitable()) // can I Last Hit that Health ? 
				return curobj;

		}
		return nullptr;
	}
	void LastHitLogic()
	{
		if (EvadeWalkerDisable)
			return;
		if (GetAsyncKeyState(lasthitkey))
		{
			auto minos = GetLastHitMinionEx();

			if (minos != nullptr)
			{
				localplayer->IssueOrder(&minos->GetPosition(), minos, GameObjectOrder::AttackUnit);
			}
			else
			{
				RightClick();
			}
		}
	}
	void LaneClearLogic()
	{
		if (GetAsyncKeyState(laneclearkey))
		{
			
		}
	}
	bool PointOnLineSegmentEv(D3DXVECTOR2 pt1, D3DXVECTOR2 pt2, D3DXVECTOR2 pt, double epsilon = 0.001)
	{
		if (pt.x - std::fmax(pt1.x, pt2.x) > epsilon ||
			std::fmin(pt1.x, pt2.x) - pt.x > epsilon ||
			pt.y - std::fmax(pt1.y, pt2.y) > epsilon ||
			std::fmin(pt1.y, pt2.y) - pt.y > epsilon)
			return false;

		if (abs(pt2.x - pt1.x) < epsilon)
			return abs(pt1.x - pt.x) < epsilon || abs(pt2.x - pt.x) < epsilon;
		if (abs(pt2.y - pt1.y) < epsilon)
			return abs(pt1.y - pt.y) < epsilon || abs(pt2.y - pt.y) < epsilon;

		double x = pt1.x + (pt.y - pt1.y) * (pt2.x - pt1.x) / (pt2.y - pt1.y);
		double y = pt1.y + (pt.x - pt1.x) * (pt2.y - pt1.y) / (pt2.x - pt1.x);

		return abs(pt.x - x) < epsilon || abs(pt.y - y) < epsilon;
	}
	void EvadeLogic()
	{
		RVector3 lastResult(0, 0, 0);
		DWORD lastMiss = 0;
		float lastMisspeed = 1000;
		for (auto mInfo : ProcessedSpells) // get all casted Spells
		{
			if (mInfo->sender == nullptr)
				continue;
			//if (*mInfo->sender->GetTeam() == *localplayer->GetTeam())
			//	continue;

			RVector3 pos2d, spell2d, spellStart2d, spellend2d, local2d;

			RVector3 spos = getSpellPosition(mInfo, evadeMultipler);
			render.r3dWorldToScreen(&spos, &spell2d); // missile cur pos
			render.r3dWorldToScreen(&mInfo->startPos, &spellStart2d);// missile startpos
			render.r3dWorldToScreen(&mInfo->endPos, &spellend2d);// missile end
			render.r3dWorldToScreen(&localplayer->GetPosition(), &local2d);// missile end

			render.DrawLine(spellStart2d.x, spellStart2d.y, spell2d.x, spell2d.y, mInfo->missileWidth, D3DCOLOR_ARGB(100, 255, 255, 255));
			if (mInfo->spellRadius > 0)
			{

				if (isPointInCircle(spellend2d.x, spellend2d.y, mInfo->spellRadius, local2d.x, local2d.y))
				{
					RVector3 orientation = RVector3(mInfo->endPos - mInfo->startPos).perpendicularTo();
					lastMisspeed = mInfo->castTime * 10;
					lastResult = localplayer->GetPosition() + mInfo->spellRadius * orientation;
					lastMiss = GetTickCount();
					RVector3 from2d, to2d;
					render.r3dWorldToScreen(&localplayer->GetPosition(), &from2d);
					render.r3dWorldToScreen(&lastResult, &to2d);
#ifdef _DEBUG
					render.DrawLine(from2d.x, from2d.y, to2d.x, to2d.y, 15, D3DCOLOR_ARGB(255, 0, 0, 255));
					ENGINE_MSG("OrbWalker Disabled : %f\n", lastMisspeed);
					render.DrawCircle((int)spellend2d.x, (int)spellend2d.y, mInfo->spellRadius, 50, D3DCOLOR_ARGB(255, 255, 0, 0));
#endif
					EvadeWalkerDisable = true;
					localplayer->IssueOrder(&lastResult, nullptr, GameObjectOrder::MoveTo);
	
				}
				render.DrawCircle((int)spellend2d.x, (int)spellend2d.y, mInfo->spellRadius, 50, D3DCOLOR_ARGB(255, 255, 0, 0));
			}
			else
			{ 
			
			if(PointOnLineSegmentEv(D3DXVECTOR2(spellStart2d.x, spellStart2d.y), D3DXVECTOR2(spellend2d.x, spellend2d.y), D3DXVECTOR2(local2d.x, local2d.y), mInfo->missileWidth * 2))
			{

				RVector3 orientation = RVector3(mInfo->endPos - mInfo->startPos).perpendicularTo();
				lastMisspeed = mInfo->castTime * 10;
				lastResult = localplayer->GetPosition() + orientation;
				lastMiss = GetTickCount();
				RVector3 from2d, to2d;
				render.r3dWorldToScreen(&localplayer->GetPosition(), &from2d);
				render.r3dWorldToScreen(&lastResult, &to2d);
#ifdef _DEBUG
				render.DrawLine(from2d.x, from2d.y, to2d.x, to2d.y, 15, D3DCOLOR_ARGB(255, 0, 0, 255));
				ENGINE_MSG("OrbWalker Disabled : %f\n", lastMisspeed);
#endif
				EvadeWalkerDisable = true;
				localplayer->IssueOrder(&lastResult, nullptr, GameObjectOrder::MoveTo);
			}
			}
				
			
		}

		if (GetTickCount() - lastMiss > lastMisspeed)
		{
			EvadeWalkerDisable = false;
			//ENGINE_MSG("OrbWalker Enabled \n");
		}
	}
	bool isInRectangle(double centerX, double centerY, double radius,
		double x, double y)
	{
		return x >= centerX - radius && x <= centerX + radius &&
			y >= centerY - radius && y <= centerY + radius;
	}

	 bool isPointInCircle(double centerX, double centerY,
		double radius, double x, double y)
	{
		if (isInRectangle(centerX, centerY, radius, x, y))
		{
			double dx = centerX - x;
			double dy = centerY - y;
			dx *= dx;
			dy *= dy;
			double distanceSquared = dx + dy;
			double radiusSquared = radius * radius;
			return distanceSquared <= radiusSquared;
		}
		return false;
	}
	virtual void onRender()
	{
		if (!bOrbWalker ||localplayer==nullptr)
			return;

		auto local = ObjectManager::GetPlayer();
		static int color = 0xCC007F00;
		if (targetselector->target !=nullptr)
		{
			int pcolor = 0xFF0000;
			lol::r3dDrawCircle.Call(&targetselector->target->GetPosition(), targetselector->target->GetAttackRange(), &pcolor, 0, 0, 0, 1);
		}

		
		if (bEvade)
		{

			EvadeLogic();
		}


	
			//RVector3 lastResult(0, 0, 0);
			//DWORD lastMiss = 0;
			//float lastMisspeed = 1000;
			//for (auto mInfo : ProcessedSpells) // get all casted Spells
			//{
			//	if (mInfo->sender == nullptr)
			//		continue;
		

			//	RVector3 pos2d, spell2d, spellStart2d, spellend2d, local2d;

			//	RVector3 spos = getSpellPosition(mInfo, evadeMultipler);
			//	render.r3dWorldToScreen(&spos, &spell2d); // missile cur pos
			//	render.r3dWorldToScreen(&mInfo->startPos, &spellStart2d);// missile startpos
			//	render.r3dWorldToScreen(&mInfo->endPos, &spellend2d);// missile end
			//	render.r3dWorldToScreen(&localplayer->GetPosition(), &local2d);// missile end
			//
			//	if (isPointInCircle(spellend2d.x, spellend2d.y, mInfo->spellRadius, local2d.x, local2d.y))
			//	{
			//		RVector3 orientation = RVector3(mInfo->endPos - mInfo->startPos).perpendicularTo();
			//		lastMisspeed = mInfo->castTime * 10;
			//		lastResult = localplayer->GetPosition() +mInfo->spellRadius * orientation;
			//		lastMiss = GetTickCount();
			//		RVector3 from2d, to2d;
			//		render.r3dWorldToScreen(&localplayer->GetPosition(), &from2d);
			//		render.r3dWorldToScreen(&lastResult, &to2d);
			//		render.DrawLine(from2d.x, from2d.y, to2d.x, to2d.y, 15, D3DCOLOR_ARGB(255, 0, 0, 255));
			//		ENGINE_MSG("OrbWalker Disabled : %f\n", lastMisspeed);
			//		EvadeWalkerDisable = true;
			//		localplayer->IssueOrder(&lastResult, nullptr, GameObjectOrder::MoveTo);
			//		render.DrawCircle((int)spellend2d.x, (int)spellend2d.y, mInfo->spellRadius, 50, D3DCOLOR_ARGB(255, 255, 0, 0));
			//	}
			//	
			//	else
			//		render.DrawCircle((int)spellend2d.x, (int)spellend2d.y, mInfo->spellRadius, 50, D3DCOLOR_ARGB(255, 255, 255, 255));
			//	//ENGINE_MSG("Position %.f %.f %.f\n", mInfo->endPos.x, mInfo->endPos.y, mInfo->endPos.z);
			//}
		

		if(bDrawADRange)
		lol::r3dDrawCircle.Call(&localplayer->GetPosition(), localplayer->GetAttackRange(), &color, 0, 0, 0, 1);

		/*Cleaner*/
		for (size_t i = 0; i < ProcessedSpells.size(); i++)
		{
			auto spell = ProcessedSpells[i];
			if (GetTickCount() - spell->pushedTime > 1000) // If Lifetime > 2000 erase that shit
			ProcessedSpells.erase(ProcessedSpells.begin() + i);
		}
		/*Cleaner*/
	

	


		//for (auto objptr : ObjectManager::GetMinions(ObjectManager::ObjectTeam::Enemies))
		//{
		//	auto curobj = (Obj_Minion*)objptr;
		//	if (!curobj->IsValidTarget())
		//		continue;

		//

		//	RVector3 pos2d;
		//	render.r3dWorldToScreen(&curobj->GetPosition(), &pos2d);
		//	if (curobj->IsLastHitable())
		//	{
		//		render.DrawString(pos2d.x, pos2d.y+10, D3DCOLOR_ARGB(255, 0, 255, 0), DT_LEFT, 15, "Health: %.f\nDamageThis: %.f", *curobj->GetHealth(), curobj->GetAttackDamageOnThis());
		//	}
		//	else
		//	{
		//		render.DrawString(pos2d.x, pos2d.y+10, D3DCOLOR_ARGB(255, 255,255, 255), DT_LEFT, 15, "Health: %.f\nDamageThis: %.f", *curobj->GetHealth(), curobj->GetAttackDamageOnThis());
		//	}

		//}

	}

	//const char * const blackListSpells[] = { "Minion","minion","BasicAttack"};
	
	
	void onProcessSpell(SpellData*spelldata, SpellCastInfo*spellcastinfo)
	{
	/*	if (*ObjectManager::GetUnitByIndex(*spellcastinfo->GetSenderIndex())->GetTeam() == *localplayer->GetTeam())
			return;*/

		auto snd = (Obj_AI_Base*)ObjectManager::GetUnitByIndex(*spellcastinfo->GetSenderIndex());


		if (snd != nullptr)
			if (!strstr(snd->GetName().c_str(), "minion") == 0)
				return;

		const char* const blackListSpells[] = {
		"Minion",
		"minion",
		"BasicAttack",
		"Recall",
		"Potion",
	};


		for (size_t i = 0; i < sizeof(blackListSpells) / sizeof(blackListSpells[0]); i++)
		{
			if (!strstr(spelldata->GetNameFF(), blackListSpells[i]) == 0)
				return;
		}

		



	


		auto sInfo = new LSpellInfo;
		sInfo->castTime = *spelldata->GetcastTime();
		sInfo->missileSpeed = *spelldata->GetmissileSpeed();
		sInfo->missileWidth = *spelldata->GetmissileWidth();
		sInfo->startPos = *spellcastinfo->GetStart();
		sInfo->endPos = *spellcastinfo->GetEnd();
		sInfo->castRange = *spelldata->GetcastRange();
		sInfo->castRadius = *spelldata->GetcastRadius();
		sInfo->pushedTime = GetTickCount();
		sInfo->spellRadius = *spelldata->GetspellRadius();
		sInfo->sender = (Obj_AI_Base*)ObjectManager::GetUnitByIndex(*spellcastinfo->GetSenderIndex());
		ProcessedSpells.push_back(sInfo);
		
		ENGINE_MSG("Spell : %s : %p , sender : %s\n", spelldata->GetNameFF(), spelldata, snd->GetName().c_str());

	
	}
	virtual void onMenu()
	{
		if (ImGui::TreeNode("OrbWalker"))
		{
			ui::Checkbox("Enabled", &bOrbWalker);
			ui::Checkbox("Auto Kite", &bKite);
			ui::Checkbox("Right Click", &bRightClick);
			ui::Checkbox("Draw Attack Range", &bDrawADRange);
			if (ImGui::TreeNode("Evade"))
			{
				ui::Checkbox("Evade LineSkills", &bEvade);
				ui::SliderFloat("Evade Speed", &evadeMultipler, 0, 20);
				ImGui::TreePop();
			}

			ui::SliderFloat("Hold Radius", &HoldRadius, 100, 250);
			ui::SliderFloat("Move Delay", &pWindMultipler, 0, 10);
			ui::SliderFloat("AD Damage", &totaldmg, 0, 1500);

			ui::Hotkey("Combo", &combokey);
			ui::Hotkey("Lane Clear", &laneclearkey);
			ui::Hotkey("Last Hit", &lasthitkey);
			ui::Hotkey("Reset Target", &resetkey);
		   ImGui::TreePop();
		}
		if (ImGui::TreeNode("Humanizer"))
		{
			ui::Checkbox("Enabled", &bHumanizer);
			
			ImGui::TreePop();
		}
	}
private:

};
#endif