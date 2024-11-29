#pragma once

class IDamageable
{
public:
	virtual void ApplyDamage(CombatData combatData) = 0;
	virtual ~IDamageable() = default;

};