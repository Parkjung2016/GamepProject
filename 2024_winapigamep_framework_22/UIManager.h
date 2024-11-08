#pragma once

class UI;
class UIManager
{
	DECLARE_SINGLE(UIManager)
private:
	UI* m_pFocusedUI;
public:
	void Init();
	void Update();

	void SetFocusedUI(UI* _pUI);
private:
	UI* GetFocusedUI() const;
	static UI* GetTargetedUI(UI* _pParentUI);
};

