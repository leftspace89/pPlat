#include "LBuffInstance.h"
#include "Obj_AI_Base.h"
Obj_AI_Base* GetAttackableUnitByNetworkID(uint id)
{
	return  (Obj_AI_Base*)MAKEPTR(Offsets::ObjectManager::LocalPlayer);
}
#ifdef yedekamanhayarramýyesinbuyedekolsunamk
BuffInstance* BuffInstance::GetBuffPtr(uint netID)
{
	auto ptr = GetAttackableUnitByNetworkID(netID);// attackable unit by network yapýlacak
	if (ptr != nullptr)
	{

		auto buffBegin = *ptr->GetBegin();
		auto buffEnd = *ptr->GetEnd();

		if (buffBegin != nullptr && buffEnd != nullptr)
		{
			for (uint32_t i = 0; i < (buffEnd - buffBegin) / sizeof(BuffInstance); i++)
			{
				auto buffNode = buffBegin + i;
				auto buffInst = buffNode->buffInst;

				if (buffNode != nullptr && buffInst != nullptr)
				{
					if (buffInst->IsValid())
					{
						auto base = buffInst->GetScriptBaseBuff();
						if (base)
						{
							//bufflist.push_back(buffInst);
							ENGINE_MSG("i(%02x) : (%.f : %.f) : (%s)\n", *buffInst->GetIndex(), *buffInst->GetStartTime(), *buffInst->GetEndTime(), base->GetName());
						}
					}

				}
			}
		}

	}
	return nullptr;
}
#endif
std::vector<BuffInstance*> BuffInstance::GetBuffList(GameObject*ptrin)
{
	std::vector<BuffInstance*> bufflist;
	auto ptr = reinterpret_cast<Obj_AI_Base*>(ptrin);//GetAttackableUnitByNetworkID(netid);// attackable unit by network yapýlacak
	if (ptr != nullptr)
	{

		auto buffBegin = *ptr->GetBegin();
		auto buffEnd = *ptr->GetEnd();

		if (buffBegin != nullptr && buffEnd != nullptr)
		{
			for (uint32_t i = 0; i < (buffEnd - buffBegin) / sizeof(BuffInstance); i++)
			{
				auto buffNode = buffBegin + i;
				auto buffInst = buffNode->buffInst;

				if (buffNode != nullptr && buffInst != nullptr)
				{
					if (buffInst->IsValid())
					{
						auto base = buffInst->GetScriptBaseBuff();
						if (base)
						{
							bufflist.push_back(buffInst);
#ifdef _DEBUG0
							ENGINE_MSG("i(%02x) : (%.f : %.f) : (%s)\n", *buffInst->GetIndex(), *buffInst->GetStartTime(), *buffInst->GetEndTime(), base->GetName());
#endif
						}
					}

				}
			}
		}

	}
	return bufflist;
}
std::vector<RVector3*> Obj_AI_Base::GetPathList()
{
	return GetPathList(reinterpret_cast<Obj_AI_Base*>(this));
}

std::vector<RVector3*> Obj_AI_Base::GetPathList(Obj_AI_Base*ptrin)
{
	std::vector<RVector3*> bufflist;
	auto ptr = ptrin;//GetAttackableUnitByNetworkID(netid);// attackable unit by network yapýlacak
	if (ptr != nullptr)
	{
		auto aim = *ptr->GetAIManager_Client();
	
		auto buffBegin = *aim->GetNavBegin();
		auto buffEnd = *aim->GetNavEnd();

		if (buffBegin != nullptr && buffEnd != nullptr)
		{
			for (uint32_t i = 0; i < (buffEnd - buffBegin) ; i++)
			{
				auto buffNode = buffBegin + (i);
				
				if (buffNode != nullptr )
				{
					if(buffNode->x > 20 && buffNode->y > 20 && buffNode->z > 20 && buffNode->x < 50000)
					{ 
					bufflist.push_back(buffNode);
#ifdef _DEBUG1
					ENGINE_MSG("%d :  %.f %.f %.f\n",i,buffNode->x, buffNode->y , buffNode->z);
#endif				
					}

				}
			}
		}

	}
	return bufflist;
}
