




UnitType GameObject::GetType()
{
	__try
	{
		if (this == nullptr)
			return UnitType::Unknown;

		auto unitType = *reinterpret_cast<UnitType**>(this + static_cast<int>(Offsets::oGameObject::Type));
		if (unitType != nullptr)
		{
			return *static_cast<UnitType*>(unitType);
		}
	}
	__except (1)
	{
		
	}

	return UnitType::Unknown;
}
byte* GameObject::GetTypeByte()
{
	return reinterpret_cast<byte*>(this + static_cast<int>(Offsets::oGameObject::Type));
}
short* GameObject::GetIndex()
{
	return reinterpret_cast<short*>(this + 0x8);
}

GameObjectVTable* GameObject::GetVirtual()
{
	return reinterpret_cast<GameObjectVTable*>(this);
}

char *GameObject::namechar()
{
	__try
	{
	return (char*)reinterpret_cast<String*>(this + static_cast<int>(Offsets::oGameObject::Name));
	}
	__except (1)
	{
		return "except";
	}
}

std::string GameObject::GetName()
{
	std::string ss(namechar());
	
	return ss;
	
	//return *reinterpret_cast<String*>(this + static_cast<int>(Offsets::oGameObject::Name));
	
	
}

void GameObject::SetName(std::wstring name)
{
	*reinterpret_cast<std::wstring*>(this + static_cast<int>(Offsets::oGameObject::Name)) = name;
}

uint* GameObject::GetNetworkId()
{
	IS_NULL_RETN(this,   static_cast<int>(Offsets::oGameObject::NetworkId), 0);
	return reinterpret_cast<uint*>(this + static_cast<int>(Offsets::oGameObject::NetworkId));
}