#pragma once
#include "UI.h"
class PanelUI :
	public UI
{

public:
	PanelUI();
	~PanelUI() override;

public:
	void MouseOn() override;
	void MouseLBDown() override;
	void MouseLBUp() override;
	void MouseLBClicked() override;
	CLONE(PanelUI);
private:
	Vec2 m_vDragStart;
};

