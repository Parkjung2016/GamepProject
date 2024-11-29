#include "pch.h"
#include "Health.h"

Health::Health() : m_combatData(), m_iHp(0), m_bIsDead(false)
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

void Health::ApplyDamage(CombatData combatData)
{
	if (m_bIsDead)return;
	m_combatData = combatData;
	m_iHp -= combatData.iDamage;
	onApplyDamaged.invoke();
	onHealthChanged.invoke(m_iHp);

	if (m_iHp <= 0)
	{
		m_bIsDead = true;
		onDead.invoke();
	}
}
