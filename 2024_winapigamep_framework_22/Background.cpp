#include "pch.h"
#include "Background.h"

#include "ResourceManager.h"
#include "Texture.h"

Background::Background() :
	m_pTex(nullptr),
	m_bIsTransparent(false),
	m_vParallaxFactor({ 1,1 })
{
}

Background::~Background()
{
}

void Background::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPosWithParallax(vPos, m_vParallaxFactor);

	if (m_bIsTransparent)
	{

		::TransparentBlt(_hdc
			, (int)vRenderPos.x
			, (int)vRenderPos.y - vSize.y
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
	else
	{
		BitBlt
		(
			_hdc
			, (int)vRenderPos.x
			, (int)vRenderPos.y - vSize.y
			, (int)vSize.x,
			(int)vSize.y,
			m_pTex->GetTexDC(),
			0,
			0,
			SRCCOPY
		);
	}
}

void Background::Update()
{

}


void Background::SetTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);
	m_vSize = { (int)m_pTex->GetWidth() ,(int)m_pTex->GetHeight() };
}


