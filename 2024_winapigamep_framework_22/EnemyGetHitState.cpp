#include "pch.h"
#include "EnemyGetHitState.h"

#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "EnemyRecoverState.h"
#include "EnemyStateMachine.h"
#include "Health.h"
#include "Rigidbody.h"
#include "TimeManager.h"


EnemyGetHitState::EnemyGetHitState() : EnemyState(ENEMY_STATE::GETHIT)
{
}

EnemyGetHitState::~EnemyGetHitState()
{
}

void EnemyGetHitState::Update()
{
	CombatData combatData = GetEnemy()->GetComponent<Health>()->GetCombatData();
	if (m_fCurrentKnockBackDuration <= combatData.fKnockBackDuration)
	{

		GetEnemy()->GetComponent<Rigidbody>()->SetVelocity(combatData.vKnockBackDir * combatData.fKnockBackPower);
		m_fCurrentKnockBackDuration += fDT;
	}
	else
	{
		GetEnemy()->GetComponent<Rigidbody>()->SetVelocity({ 0,0 });
		GetStateMachine()->ChangeState(ENEMY_STATE::RECOVER);

		EnemyState* state = GetStateMachine()->GetState(ENEMY_STATE::RECOVER);
		dynamic_cast<EnemyRecoverState*>(state)->SetWaitTime(.3f);

	}
}

void EnemyGetHitState::Enter()
{
	GetEnemy()->GetComponent<Animator>()->SetIsHit(true);
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"GetHit", false);

}

void EnemyGetHitState::Exit()
{
	GetEnemy()->GetComponent<Animator>()->SetIsHit(false);
	m_fCurrentKnockBackDuration = 0;
}
