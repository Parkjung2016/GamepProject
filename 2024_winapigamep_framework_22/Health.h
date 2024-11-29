#pragma once
#include "Action.h"
#include "Component.h"
#include "Interfaces.h"

class Health : public Component, public IDamageable
{
public:
	Health();
	~Health() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;

public:
	void ApplyDamage(CombatData combatData) override;
	void SetCombatData(CombatData _combatData) { m_combatData = _combatData; }
	CombatData GetCombatData() { return m_combatData; }
	bool GetIsDead() const { return m_bIsDead; }
public:
	Action<int> onHealthChanged;
	Action<> onApplyDamaged;
	Action<> onDead;

private:
	CombatData m_combatData;
	int m_iHp;
	bool m_bIsDead;

};

