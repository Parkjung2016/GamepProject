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
			auto playerHealth = GetEnemy()->GetPlayer()->GetComponent<Health>();
			if (playerHealth->GetIsDead())return;
			auto info = GetEnemy()->GetInfo();
			Vec2 vOtherPos = GetEnemy()->GetPlayer()->GetPos();

			Vec2 vPos = GetEnemy()->GetPos();
			Vec2 dis = (vOtherPos - vPos);
			dis.y = -20;
			Vec2 vKnockBackDir = dis.Normalize();
			CombatData combatData
			{
				info.iPower,
				vKnockBackDir,
				info.fAttackKnockBackPower,
				info.fAttackKnockBackDuration

			};
			playerHealth->ApplyDamage(combatData);
		}
	}

	if (animator->GetCurrentAnim()->IsFinished())
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::RECOVER);
	}
}

void EnemyAttackState::Enter()
{
	Animator* animator = GetEnemy()->GetComponent<Animator>();
	Player* pPlayer = GetEnemy()->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = GetEnemy()->GetPos();

	animator->SetIsRotate(vPlayerpos.x < vEnemyPos.x);
	GetEnemy()->GetComponent<Rigidbody>()->SetVelocity({ 0.f,0.f });
	animator->PlayAnimation(L"Attack", false);

}

void EnemyAttackState::Exit()
{
	_animationTrigger = false;
}
