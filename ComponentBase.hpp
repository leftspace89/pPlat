#pragma once
#ifndef  COMPONENTBASE
#define COMPONENTBASE
//team
extern std::vector<DWORD>pComponents;
extern std::vector<DWORD>teamheroes;
extern std::vector<DWORD>teaminions;
extern std::vector<DWORD>teamturrets;
extern std::vector<DWORD>teaminhibs;

// enemy
extern std::vector<DWORD>enemyheroes;
extern std::vector<DWORD>enemyminions;
extern std::vector<DWORD>enemyturrets;
extern std::vector<DWORD>enemyinhibs;

class pComponent
{
public:
	pComponent(){};
	~pComponent() {};
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;
	virtual void onMenu() = 0;
	virtual void onProcessSpell(SpellData*spelldata,SpellCastInfo*spellcastinfo) = 0;
	void Add()
	{
		pComponents.push_back(reinterpret_cast<DWORD>(this));
	}

	static void ComponentsEvent_onRender()
	{
		

		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onRender();
		}
	}

	

	static void ComponentsEvent_onUpdate()
	{
		

		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
              			component->onUpdate();
		}
	}
	static void ComponentEvents_onStart()
	{
	
		Obj_AI_Base::ApplyHooks();
		Spellbook::ApplyHooks();

		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onStart();
		}
	}
	static void ComponentEvents_onMenu()
	{
	

		for (DWORD pPtr : pComponents)
		{
			pComponent*component = reinterpret_cast<pComponent*>(pPtr);
			component->onMenu();
		}
	}
	char classname[255];
	char Heroname[255];
	char version[255];
	
private:
};


#endif // ! COMPONENTBASE
