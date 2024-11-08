#include "pch.h"
#include "EnemyState.h"

#include "EnemyStateMachine.h"

EnemyState::EnemyState(ENEMY_STATE _eState)
	: m_pStateMachine(nullptr), m_eState(_eState)
{
}

EnemyState::~EnemyState()
{
}


Enemy* EnemyState::GetEnemy() const
{
	return m_pStateMachine->GetOwner();
}
