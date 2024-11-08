#pragma once
#include "Component.h"
class Gravity :
	public Component
{
public:
	Gravity();
	~Gravity() override;
private:
	bool m_bGround;

public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;

public:
	void SetGround(bool _b);
};

