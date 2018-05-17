


Obj_AI_Base* ObjectManager::GetPlayer()
{
	return *reinterpret_cast<Obj_AI_Base**>(MAKE_RVA(Offsets::ObjectManager::LocalPlayer));
}

GameObject** ObjectManager::GetUnitArray()
{
	auto bb = reinterpret_cast<GameObject**>(MAKEPTR(Offsets::ObjectManager::ObjectList));
	return bb; //benm objectlistime göre 3 kez deðil 2 kez castlanýyor
}

std::vector<GameObject*> ObjectManager::GetMinions(ObjectTeam type)
{
	auto unitarray = ObjectManager::GetUnitArray();
	std::vector<GameObject*>result;
	if (unitarray)
	{
		for (uint i = 0; i < 10000; i++)
		{
			auto unit = (Obj_AI_Base*)unitarray[i];
			if (unit)
			{
				
				if (strstr(unit->GetName().c_str(), "Minion") == 0)
					continue;

				if (type == ObjectTeam::All)
				{
					if (unit->GetType() == UnitType::AIMinionClient && *unit->GetHealth() > 1 )
					{
						result.push_back((GameObject*)unit);
					}
				}
				else if (type == ObjectTeam::Allies)
				{
					if (unit->GetType() == UnitType::AIMinionClient && *unit->GetHealth() > 1 && *GetPlayer()->GetTeam() == *unit->GetTeam())
					{
						result.push_back((GameObject*)unit);
					}
				}
				else if (type == ObjectTeam::Enemies)
				{
					if (unit->GetType() == UnitType::AIMinionClient && *unit->GetHealth() > 1 && *GetPlayer()->GetTeam() != *unit->GetTeam())
					{
						result.push_back((GameObject*)unit);
					}
				}
				
			}
		}
	} 
	return result;
}
std::vector<GameObject*> ObjectManager::GetHeroes(ObjectTeam type, float range , Obj_AI_Base*entity)
{
	auto unitarray = ObjectManager::GetUnitArray();
	std::vector<GameObject*>result;
	if (unitarray)
	{
		for (uint i = 0; i < 10000; i++)
		{
			auto unit = (Obj_AI_Base*)unitarray[i];
			if (unit)
			{
				if (*unit->GetNetworkId() == *GetPlayer()->GetNetworkId())
					continue;

	/*			if (unit->Distance(entity->GetServerPosition()) > range)
					continue;*/


				if (type == ObjectTeam::All)
				{
					if (unit->GetType() == UnitType::AIHeroClient && *unit->GetHealth() > 1)
					{
						result.push_back((GameObject*)unit);
					}
				}
				else if (type == ObjectTeam::Allies)
				{
					if (unit->GetType() == UnitType::AIHeroClient && *unit->GetHealth() > 1 && *GetPlayer()->GetTeam() == *unit->GetTeam())
					{
						result.push_back((GameObject*)unit);
					}
				}
				else if (type == ObjectTeam::Enemies)
				{
					if (unit->GetType() == UnitType::AIHeroClient && *unit->GetHealth() > 1 && *GetPlayer()->GetTeam() != *unit->GetTeam())
					{
						result.push_back((GameObject*)unit);
					}
				}

			}
		}
	}
	return result;
}

GameObject*ObjectManager::GetNearMouseTarget()
{
	GameObject*lasthero = nullptr;
	float NearDistance = 1000;
	for (auto g_object : ObjectManager::GetHeroes(ObjectManager::ObjectTeam::Enemies))
	{
		float dist = Game::Cursor()->GetPosition()->Distance(g_object->GetPosition());
		if (dist < NearDistance && *g_object->GetVisible() && reinterpret_cast<Obj_AI_Base*>(g_object)->isValid())
		{
			NearDistance = dist;
			lasthero = g_object;
		}
	}
	return lasthero;
}

GameObject* ObjectManager::GetUnitByIndex(uint index)
{
	if (index <= 0)
	{
		return nullptr;
	}

	return GetUnitArray()[index];
}

GameObject* ObjectManager::GetUnitByNetworkId(uint networkId)
{
	__try
	{
		if (networkId != 0)
		{
			for (auto i = 0; i < 10000; i++)
			{
				auto unit = GetUnitArray()[i];
				if (unit != nullptr)
				{
					auto netId = unit->GetNetworkId();
					if (netId != nullptr)
					{
						if (*unit->GetNetworkId() == *GetPlayer()->GetNetworkId())
							continue;

						if (*netId == networkId && *netId >= 0x3FFFFCC8)
						{
							return unit;
						}
					}
				}
			}
		}
	}
	__except (1) {}

	return nullptr;
}