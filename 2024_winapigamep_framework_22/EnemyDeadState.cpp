#include "pch.h"
#include "EnemyDeadState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "Gravity.h"
#include "Health.h"
#include "MyFunc.h"
#include "Rigidbody.h"
#include "TimeManager.h"

EnemyDeadState::EnemyDeadState() : EnemyState(ENEMY_STATE::DEAD),
m_fCurrentDestroyTime(0),
m_fDestroyTime(1)
{
}

EnemyDeadState::~EnemyDeadState()
{
}

void EnemyDeadState::Update()
{
	if (m_fCurrentDestroyTime <= m_fDestroyTime)
	{
		m_fCurrentDestroyTime += fDT;
	}
	else
	{
		DeleteObject(GetEnemy());
	}
}

void EnemyDeadState::Enter()
{
	GetStateMachine()->SetCanChangeState(false);
	GetEnemy()->GetComponent<Health>()->SetDead();
	GetEnemy()->RemoveComponent<Collider>();
	GetEnemy()->RemoveComponent<Rigidbody>();
	GetEnemy()->RemoveComponent<Gravity>();
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Dead", false);

}

void EnemyDeadState::Exit()
{
}
