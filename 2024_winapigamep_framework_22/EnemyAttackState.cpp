#include "pch.h"
#include "EnemyAttackState.h"

#include "Animation.h"
#include "Animator.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"

EnemyAttackState::EnemyAttackState() : EnemyState(ENEMY_STATE::ATTACK)
{
}

EnemyAttackState::~EnemyAttackState()
{
}

void EnemyAttackState::Update()
{
	Animator* animator = GetEnemy()->GetComponent<Animator>();

	if (animator->GetCurrentAnim()->GetCurFrame() == 2 && !_animationTrigger)
	{
		_animationTrigger = true;
		float fAttackRange = GetEnemy()->GetInfo().fAttackRange;

		if (GetEnemy()->IsPlayerInFront() && GetEnemy()->IsPlayerInRange(fAttackRange))
		{
			CombatData combatData
			{
				GetEnemy()->GetInfo().iPower
			};
			GetEnemy()->GetPlayer()->GetComponent<Health>()->ApplyDamage(combatData);
		}
	}

	if (animator->GetCurrentAnim()->IsFinished())
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::RECOVER);
	}
}

void EnemyAttackState::Enter()
{
	GetEnemy()->GetComponent<Rigidbody>()->SetVelocity({ 0.f,0.f });
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Attack", false);

}

void EnemyAttackState::Exit()
{
	_animationTrigger = false;
}
