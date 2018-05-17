#pragma once
class Obj_AI_Base;
class
	DLLEXPORT ObjectManager
{
public:
	
	enum ObjectTeam
	{
		All,
		Allies,
		Enemies
	};
	static GameObject** GetUnitArray();
	static std::vector<GameObject*> GetMinions(ObjectTeam enemy);
	static std::vector<GameObject*> GetHeroes(ObjectTeam type, float range = FLT_MAX, Obj_AI_Base*entity = GetPlayer());
	static Obj_AI_Base* GetPlayer();
	static GameObject*GetUnderMouseObj()
	{
		auto obj = MAKEPTR(Offsets::ObjectManager::UnderMouseObj);
		if (!obj)
			return nullptr;

		if (*reinterpret_cast<GameObject*>(obj)->GetNetworkId() == *reinterpret_cast<GameObject*>(GetPlayer())->GetNetworkId())
			return nullptr;

		if (*reinterpret_cast<GameObject*>(obj)->GetTeam() == *reinterpret_cast<GameObject*>(GetPlayer())->GetTeam())
			return nullptr;


		if (reinterpret_cast<GameObject*>(obj)->GetType() != UnitType::AIHeroClient)
			return nullptr;

		return reinterpret_cast<GameObject*>(obj);
	}
	//mouse en yakýn hedefi alýr
	static GameObject*GetNearMouseTarget();
	static GameObject* GetUnitByIndex(uint index);
	static GameObject* GetUnitByNetworkId(uint networkId);
};