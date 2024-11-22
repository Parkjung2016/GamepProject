#pragma once
#include "Action.h"
#include "Component.h"

class Health : public Component
{
public:
	Health();
	~Health() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;

public:
	void ApplyDamage(int iDamage);

public:
	Action<int> onHealthChanged;
	Action<> onApplyDamaged;

private:
	int m_iHp;


};

