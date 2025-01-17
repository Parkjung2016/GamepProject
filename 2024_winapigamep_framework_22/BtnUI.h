#pragma once
#include "UI.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);
class BtnUI :
	public UI
{

public:
	BtnUI();
	~BtnUI() override;
public:
	void MouseOn() override;
	void MouseLBDown() override;
	void MouseLBUp() override;
	void MouseLBClicked() override;
	void Render(HDC _hdc) override;
	void SetClickedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
	{
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetNormalTexture(const wstring& _wKey, const wstring& _wPath);
	void SetPressTexture(const wstring& _wKey, const wstring& _wPath);
	CLONE(BtnUI)

private:
	Texture* m_pNormalTex;
	Texture* m_pPressTex;
	BTN_FUNC m_pFunc;
	DWORD_PTR m_param1;
	DWORD_PTR m_param2;
};

