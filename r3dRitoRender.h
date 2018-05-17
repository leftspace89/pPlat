#pragma once
class r3DRitoRender
{
public:
	MAKE_GET(projectionMatrix, D3DXMATRIX, Offsets::r3dRendererStruct::Projection);
	MAKE_GET(viewMatrix, D3DXMATRIX, Offsets::r3dRendererStruct::View);
	MAKE_GET(screenWidth, uint, Offsets::r3dRendererStruct::ClientWidth);
	MAKE_GET(screenHeight, uint, Offsets::r3dRendererStruct::ClientHeight);

private:

};