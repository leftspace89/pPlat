LSRender render;


using namespace pPlat::Native;
static LPDIRECT3DDEVICE9        g_pd3dDevice = NULL;
static D3DPRESENT_PARAMETERS    g_d3dpp;
static WNDPROC def_wndproc = nullptr;
static bool MenuIsOpen = true;
static HWND GameWindow =  FindWindowA("Dx9", 0);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
static  DWORD *vTable;
MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9, CONST RECT *, CONST RECT *, HWND, CONST RGNDATA * > r3dPresentEx;
MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9> r3dEndScene;
MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT > r3dDrawPrimtive;
MAKE_HOOK<convention_type::stdcall_t, HRESULT, LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS* > r3dResetEx;

bool check[255];

std::vector<DWORD>pComponents;
TargetSelector*targetselector = new TargetSelector();


LRESULT WINAPI hkWndProc(HWND window, UINT message_type, WPARAM w_param, LPARAM l_param) {
	
	if (MenuIsOpen)
		ImGui_ImplWin32_WndProcHandler(GameWindow, message_type, w_param, l_param);

	//if (MenuIsOpen)
	//	return 0;

	return CallWindowProc(def_wndproc, window, message_type, w_param, l_param);
};
char * tr(char*str)
{
	return str;
}
LRESULT CALLBACK DXInputHook(int nCode, WPARAM wParam, LPARAM lParam) 
{
	ImGui_ImplDx9_WndProcHandler((LPMSG)lParam);
	return CallNextHookEx(0, nCode, wParam, lParam);
}
void DirectxMenu(LPDIRECT3DDEVICE9 pDevice)
{

	pDevice->SetTexture(0, 0);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CLIPPING, FALSE);
	pDevice->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_VERTEXBLEND, D3DVBF_DISABLE);
	pDevice->SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	pDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	pDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	pDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
}

int HataYakala(int code, PEXCEPTION_POINTERS ex) {
	printf("Hata Kodu : %p  , Lokasyon : %p\n", code, ex->ExceptionRecord->ExceptionAddress);
	return EXCEPTION_EXECUTE_HANDLER;
}

void LSMenu()
{
	if (MenuIsOpen)
	{
		
		/*ui::SetNextWindowSize(ImVec2(600, 250));
		ui::Begin(tr("pPlat 0.0.1 > ALL"), &MenuIsOpen, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize);
		if (ui::TabButtonGIndex() == 0)
		{
		
		}
		ImVec2 pos = ui::GetWindowPos();
		ui::End();
		ui::SetNextWindowSize(ImVec2(150, 250));
		ui::SetNextWindowPos(ImVec2(pos.x - 155, pos.y), ImGuiSetCond_Always);*/
		//ui::SetNextWindowSize(ImVec2(300, 600));
		ui::Begin(tr("pPlat 0.0.2 > ALL"), &MenuIsOpen);
		for (size_t i = 0; i < 3; i++)
		{
			ui::Spacing();
		}

		if (Game::IsInGame())
		pComponent::ComponentEvents_onMenu();
	
		ui::End();
	}
}
void D3DXMatrixDraw(const D3DXMATRIX *pM)
{
	render.DrawString(120, 100, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER, 16, "%3.3f %3.3f %3.3f %3.3f", pM->_11, pM->_12, pM->_13, pM->_14);
	render.DrawString(120, 120, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER, 16, "%3.3f %3.3f %3.3f %3.3f", pM->_21, pM->_22, pM->_23, pM->_24);
	render.DrawString(120, 140, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER, 16, "%3.3f %3.3f %3.3f %3.3f", pM->_31, pM->_32, pM->_33, pM->_34);
	render.DrawString(120, 160, D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER, 16, "%3.3f %3.3f %3.3f %3.3f", pM->_41, pM->_42, pM->_43, pM->_44);
}


void ImGuiEx(LPDIRECT3DDEVICE9 pDevice)
{
	//DirectxMenu(pDevice);
	if (LSUtils::GetKeyPressed(VK_INSERT))
	{
		MenuIsOpen = !MenuIsOpen;
	}
	static bool nope = true;
	if (nope)
	{
		GameWindow = FindWindowA(0, "League of Legends (TM) Client");
		
		ImGui::CreateContext();
		def_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(GameWindow, GWLP_WNDPROC, LONG_PTR(hkWndProc)));
		//SetWindowsHookEx(WH_GETMESSAGE, DXInputHook, 0, GetCurrentThreadId());
		ImGui_ImplDX9_Init(GameWindow, pDevice);
		ImGui_ImplDX9_CreateDeviceObjects();
		ui::StyleColorsMaze();
		nope = false;
	}
	ImGui_ImplDX9_NewFrame();
	LSMenu();
	ui::EndFrame();
	ui::Render();
	ImGui_ImplDX9_RenderDrawData(ui::GetDrawData());
}

template<typename type>
class GetSet
{
public:
	void set(type &x) { x = 101; }
	type get() const { return 0; }
	
};

