#include "pch.h"
#include "EnemyAttackState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"

EnemyAttackState::EnemyAttackState() : EnemyState(ENEMY_STATE::ATTACK),
m_bAnimationTrigger(false)
{
}

EnemyAttackState::~EnemyAttackState()
{
}

void EnemyAttackState::Update()
{
	auto playerHealth = GetEnemy()->GetPlayer()->GetComponent<Health>();
	Animator* pAnimator = GetEnemy()->GetComponent<Animator>();

	if (!playerHealth->GetIsDead() && pAnimator->GetCurrentAnim()->GetCurFrame() == 2 && !m_bAnimationTrigger)
	{
		m_bAnimationTrigger = true;
		float fAttackRange = GetEnemy()->GetInfo().fAttackRange + 50;
		GetEnemy()->GetComponent<Audio>()->PlayEvent("event:/SFX/Zombie/ZombieBite");

		if (GetEnemy()->IsPlayerInFront() && GetEnemy()->IsPlayerInRange(fAttackRange))
		{

			auto info = GetEnemy()->GetInfo();
			Vec2 vOtherPos = GetEnemy()->GetPlayer()->GetPos();

			Vec2 vPos = GetEnemy()->GetPos();
			Vec2 dis = (vOtherPos - vPos);
			dis.y = -20;
			Vec2 vKnockBackDir = dis.Normalize();
			CombatData combatData
			{
				GetEnemy(),
				info.iPower,
				vKnockBackDir,
				info.fAttackKnockBackPower,
				info.fAttackKnockBackDuration

			};
			playerHealth->ApplyDamage(combatData);
		}
	}

	if (pAnimator->GetCurrentAnim()->IsFinished())
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::RECOVER);
	}
}

void EnemyAttackState::Enter()
{
	Animator* pAnimator = GetEnemy()->GetComponent<Animator>();
	Player* pPlayer = GetEnemy()->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = GetEnemy()->GetPos();

	pAnimator->SetIsRotate(vPlayerpos.x < vEnemyPos.x);
	Rigidbody* pRigid = GetEnemy()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	pAnimator->PlayAnimation(L"Attack", false);

}

void EnemyAttackState::Exit()
{
	m_bAnimationTrigger = false;
}
