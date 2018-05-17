#include "LSRender.h"
LSRender::LSRender()
{
	sDevice = 0;
	sSprite = 0;
	for (size_t i = 0; i < 200; i++)
	{
		fonts[i] = 0;
	}
	ready = false;

}

LSRender::~LSRender()
{

}

bool LSRender::Attach(LPDIRECT3DDEVICE9 pDevice)
{
	if (!pDevice)
		return false;

	if (!sDevice)
		sDevice = pDevice;

	if (!sSprite)
		D3DXCreateSprite(sDevice, &sSprite);

	if (!sLine)
		D3DXCreateLine(pDevice, &sLine);


	if (sDevice && sSprite && sLine)
		ready = true;
	else
		ready = false;


	static POINT cursorpoint;
	GetCursorPos(&cursorpoint);
	ScreenToClient(GetForegroundWindow(), &cursorpoint);
	CursorPos.x = (FLOAT)cursorpoint.x;
	CursorPos.y = (FLOAT)cursorpoint.y;

	//DrawBox(CursorPos, D3DXVECTOR2(20, 20), D3DCOLOR_ARGB(255, 255, 255, 0));
	return ready;
}

void LSRender::LostDevice()
{
	for (size_t i = 0; i < 255; i++)
	{
		if (fonts[i])
		{
			fonts[i]->OnLostDevice();
		}
	}

	if (sLine)
		sLine->OnLostDevice();
	if (sSprite)
		sSprite->OnLostDevice();


}

void LSRender::ResetDevice()
{
	for (size_t i = 0; i < 255; i++)
	{
		if (fonts[i])
		{
			fonts[i]->OnResetDevice();
			fonts[i] = 0;
		}
	}
	if (sLine)
	{
		sLine->OnResetDevice();
		sLine = 0;
	}
	if (sSprite)
	{
		sSprite->OnResetDevice();
		sSprite = 0;
	}
}

bool LSRender::Ready()
{
	return ready;
}
LPDIRECTINPUT8 di;
LPDIRECTINPUTDEVICE8 keyboard;
#define keydown(name,key) (name[key] & 0x80)
HRESULT initializedirectinput8() {
	HRESULT hr;
	// Create a DirectInput device
	if (FAILED(hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&di, NULL))) {
		
	}
	return hr;
}

