#include "pch.h"
#include "Health.h"

Health::~Health()
{
}

void Health::LateUpdate()
{
}

void Health::Render(HDC _hdc)
{
}

void Health::ApplyDamage(int iDamage)
{
	m_iHp -= iDamage;
	onApplyDamaged.invoke();
	onHealthChanged.invoke(m_iHp);
}

Health::Health()
{
}
