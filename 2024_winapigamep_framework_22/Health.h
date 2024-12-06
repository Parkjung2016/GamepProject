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
	virtual void ApplyDamage(CombatData _combatData) override;
	void SetMaxHealth(int _iMaxHealth);
	int GetCurrentHealth() const { return m_iCurrentHealth; }
	int GetMaxHealth() const { return m_iMaxHealth; }
	bool GetIsDead()const { return m_bIsDead; }
	void SetDead() { m_bIsDead = true; }
	void SetCombatData(CombatData _combatData) { m_combatData = _combatData; }
	CombatData GetCombatData() { return m_combatData; }
public:
	Action<int> onHealthChanged;
	Action<> onApplyDamaged;
	Action<> onDead;

protected:
	CombatData m_combatData;
	int m_iCurrentHealth;
	int m_iMaxHealth;
	bool m_bIsDead;

};

