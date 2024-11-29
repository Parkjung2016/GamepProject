#include "pch.h"
#include "Background.h"

#include "ResourceManager.h"
#include "Texture.h"

Background::Background()
{

}

Background::~Background()
{
}

void Background::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPosWithParallax(vPos, m_vParallaxFactor, vSize);

	::TransparentBlt(_hdc
		, (int)(vRenderPos.x - vSize.x / 2.f)
		, (int)(vRenderPos.y - vSize.y / 2.f)
		, (int)vSize.x,
		(int)vSize.y,
		m_pTex->GetTexDC(),
		0,
		0,
		(int)vSize.x,
		(int)vSize.y,
		RGB(255, 0, 255)
	);
}

void Background::Update()
{
}

void Background::SetTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);
}


