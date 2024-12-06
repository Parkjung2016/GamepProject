#pragma once
#include "Health.h"
class Player;
class PlayerHealth :
	public Health
{
public:
	PlayerHealth();
	~PlayerHealth() override;
public:
	void ApplyDamage(CombatData combatData) override;
	void SetOwner(Object* _owner) override;
private:
	Player* m_pPlayer;

};

