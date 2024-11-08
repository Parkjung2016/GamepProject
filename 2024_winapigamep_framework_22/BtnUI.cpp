#include "pch.h"
#include "BtnUI.h"

BtnUI::BtnUI() : UI(false), m_pFunc(nullptr), m_param1(0), m_param2(0)
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
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}
}
