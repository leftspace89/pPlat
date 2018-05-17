#pragma once
#ifndef OBJMINION
#define OBJMINION
class Obj_Minion : public Obj_AI_Base
{
public:

	
	float AD_Multiplier()
	{
		if (this == nullptr)
			return 0;

		float armor = *GetCharData()->GetArmor();
		if (armor > 0)
			return 100 / (100 + *GetCharData()->GetArmor());
		else
			return 2 - (100 / (100 - armor));
	}

	float GetAttackDamageOnThis()
	{
		float ad = *ObjectManager::GetPlayer()->GetCharData()->GetBaseAttackDamage() + *ObjectManager::GetPlayer()->GetCharData()->GetBonusAttackDamage();
		return ad * AD_Multiplier();
	}

	bool IsLastHitable()
	{
		float ad = *ObjectManager::GetPlayer()->GetCharData()->GetBaseAttackDamage() + *ObjectManager::GetPlayer()->GetCharData()->GetBonusAttackDamage();
		return (*GetHealth() <= ad * AD_Multiplier());
	}
	bool IsLastHitable(float health)
	{
		float ad = *ObjectManager::GetPlayer()->GetCharData()->GetBaseAttackDamage() + *ObjectManager::GetPlayer()->GetCharData()->GetBonusAttackDamage();
		return (health <= ad * AD_Multiplier());
	}
	
private:
	
};

#endif 