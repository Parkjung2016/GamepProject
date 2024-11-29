#pragma once
#include "UI.h"
class PanelUI :
	public UI
{

public:
	PanelUI();
	PanelUI(bool _bCanMovePanel);
	~PanelUI() override;

public:
	void MouseOn() override;
	void MouseLBDown() override;
	void MouseLBUp() override;
	void MouseLBClicked() override;
	CLONE(PanelUI);
private:
	bool m_bCanMovePanel;
	Vec2 m_vDragStart;
};

