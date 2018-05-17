#pragma once
#ifndef ATTACKABLEUNIT
#define ATTACKABLEUNIT

class
	DLLEXPORT AttackableUnit : public GameObject
{
public:
	static bool ApplyHooks();
	
	MAKE_GET(ArmorMaterial, std::string, Offsets::oAttackableUnit::ArmorMaterial);
	MAKE_GET(AttackShield, float, Offsets::oAttackableUnit::AttackShield);
	MAKE_GET(HasBotAI, bool, Offsets::oAttackableUnit::HasBotAI);
	MAKE_GET(Health, float, Offsets::oAttackableUnit::Health);
	MAKE_GET(IsBot, bool, Offsets::oAttackableUnit::IsBot);
	MAKE_GET(IsInvulnerable, bool, Offsets::oAttackableUnit::IsInVulnerable);
	MAKE_GET(IsLifestealImmune, bool, Offsets::oAttackableUnit::IsLifestealImmune);
	MAKE_GET(IsPhysicalImmune, bool, Offsets::oAttackableUnit::IsPhysicalImmune);
	MAKE_GET(IsZombie, bool, Offsets::oAttackableUnit::IsZombie);
	MAKE_GET(MagicImmune, bool, Offsets::oAttackableUnit::MagicImmune);
	MAKE_GET(AllShield, float, Offsets::oAttackableUnit::AllShield);
	MAKE_GET(MagicShield, float, Offsets::oAttackableUnit::MagicShield);
	MAKE_GET(Mana, float, Offsets::oAttackableUnit::Mana);
	MAKE_GET(MaxHealth, float, Offsets::oAttackableUnit::MaxHealth);
	MAKE_GET(MaxMana, float, Offsets::oAttackableUnit::MaxMana);
	MAKE_GET(OverrideCollisionHeight, float, Offsets::oAttackableUnit::OverrideCollisionHeight);
	MAKE_GET(OverrideCollisionRadius, float, Offsets::oAttackableUnit::OverrideCollisionRadius);
	MAKE_GET(PathfindingCollisionRadius, float, Offsets::oAttackableUnit::PathfindingCollisionRadius);
	MAKE_GET(WeaponMaterial, std::string, Offsets::oAttackableUnit::WeaponMaterial);
	MAKE_GET(Direction, RVector3, Offsets::oAttackableUnit::Direction);

	
	bool IsMelee()
	{
		return *reinterpret_cast<byte*>(this + static_cast<int>(Offsets::Obj_AIBase::CombatType)) == 1;
	}

	bool IsRanged()
	{
		return *reinterpret_cast<byte*>(this + static_cast<int>(Offsets::Obj_AIBase::CombatType)) == 2;
	}

	bool IsAttackingPlayer()
	{
		return false;
	}

	float AttackableUnit::GetHealthPercent()
	{
		if (*this->GetHealth() <= 0)
			return 0;

		return *this->GetHealth() * 100 / *this->GetMaxHealth();
	}

	float AttackableUnit::GetManaPercent()
	{
		if (!this
			|| *this->GetIsDead()
			|| *this->GetMana() == 0) return 0;

		return *this->GetMana() * 100 / *this->GetMaxMana();
	}


};
#endif