void createdikeyboard() {
	di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(NULL, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	keyboard->Acquire();
}
bool inited = true;
void initdirect()
{
	if (!inited)
		return;
	initializedirectinput8();
	createdikeyboard();

	inited = true;

}
DWORD curtick = GetTickCount();
BYTE dikeys[256];

#define GetAsyncKeyStateB(kod) keydown(dikeys,#kod) && GetTickCount() - curtick  > 250
struct CUSTOMVERTEX { FLOAT X, Y, Z; DWORD COLOR; };
#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

bool LSRender::GetKeyPressed(int vKey)
{
	bool isPressed = GetAsyncKeyState(vKey) & 0x8000 && GetTickCount() - curtick  > 300;
	if (isPressed)
	{
		curtick = GetTickCount();
	
	}
	return isPressed;
}
bool GetDIKeyPressed(int vKey)
{
	initdirect();
	keyboard->GetDeviceState(256, dikeys);

	bool isPressed = (dikeys[vKey] & 0x80) && GetTickCount() - curtick  > 300;
	if (isPressed)
	{
		curtick = GetTickCount();

	}
	return isPressed;
}
LPD3DXFONT LSRender::CreateFontBySize(int size, char* font)
{
	if (fonts[size])
		return fonts[size];

	if (sDevice)
		if (fonts[size] == 0)
			if (FAILED(D3DXCreateFontA(sDevice, size, 0, 500, 0, 0, TURKISH_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, font, &fonts[size])))
			{
				return 0;
			}

	return fonts[size];
}

void LSRender::DrawString(float x, float y, D3DCOLOR color, DWORD Flag, int fontsize, const char * text, ...)
{
	if (!Ready())
		return;

	if (!fonts[fontsize])
	{
		fonts[fontsize] = CreateFontBySize(fontsize);
		return;
	}

	if (!fonts[fontsize])
		return;

	if (!sSprite)
		return;

	RECT rct;
	rct.left = (LONG)x - 1;
	rct.right = (LONG)x + 1;
	rct.top = (LONG)y - 1;
	rct.bottom = (LONG)y + 1;

	va_list va_alist;
	char vaBuffer[256] = { 0 };
	va_start(va_alist, text);
	_vsnprintf(vaBuffer + strlen(vaBuffer), sizeof(vaBuffer) - strlen(vaBuffer), text, va_alist);
	va_end(va_alist);

	sSprite->Begin(D3DXSPRITE_ALPHABLEND);
	fonts[fontsize]->DrawTextA(sSprite, vaBuffer, -1, &rct, Flag | DT_NOCLIP, color);
	sSprite->End();
}







void LSRender::DrawStringL(float x, float y, int fontsize, DWORD color, char * text)
{
	if (!Ready())
		return;

	if (!fonts[fontsize])
	{
		fonts[fontsize] = CreateFontBySize(fontsize);
		return;
	}

	if (!fonts[fontsize])
		return;

#pragma warning (push)
#pragma warning (disable:4244)
	RECT rect;
	SetRect(&rect, (float)x, (float)y, (float)x, (float)y);
	fonts[fontsize]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
#pragma warning (pop)
}

void LSRender::DrawLine(float fx, float fy, float tx, float ty, float width, D3DCOLOR color)
{

	if (!Ready())
		return;

	D3DXVECTOR2 dLine[2];

	sLine->SetWidth(width);
	sLine->SetAntialias(true);
	sLine->SetGLLines(true);

	dLine[0].x = fx;
	dLine[0].y = fy;

	dLine[1].x = tx;
	dLine[1].y = ty;

	sLine->Draw(dLine, 2, color);

}
void LSRender::GradientBox(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR color, D3DCOLOR color2, bool vertical) {
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	pVertex[4] = { { Pos.x, Pos.y, 0.0f, 1.0f, color },{ Pos.x + Size.x, Pos.y, 0.0f, 1.0f, vertical ? color : color2 },{ Pos.x, Pos.y + Size.y, 0.0f, 1.0f, vertical ? color2 : color },{ Pos.x + Size.x, Pos.y + Size.y, 0.0f, 1.0f, color2 } };
	sDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	sDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof(Vertex));
}
void LSRender::DrawBox(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR Color)
{
	if (!Ready())
		return;

	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[17] = { { Pos.x, Pos.y + Size.y, 0.0f, 0.0f, Color },{ Pos.x, Pos.y, 0.0f, 0.0f, Color },{ Pos.x + Size.x, Pos.y + Size.y, 0.0f, 0.0f, Color },{ Pos.x + Size.x, Pos.y, 0.0f, 0.0f, Color } };
	sDevice->SetTexture(0, NULL);
	sDevice->SetPixelShader(0);
	sDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	sDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	sDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	sDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	sDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	sDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));

	return;
}

