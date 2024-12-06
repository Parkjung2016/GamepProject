#pragma once
#include "Object.h"
class UI :
	public Object
{
public:
	UI(bool _bCamAff);
	UI(const UI& _origin);
	virtual	~UI();
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;

protected:
	vector<UI*> m_vecChildUI;
	UI* m_pParentUI;
	Vec2 m_vFinalPos;

	bool m_bIgnored;
	bool m_bCamAffected;
	bool m_bMouseOn;
	bool m_bLBDown;

public:
	Vec2 GetFinalPos() const { return m_vFinalPos; }
	UI* GetParent() const { return m_pParentUI; }
	bool IsMouseOn() const { return m_bMouseOn; }
	bool IsLBDown()const { return m_bLBDown; }
	bool IsIgnored() const { return m_bIgnored; }
	void SetIgnored() { m_bIgnored = true; }
	void AddChild(UI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
	const vector<UI*>& GetChildUI() { return m_vecChildUI; }
protected:
	void Update_Child();
	void LateUpdate_Child();
	void Render_Child(HDC _hdc);

	void MouseOnCheck();
public:
	virtual void MouseOn();
	virtual void MouseLBDown();
	virtual void MouseLBUp();
	virtual void MouseLBClicked();

	virtual UI* Clone() = 0;
	friend class UIManager;

};

