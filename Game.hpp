#pragma once
#ifndef GAME
class r3dCursor
{
public:
	MAKE_GET(Position, RVector3, 0x90);
};
class Game
{
public:
	static bool IsInGame()
	{
		return (MAKEPTR(Offsets::ObjectManager::LocalPlayer)) > 0;
	}
	static r3dCursor*Cursor()
	{
		return reinterpret_cast<r3dCursor*>(MAKEPTR(Offsets::r3dRenderer::LOLCursor));
	}
};

#define GAME
#endif // !GAME