void LSRender::FillRGB(int x, int y, int w, int h, D3DCOLOR Color)
{
	if (!Ready())
		return;

	D3DRECT rec = { x, y, x + w, y + h };
	sDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

void LSRender::DrawBorder(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, int px, D3DCOLOR BorderColor)
{
	if (!Ready())
		return;

	FillRGB(Pos.x, (Pos.y + Size.y - px), Size.x, px, BorderColor);
	FillRGB(Pos.x, Pos.y, px, Size.y, BorderColor);
	FillRGB(Pos.x, Pos.y, Size.x, px, BorderColor);
	FillRGB(Pos.x + Size.x - px, Pos.y, px, Size.y, BorderColor);

}

int LSRender::GetTextWidth(const char * szText, int fontsize)
{
	if (!Ready())
		return 0;
	if (!fonts[fontsize])
		return 0;

	RECT rcRect = { 0,0,0,0 };
	if (fonts[fontsize])
	{
		fonts[fontsize]->DrawText(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
	}
	return rcRect.right - rcRect.left;
}




void LSRender::MoveByMouse(D3DXVECTOR2 &Pos, D3DXVECTOR2& Size)
{
	if (BoundBox(CursorPos, D3DXVECTOR2(Pos.x, Pos.y), D3DXVECTOR2(Size.x, Size.y)))
	{

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			Pos.x = CursorPos.x - ClickPos.x;
			Pos.y = CursorPos.y - ClickPos.y;

		}
		else
		{
			ClickPos.x = (CursorPos.x - Pos.x);
			ClickPos.y = (CursorPos.y - Pos.y);
		}
	}
}

void LSRender::ResizeByMouse(D3DXVECTOR2 &Pos, D3DXVECTOR2& Size)
{
	static D3DXVECTOR2 defsize = Size;

	if (BoundBox(CursorPos, D3DXVECTOR2(Pos.x, Pos.y), D3DXVECTOR2(Size.x, Size.y)))
	{

		if (GetAsyncKeyState(VK_LBUTTON) < 0)
		{
			Size.x = CursorPos.x - ClickPos.x;
			Size.y = CursorPos.y - ClickPos.y;
		}
		else
		{
			ClickPos.x = (CursorPos.x - Size.x);
			ClickPos.y = (CursorPos.y - Size.y);
		}
	}
}

D3DCOLOR LSRender::FromHex(DWORD hexcolor)
{
	BYTE r = (BYTE)((hexcolor >> 16) & 0xFF);
	BYTE g = (BYTE)((hexcolor >> 8) & 0xFF);
	BYTE b = (BYTE)(hexcolor & 0xFF);
	return D3DCOLOR_ARGB(255, r, g, b);
}


void LSRender::MoveByKeyboard(D3DXVECTOR2 & Pos)
{
	if (GetAsyncKeyState(VK_UP))
		Pos.y -= 0.5f;
	else if (GetAsyncKeyState(VK_DOWN))
		Pos.y += 0.5f;
	if (GetAsyncKeyState(VK_LEFT)) { Pos.x -= 0.5f; }
	if (GetAsyncKeyState(VK_RIGHT)) { Pos.x += 0.5f; }
}

bool LSRender::r3dWorldToScreen( RVector3* p_World, RVector3* p_Screen)
{
	__try
	{
		D3DXMATRIX mWorld;
		memset(&mWorld, 0, sizeof(mWorld));
		D3DXMatrixIdentity(&mWorld);
		r3DRitoRender * ritorender = (r3DRitoRender*)*(DWORD*)(MAKE_RVA(Offsets::r3dRenderer::r3dRendererInstance));
		D3DVIEWPORT9 v_Viewport;
		sDevice->GetViewport(&v_Viewport);
		D3DXVec3Project(p_Screen, p_World, &v_Viewport, &*ritorender->GetprojectionMatrix(), &*ritorender->GetviewMatrix(), &mWorld);


		p_Screen->x = (p_Screen->x) / (*ritorender->GetscreenWidth()) * *ritorender->GetscreenWidth();
		p_Screen->y = (p_Screen->y) / (*ritorender->GetscreenHeight()) * *ritorender->GetscreenHeight();

		if (p_Screen->x < 0.f || p_Screen->x > *ritorender->GetscreenWidth())
			return false;

		if (p_Screen->y < 0.f || p_Screen->y > *ritorender->GetscreenHeight())
			return false;
		//printf("W %d H %d X : %.f , Y : %.f\n", ritorender->screenWidth, ritorender->screenHeight, p_Screen->x, p_Screen->y);
	}
	__except (1)
	{

	}
	return true;
}
float LSRender::r3dDistance(RVector3 a, RVector3 b)
{
	RVector3 vector = RVector3(a.x - b.x, a.y - b.y, a.z - b.z);
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}