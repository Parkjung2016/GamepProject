#include "pch.h"
#include "EnemyDeadState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "Gravity.h"
#include "Health.h"
#include "MyFunc.h"
#include "Player.h"
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
	Animator* pAnimator = GetEnemy()->GetComponent<Animator>();
	if (!pAnimator->GetCurrentAnim()->IsFinished())return;
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
	GetEnemy()->GetComponent<Audio>()->StopAllEvents();
	GetEnemy()->GetComponent<Audio>()->PlayEvent("event:/SFX/Zombie/ZombieDead");

	GetStateMachine()->SetCanChangeState(false);
	GetEnemy()->GetPlayer()->AddDashableCount();
	GetEnemy()->GetComponent<Health>()->SetDead();
	GetEnemy()->RemoveComponent<Collider>();
	GetEnemy()->RemoveComponent<Rigidbody>();
	GetEnemy()->RemoveComponent<Gravity>();
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Dead", false);

}

void EnemyDeadState::Exit()
{
}
