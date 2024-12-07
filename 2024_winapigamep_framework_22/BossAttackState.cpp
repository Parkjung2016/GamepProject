#include "pch.h"
#include "BossAttackState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"

BossAttackState::BossAttackState() : BossState(BOSS_STATE::ATTACK)
{
}

BossAttackState::~BossAttackState()
{
}

void BossAttackState::Update()
{
	auto playerHealth = GetBoss()->GetPlayer()->GetComponent<Health>();
	if (playerHealth->GetIsDead())
	{
		GetStateMachine()->ChangeState(BOSS_STATE::IDLE);
		return;
	}
	Animator* pAnimator = GetBoss()->GetComponent<Animator>();

	if (pAnimator->GetCurrentAnim()->GetCurFrame() == 2 && !m_bAnimationTrigger)
	{
		m_bAnimationTrigger = true;
		float fAttackRange = GetBoss()->GetInfo().fAttackRange;
		GetBoss()->GetComponent<Audio>()->PlayEvent("event:/SFX/Boss/AttackSwing");

		if (GetBoss()->IsPlayerInFront() && GetBoss()->IsPlayerInRange(fAttackRange))
		{

			auto info = GetBoss()->GetInfo();
			Vec2 vOtherPos = GetBoss()->GetPlayer()->GetPos();

			Vec2 vPos = GetBoss()->GetPos();
			Vec2 dis = (vOtherPos - vPos);
			dis.y = -20;
			Vec2 vKnockBackDir = dis.Normalize();
			CombatData combatData
			{
				GetBoss(),
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
		GetStateMachine()->ChangeState(BOSS_STATE::RECOVER);
	}
}

void BossAttackState::Enter()
{

	Animator* pAnimator = GetBoss()->GetComponent<Animator>();
	Player* pPlayer = GetBoss()->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = GetBoss()->GetPos();

	pAnimator->SetIsRotate(vPlayerpos.x < vEnemyPos.x);
	Rigidbody* pRigid = GetBoss()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	pAnimator->PlayAnimation(L"Attack", false);
}

void BossAttackState::Exit()
{
	m_bAnimationTrigger = false;
}
