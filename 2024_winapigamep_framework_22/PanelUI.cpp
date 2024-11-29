#include "pch.h"
#include "PanelUI.h"

#include "InputManager.h"

PanelUI::PanelUI() : UI(false)
{
}

PanelUI::PanelUI(bool _bCanMovePanel) : UI(false), m_bCanMovePanel(_bCanMovePanel)
{
}

PanelUI::~PanelUI()
{
}

void PanelUI::MouseOn()
{
	if (!m_bCanMovePanel)return;
	if (IsLBDown())
	{
		Vec2 mousePos = GET_MOUSEPOS;
		Vec2 vDiff = mousePos - m_vDragStart;

		Vec2 vCurPos = GetPos();
		vCurPos += vDiff;
		SetPos(vCurPos);

		m_vDragStart = mousePos;
	}
}

void PanelUI::MouseLBDown()
{
	m_vDragStart = GET_MOUSEPOS;
}

void PanelUI::MouseLBUp()
{
}

void PanelUI::MouseLBClicked()
{
}

