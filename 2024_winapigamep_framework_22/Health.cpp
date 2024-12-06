#include "pch.h"
#include "Health.h"


Health::Health() : m_combatData(), m_iCurrentHealth(0), m_iMaxHealth(10), m_bIsDead(false)
{
}

Health::~Health()
{
}

void Health::LateUpdate()
{
}

void Health::Render(HDC _hdc)
{
}

void Health::ApplyDamage(CombatData _combatData)
{
	if (m_bIsDead)return;
	m_combatData = _combatData;
	m_iCurrentHealth -= _combatData.iDamage;
	if (m_iCurrentHealth <= 0)
	{
		m_iCurrentHealth = 0;
		SetDead();
		onDead.invoke();
	}
	onApplyDamaged.invoke();
	onHealthChanged.invoke(m_iCurrentHealth);
}

void Health::SetMaxHealth(int _iMaxHealth)
{
	m_iMaxHealth = _iMaxHealth;
	m_iCurrentHealth = _iMaxHealth;
	onHealthChanged.invoke(m_iCurrentHealth);
}
