#pragma once
#include "UI.h"
class PanelUI :
	public UI
{

public:
	PanelUI();
	~PanelUI() override;

public:
	void Render(HDC _hdc) override;

	void SetTexture(const wstring& _wKey, const wstring& _wPath);

	CLONE(PanelUI);
private:
	Texture* m_pTex;

};