//typedef void(__thiscall* tIssueOrder)(LSLObject *Player, int Mode, RVector3* Pos, LSLObject *target, int a4, int a5, char a7);
//tIssueOrder issueOrderx = reinterpret_cast<tIssueOrder>(MAKEPTR(pfnIssueOrder));
void r3dMainLoop()
{
	float health = 100;
	DWORD ptrr = reinterpret_cast<DWORD>(&health);
	

	do
	{
		Sleep(100);
	} while (!Game::IsInGame());
	Sleep(1000);
	pComponent::ComponentEvents_onStart();
	
	while (true)
	{
		
		if (Game::IsInGame())
		{
			//ObjectManager::GetAllObjects();

			pComponent::ComponentsEvent_onUpdate();
		}
			
		
		//LSLCursor *lolcursor = (LSLCursor*)*(DWORD*)(MAKEPTR(oCursorPTR));
		//if(GetAsyncKeyState(VK_LSHIFT))
		//ENGINE_MSG("%.f %.f %.f\n", lolcursor->CursorPosXYZ.x, lolcursor->CursorPosXYZ.y, lolcursor->CursorPosXYZ.z);
		//__try
		//{
		//	LSLObject*player = (LSLObject*)*(DWORD*)(MAKEPTR(oLocalPlayer));
		//	if (lolcursor)
		//		if (GetAsyncKeyState(VK_SPACE))
		//			issueOrderx(player, 2, &lolcursor->CursorPosXYZ, NULL, 0, 0, 1);
		//}
		//__except (1)
		//{
		//	//ENGINE_MSG("Exception  %s\n",__FUNCTION__);
		//}
		
		Sleep(1);
	}
}



void r3dHooks()
{
	if (!vTable)
		return;
	//static ObjectManager *objectmanager = new ObjectManager();
	//OrbWalker*walker = new OrbWalker();
	//walker->Add();

	
	targetselector->Add();

	LCoreTest*test = new LCoreTest();
	test->Add();
	TosbikBlitz * blitz = new TosbikBlitz();
	blitz->Add();
	TospikThresh*thresh = new TospikThresh();
	thresh->Add();

	TospikCait*cait = new TospikCait();
	cait->Add();

	OrbWalker*walker = new OrbWalker();
	walker->Add();

	TospikBrand*brand = new TospikBrand();
	brand->Add();


	LSUtils::CreateThreadA(r3dMainLoop);	 

	r3dEndScene.Apply(vTable[42], [](LPDIRECT3DDEVICE9 pDevice) -> HRESULT {
		render.Attach(pDevice);

		if (Game::IsInGame())
		pComponent::ComponentsEvent_onRender();

		ImGuiEx(pDevice);
		
		/*for (ObjectManager*tmp : ObjectManager::GetAllObjects())
		{
			RVector3 Screen;
			if (tmp->GetObjectType() == ObjectManager::ObjectType::HERO)
				if (render.r3dWorldToScreen(&tmp->GetPosition(), &Screen))
				{
					render.DrawString(Screen.x, Screen.y, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "object : %02x", tmp->GetObjectType());
				}

			if (tmp->GetObjectType() == ObjectManager::ObjectType::HERO)
			{


			}
			else if (tmp->GetObjectType() == ObjectManager::ObjectType::MINION)
			{
				RVector3 Screen;
				if (render.r3dWorldToScreen(&tmp->GetPosition(), &Screen))
				{
					render.DrawString(Screen.x, Screen.y, D3DCOLOR_ARGB(255, 255, 255, 255), DT_LEFT, 15, "Minion");
				}
			}
			else if (tmp->GetObjectType() == ObjectManager::ObjectType::TURRET)
			{

			}
			else if (tmp->GetObjectType() == ObjectManager::ObjectType::INHIB)
			{

			}
		}*/
	
		HRESULT pp = r3dEndScene.CallOriginal(pDevice);

			

		return pp;
	});


	r3dResetEx.Apply(vTable[16], [](LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS*pPresentationParameters) -> HRESULT {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		render.ResetDevice();
		HRESULT hres = r3dResetEx.CallOriginal(pDevice, pPresentationParameters);
		if (hres == D3DERR_INVALIDCALL)
		{
			render.LostDevice();
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return hres;
	});
	
}

 void HookStart()
 {
	
	 DWORD adr;
	 DWORD hD3D = 0;


	
	 do
	 {
		 GameWindow = FindWindowA(0, "League of Legends (TM) Client");
		 Sleep(100);
	 } while (!GameWindow);
	 hD3D = (DWORD)GetModuleHandleA("d3d9.dll");
	 do
	 {
		 hD3D = (DWORD)GetModuleHandleA("d3d9.dll");
	 } while (!hD3D);
	 adr = LSUtils::FindPattern(hD3D, 0x128000, (PBYTE)"\xC7\x06\x00\x00\x00\x00\x89\x86\x00\x00\x00\x00\x89\x86", "xx????xx????xx");
	 if (adr)
	 {
		 memcpy(&vTable, (void *)(adr + 2), 4);
		 ENGINE_MSG("pPlat Initialized\n");
		 r3dHooks();
	 }
 }

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		LSUtils::CreateThreadA(HookStart);
		break;
	default:
		break;
	}
	return TRUE;
}