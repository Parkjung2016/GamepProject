#include "pch.h"
#include "UI.h"

#include "MyFunc.h"
#include "GDISelector.h"
#include "InputManager.h"

UI::UI(bool _bCamAff)
	: m_pParentUI(nullptr),
	m_bCamAffected(_bCamAff),
	m_bMouseOn(false)
{
}

UI::UI(const UI& _origin)
	: Object(_origin),
	m_pParentUI(nullptr),
	m_bCamAffected(_origin.m_bCamAffected),
	m_bMouseOn(false),
	m_bLBDown(false)
{

	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

UI::~UI()
{
	SafeDeleteVec(m_vecChildUI);
}

void UI::Update()
{
	Update_Child();
}

void UI::LateUpdate()
{
	Object::LateUpdate();
	m_vFinalPos = GetPos();
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	MouseOnCheck();

	LateUpdate_Child();
}

void UI::Render(HDC _hdc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vSize = GetSize();
	if (m_bCamAffected)
	{
		vPos = GET_SINGLE(Camera)->GetRenderPos(vPos);
	}

	if (m_bLBDown)
	{
		GDISelector select(_hdc, PEN_TYPE::GREEN);
		Rectangle(_hdc, int(vPos.x), int(vPos.y), int(vPos.x + vSize.x), int(vPos.y + vSize.y));
	}
	else
	{
		Rectangle(_hdc, int(vPos.x), int(vPos.y), int(vPos.x + vSize.x), int(vPos.y + vSize.y));

	}

	Render_Child(_hdc);
}

void UI::Update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Update();
	}
}

void UI::LateUpdate_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->LateUpdate();
	}
}


void UI::Render_Child(HDC _hdc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render(_hdc);
	}
}

void UI::MouseOnCheck()
{
	Vec2 vMousePos = GET_MOUSEPOS;
	Vec2 vSize = GetSize();

	if (m_bCamAffected)
	{
		vMousePos = GET_SINGLE(Camera)->GetRealPos(vMousePos);
	}
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vSize.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vSize.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void UI::MouseOn()
{
}

void UI::MouseLBDown()
{

}

void UI::MouseLBUp()
{
}

void UI::MouseLBClicked()
{
}
