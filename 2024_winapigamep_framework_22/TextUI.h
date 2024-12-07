#pragma once
#include "UI.h"
class TextUI :
	public UI
{
public:
	TextUI();
	TextUI(bool _bIsPopup, float _fFontSize);
	~TextUI() override;

public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void SetAlign(UINT _uAlign) { m_uAlign = _uAlign; }
	void SetText(const wstring& _wText) { m_wText = _wText; }
	CLONE(TextUI)

private:
	UINT m_uAlign;
	bool m_bIsPopup;
	float m_fFontSize;
	float m_fCurrentDestroyTime;
	wstring m_wText;
	HFONT m_font;
};

