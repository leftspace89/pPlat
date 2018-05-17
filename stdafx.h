#pragma once
#include "imgui\imgui.h"
#include "imgui\imgui_tabs.h"
#include "imgui\imgui_impl_dx9.h"
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#define OBJECT_REPEAT_INTERVAL 300
#define ui ImGui
typedef unsigned char byte;
typedef unsigned int  uint;

#include <dinput.h>
#include <tchar.h>
#include <detours.h>
#include <cstdint>
#include <conio.h>
#include <vector>
#include <time.h>
#include <string>
#include <string.h>
#include "String.h"
#include <cmath>
#include "rVectors.hpp"
#include "adDetour.hpp"
#include "macros.h"
#include "Offsets.h"
#include "r3dRitoRender.h"
#include "Game.hpp"
#include "BuffManagerBase.h"
#include "SpellBook.h"
#include "GameObject.h"
#include "Humanizer.h"
#include "AttackableUnit.h"
#include "LObjectManager.h"
#include "Obj_AI_Base.h"
#include "Obj_Minion.h"
#include "Obj_Hero.h"

#include "Prediction.h"
#include "ExpPredict.hpp"
using namespace pPlat::Native;
#include "Memory.h"
#include "ComponentBase.hpp"
#include "Logging.hpp"
#include "Classes.h"
#include "typdefs.h"
#include "LSUtils.hpp"
#include "LSRender.h"
#include "ObjectManager.h"
#include "TargetSelector.hpp"
extern TargetSelector*targetselector;
#include "OrbWalker.hpp"
#include "TospikThresh.h"
#include "TospikBlitz.h" // test blüzzzzzzzzzz
#include "LCoreTest.hpp"
#include "TospikCait.hpp"
#include "TospikBrand.hpp"

#include <cstdio>
#include <time.h>
#include <conio.h>

#pragma comment(lib,"detours.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3dx9.lib")



