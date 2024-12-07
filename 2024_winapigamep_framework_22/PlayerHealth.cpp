#include "pch.h"
#include "PlayerHealth.h"

#include "Audio.h"
#include "Enemy.h"
#include "Player.h"

PlayerHealth::PlayerHealth() : m_pPlayer(nullptr)
{
}

PlayerHealth::~PlayerHealth()
{
}

void PlayerHealth::ApplyDamage(CombatData combatData)
{
	if (m_bIsDead)return;
	if (m_pPlayer->IsBlocking())
	{
		Enemy* pENemy = (Enemy*)(combatData.pDealer);
		if (pENemy)
		{
			GetOwner()->GetComponent<Audio>()->PlayEvent("event:/SFX/Player/AttackBlock");

			pENemy->FreezeMove(3);
		}
		return;
	}
	Health::ApplyDamage(combatData);
}

void PlayerHealth::SetOwner(Object* _owner)
{
	Health::SetOwner(_owner);
	m_pPlayer = (Player*)_owner;
}

