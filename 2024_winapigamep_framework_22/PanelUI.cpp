#include "pch.h"
#include "PanelUI.h"

#include "ResourceManager.h"
#include "Texture.h"

PanelUI::PanelUI() : UI(false)
{
}

PanelUI::~PanelUI()
{
}

void PanelUI::Render(HDC _hdc)
{
	Vec2 vPos = GetFinalPos();
	int texWidth = (int)m_pTex->GetWidth();
	int texHeight = (int)m_pTex->GetHeight();


	TransparentBlt(_hdc,
		(int)vPos.x- texWidth/2.f,
		(int)vPos.y - texHeight / 2.f,
		(int)texWidth,
		(int)texHeight,
		m_pTex->GetTexDC(),
		0,
		0,
		(int)texWidth,
		(int)texHeight,
		RGB(255, 0, 255));
	Render_Child(_hdc);

}

void PanelUI::SetTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);
	SetSize({ (int)m_pTex->GetWidth()  ,(int)m_pTex->GetHeight() });
}
