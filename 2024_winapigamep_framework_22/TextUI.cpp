#include "pch.h"
#include "TextUI.h"

#include "EventManager.h"
#include "GDISelector.h"
#include "ResourceManager.h"
#include "TimeManager.h"

TextUI::TextUI() : UI(false), m_uAlign(TA_TOP),
m_bIsPopup(false),
m_fFontSize(25), m_fCurrentDestroyTime(0)
{
}

TextUI::TextUI(bool _bIsPopup, float _fFontSize) : UI(false),
m_uAlign(_bIsPopup ? TA_CENTER : TA_TOP),
m_fCurrentDestroyTime(0)
{
	m_bIsPopup = _bIsPopup;
	m_fFontSize = _fFontSize;
}

TextUI::~TextUI()
{
	DeleteObject(m_font);

}

void TextUI::Start()
{
	m_font = CreateFont(
		m_fFontSize,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		HANGEUL_CHARSET,
		0,
		0,
		0,
		VARIABLE_PITCH | FF_ROMAN,
		TEXT("Neo둥근모 Pro"));
}

void TextUI::Update()
{
	UI::Update();

	if (!m_bIsPopup)return;
	if (m_fCurrentDestroyTime <= 0.6f)
	{
		m_fCurrentDestroyTime += fDT;

		Vec2 vPos = GetPos();
		vPos.y -= 100 * fDT;
		SetPos(vPos);
	}
	else if (m_fFontSize >= 2)
	{
		m_fFontSize -= 200 * fDT;

	}
	else
	{
		m_fFontSize = 2;
		tEvent evt;
		evt.eveType = EVENT_TYPE::DELETE_OBJECT;
		evt.lParam = (DWORD_PTR)this;
		GET_SINGLE(EventManager)->AddEvent(evt);
	}
}

void TextUI::Render(HDC _hdc)
{
	Vec2 vPos;
	if (m_bIsPopup)
		vPos = GET_SINGLE(Camera)->GetRenderPos(GetPos());
	else
		vPos = GetFinalPos();

	HFONT oldFont = (HFONT)SelectObject(_hdc, m_font);
	SetTextAlign(_hdc, m_uAlign);
	SetTextColor(_hdc, RGB(255, 255, 255));
	SetBkMode(_hdc, TRANSPARENT);
	TextOut(_hdc, vPos.x, vPos.y, m_wText.c_str(), m_wText.size());

	SelectObject(_hdc, oldFont);
}
