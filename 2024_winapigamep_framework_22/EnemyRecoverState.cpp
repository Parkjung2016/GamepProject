#include "pch.h"
#include "EnemyRecoverState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "TimeManager.h"

EnemyRecoverState::EnemyRecoverState() : EnemyState(ENEMY_STATE::RECOVER),
m_fWaitTime(1), m_fCurrentWaitTime(0)
{
}

EnemyRecoverState::~EnemyRecoverState()
{
}

void EnemyRecoverState::Update()
{
	if (m_fCurrentWaitTime <= m_fWaitTime)
	{
		m_fCurrentWaitTime += fDT;
	}
	else
	{
		Enemy* pEnemy = GetEnemy();
		float fAttackRange = pEnemy->GetInfo().fAttackRange;
		if (pEnemy->IsPlayerInRange(fAttackRange))
		{
			GetStateMachine()->ChangeState(ENEMY_STATE::ATTACK);
		}
		else
			GetStateMachine()->ChangeState(ENEMY_STATE::IDLE);
	}
}

void EnemyRecoverState::Enter()
{
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);

}

void EnemyRecoverState::Exit()
{
	m_fCurrentWaitTime = 0;
}
