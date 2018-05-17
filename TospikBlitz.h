#pragma once
#ifndef TOSPIKBLITZ
#define TOSPIKBLITZ
#include "LBuffInstance.h"
class TosbikBlitz : public pComponent
{
public:
	bool bInited = false;
	bool bEnabled = true,bAutoQ=true;
	float sDelay = 0.1f, sSpeed = 0.25f;

	Obj_AI_Base * localplayer = nullptr;
	TosbikBlitz() { strcpy(classname, "TosbikBlitz"); strcpy(Heroname, "Blitzcrank"); strcpy(version, "0.0.1"); };
	~TosbikBlitz() {};
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

	D3DXVECTOR2 findVel(const D3DXVECTOR2& aPos, const D3DXVECTOR2& bPos, float speed) {
		D3DXVECTOR2 disp = bPos - aPos;
		float distance = sqrt(disp.x*disp.x + disp.y*disp.y); // std::hypot(disp.x, disp.y) if C++ 11
		return disp * (speed / distance);
	}
	
	//std::vector<D3DXVECTOR2> CutPath(this List<Vector2> path, float distance)
	//{
	//	std::vector<D3DXVECTOR2>result;
	//	auto Distance = distance;
	//	if (distance < 0)
	//	{
	//		path[0] = path[0] + distance * (path[1] - path[0]).Normalized();
	//		return path;
	//	}

	//	for (var i = 0; i < path.Count - 1; i++)
	//	{
	//		var dist = path[i].Distance(path[i + 1]);
	//		if (dist > Distance)
	//		{
	//			result.Add(path[i] + Distance * (path[i + 1] - path[i]).Normalized());
	//			for (var j = i + 1; j < path.Count; j++)
	//			{
	//				result.Add(path[j]);
	//			}

	//			break;
	//		}
	//		Distance -= dist;
	//	}
	//	return result.Count > 0 ? result : new List<Vector2>{ path.Last() };
	//}
	
	 float PathLength(std::vector<RVector3*>path)
	{
		auto distance = 0.0f;
		
		for (auto i = 0; i < path.size() - i > 0 ? 1 : 0; i++)
		{
			if (path[i]->x <= 0)
				continue;

			distance += render.r3dDistance(*path[i], *path[i + 1]);//path[i].Distance(path[i + 1]);
		}
		return distance;
	}

	
	
	std::vector<RVector3*> GetWaypoints(Obj_AI_Base* unit)
	{
		std::vector<RVector3*>result;


		result.push_back(&unit->GetServerPosition());
		auto path = unit->GetPathList();
		if (path.size() > 0)
		{
			auto first = path[0];
			if(first->x != -107374176)
			if (render.r3dDistance(*first, *result[0]) > 40)
			{
				result.push_back(first);
			}
			

			for (int i = 1; i < path.size(); i++)
			{
				if (path[i]->x != -107374176)
				result.push_back(path[i]);
			}
		}
		return result;
	}
	#define var auto


	
	
	void onRender()
	{
		if (!bInited)
			return;
		if (!bEnabled)
			return;

		
		//std::pair < string, bool,>ss;
		//std::vector<std::variant<std::pair<wstring, bool>, std::vector<std::pair<wstring, bool>>>> map;
		
		#ifdef path
		auto local = ObjectManager::GetPlayer();

		if (local != nullptr && navdraw)
		{
			auto paths = local->GetPathList();
			if(paths.size()>0)
			{
				RVector3 path1, path2;
				for (size_t i = 0; i < paths.size() -1 ; i++)
				{
					if (render.r3dWorldToScreen(paths[i], &path1))
					{
						
						
					}
					render.r3dWorldToScreen(paths[i + 1], &path2);
					render.DrawLine(path1.x, path1.y, path2.x, path2.y, 10, D3DCOLOR_ARGB(255, 255, 255, 255));
					int color = 0xFFFFFFFF;
					//lol::r3dDrawCircle.Call(paths[i + 1], 50, &color, 0, 0, 0, 1);
					//lol::r3dDrawCircle.Call(paths[i], 50, &color, 0, 0, 0, 1);
					//
						

				}
			}
		}
		#endif
		if (bAutoQ)
		{
		

			if (targetselector->target != nullptr )
			{
				D3DCOLOR predcolor = D3DCOLOR_ARGB(255, 255, 255, 255);

				var pred = new Prediction(new LinePrediction());
				RVector3 Predict = pred->LinePred->Calculate(targetselector->target,925.0f,1750.0f,0.250f);//FastPrediction(ObjectManager::GetPlayer()->GetPosition(),target,sDelay,sSpeed);
				
				if (!pred->IsCollisioned(Prediction::CollisionType::Minion, targetselector->target->GetPosition(), 100))
				{
					predcolor = D3DCOLOR_ARGB(255, 0, 255, 0);
					if (GetAsyncKeyState(VK_SPACE))
					{

						if (targetselector->target->IsValidTarget(925) && Predict !=RVector3(0,0,0))
							ObjectManager::GetPlayer()->GetSpellbook()->CastSpell(SpellSlot::Q, RVector3(0, 0, 0), Predict);

						if (targetselector->target->HasBuff("stun", true))
						{
							ObjectManager::GetPlayer()->GetSpellbook()->CastSpell(SpellSlot::E);
						}
						if (targetselector->target->HasBuff("powerfistslow", false))
							if (targetselector->target->IsValidTarget(600))
								ObjectManager::GetPlayer()->GetSpellbook()->CastSpell(SpellSlot::R); // ult cast

					}
				}
				else
				{
					predcolor = D3DCOLOR_ARGB(255, 255, 0, 0);
				}
					

				if (targetselector->target->IsValidTarget(920))
				{
					RVector3 predict2d, local2d;
					render.r3dWorldToScreen(&Predict, &predict2d);
					render.r3dWorldToScreen(&ObjectManager::GetPlayer()->GetPosition(), &local2d);
					render.DrawLine(local2d.x, local2d.y, predict2d.x, predict2d.y, 5, predcolor);
				}
			


			}
			
		}
	}

	void onMenu()
	{
		if (!bInited)
			return;
		if (ImGui::TreeNode("BlitzCrank"))
		{
			ui::Checkbox("Enabled", &bEnabled);
			ui::Checkbox("Auto Combo", &bAutoQ);
			ImGui::TreePop();
		}
	}
};

#endif 