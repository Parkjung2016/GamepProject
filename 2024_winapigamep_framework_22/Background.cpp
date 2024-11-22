#include "pch.h"
#include "Background.h"

#include "ResourceManager.h"
#include "Texture.h"

Background::Background()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Background_0", L"Texture\\Map\\Background_0.bmp");

}

Background::~Background()
{
}

void Background::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	, 0, 0, SRCCOPY
	//);
}

void Background::Update()
{
}


