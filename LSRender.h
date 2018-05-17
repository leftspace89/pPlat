#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <stdio.h>
class LSRender
{
public:
	LSRender();
	~LSRender();

	bool Attach(LPDIRECT3DDEVICE9 pDevice);
	void LostDevice();
	void ResetDevice();
	bool Ready();

	void DrawString(float x, float y, D3DCOLOR color, DWORD Flag, int fontsize, const char* text, ...);
	void DrawStringL(float x, float y, int fontsize, DWORD color, char *text);
	void DrawLine(float fx, float fy, float tx, float ty, float width, D3DCOLOR color);
	void DrawBox(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR Color);
	void FillRGB(int x, int y, int w, int h, D3DCOLOR Color);
	void DrawBorder(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, int px, D3DCOLOR BorderColor);
	void GradientBox(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, D3DCOLOR color, D3DCOLOR color2, bool vertical);
	bool r3dWorldToScreen( RVector3* p_World, RVector3* p_Screen);
	/*Utils*/
	int GetTextWidth(const char *szText, int fontsize);
	bool BoundBox(D3DXVECTOR2 cursorPos, D3DXVECTOR2 Pos, D3DXVECTOR2 Size)
	{
		return Pos.x >= cursorPos.x - Size.x && Pos.x <= cursorPos.x + Size.x && Pos.y >= cursorPos.y - Size.y && Pos.y <= cursorPos.y + Size.y /*sol*/ &&  cursorPos.x >= Pos.x /*üst*/ && cursorPos.y >= Pos.y;
	}
	D3DXVECTOR2 GetCursorLoc() { return CursorPos; }
	void MoveByMouse(D3DXVECTOR2& Pos, D3DXVECTOR2 &Size);
	void ResizeByMouse(D3DXVECTOR2 & Pos, D3DXVECTOR2 & Size);
	D3DCOLOR FromHex(DWORD hexcolor);
	void MoveByKeyboard(D3DXVECTOR2& Pos);
	bool GetKeyPressed(int vKey);

	float r3dDistance(RVector3 a, RVector3 b);

	static const int CIRCLE_RESOLUTION = 64;

	struct VERTEX_2D_DIF { // transformed colorized
		float x, y, z, rhw;
		D3DCOLOR color;
		static const DWORD FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	};

	void DrawCircleFilled(float mx, float my, float r, D3DCOLOR color)
	{
		VERTEX_2D_DIF verts[CIRCLE_RESOLUTION + 1];

		for (int i = 0; i < CIRCLE_RESOLUTION + 1; i++)
		{
			verts[i].x = mx + r * cos(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
			verts[i].y = my + r * sin(D3DX_PI*(i / (CIRCLE_RESOLUTION / 2.0f)));
			verts[i].z = 0;
			verts[i].rhw = 1;
			verts[i].color = color;
		}

		sDevice->SetFVF(VERTEX_2D_DIF::FVF);
		sDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, CIRCLE_RESOLUTION - 1, &verts, sizeof(VERTEX_2D_DIF));
	}
#define PI 3.14159265//Defining what PI is. PI is a Circle
	void DrawCircle(int X, int Y, int radius, int numSides, DWORD Color)
	{
		if (!sLine)
			return;
		D3DXVECTOR2 Line[128];
		float Step = PI * 2.0 / numSides;
		int Count = 0;
		for (float a = 0; a < PI*2.0; a += Step)
		{
			float X1 = radius * cos(a) + X;
			float Y1 = radius * sin(a) + Y;
			float X2 = radius * cos(a + Step) + X;
			float Y2 = radius * sin(a + Step) + Y;
			Line[Count].x = X1;
			Line[Count].y = Y1;
			Line[Count + 1].x = X2;
			Line[Count + 1].y = Y2;
			Count += 2;
		}
		sLine->Begin();
		sLine->Draw(Line, Count, Color);
		sLine->End();
	}

	LPDIRECT3DDEVICE9 Device() { return sDevice; }
	/*Utils*/
private:
	LPD3DXFONT CreateFontBySize(int size, char* font = "Tahoma");
	LPDIRECT3DDEVICE9 sDevice;
	LPD3DXFONT fonts[255];
	LPD3DXSPRITE sSprite;
	LPD3DXLINE sLine;
	bool ready;
	D3DXVECTOR2 CursorPos, ClickPos;


};
extern LSRender render;
