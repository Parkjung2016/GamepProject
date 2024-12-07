#include "pch.h"
#include "BtnUI.h"

#include "AudioSystem.h"
#include "ResourceManager.h"
#include "SoundEvent.h"
#include "Texture.h"

BtnUI::BtnUI() : UI(false),
m_pNormalTex(nullptr),
m_pPressTex(nullptr
), m_pFunc(nullptr),
m_param1(0),
m_param2(0)
{
}

BtnUI::~BtnUI()
{
}

void BtnUI::MouseOn()
{
}

void BtnUI::MouseLBDown()
{
}

void BtnUI::MouseLBUp()
{

}

void BtnUI::MouseLBClicked()
{

	GET_SINGLE(AudioSystem)->PlayEvent("event:/UI/ClickBtn");

	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}
}

void BtnUI::Render(HDC _hdc)
{
	Vec2 vPos = GetFinalPos();
	Texture* pTex;
	if (m_bLBDown)
	{
		pTex = m_pPressTex;
	}
	else
		pTex = m_pNormalTex;
	int texWidth = (int)pTex->GetWidth();
	int texHeight = (int)pTex->GetHeight();


	TransparentBlt(_hdc,
		(int)vPos.x - texWidth / 2.f,
		(int)vPos.y - texHeight / 2.f,
		(int)texWidth,
		(int)texHeight,
		pTex->GetTexDC(),
		0,
		0,
		(int)texWidth,
		(int)texHeight,
		RGB(255, 0, 255));
}

void BtnUI::SetNormalTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pNormalTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);
	SetSize({ (int)m_pNormalTex->GetWidth()  ,(int)m_pNormalTex->GetHeight() });
}

void BtnUI::SetPressTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pPressTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);

}

