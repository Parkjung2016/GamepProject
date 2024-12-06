#include "pch.h"
#include "BossDashAttackState.h"

#include "Animation.h"
#include "Animator.h"
#include "Boss.h"
#include "BossRecoverState.h"
#include "BossStateMachine.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"

BossDashAttackState::BossDashAttackState() : BossState(BOSS_STATE::DASHATTACK)
{
}

BossDashAttackState::~BossDashAttackState()
{
}

void BossDashAttackState::Update()
{
	auto playerHealth = GetBoss()->GetPlayer()->GetComponent<Health>();
	Animator* pAnimator = GetBoss()->GetComponent<Animator>();
	if (pAnimator->GetCurrentAnim()->GetCurFrame() == 2 && !m_bAnimationTrigger)
	{
		m_bAnimationTrigger = true;
		auto info = GetBoss()->GetInfo();
		Rigidbody* pRigid = GetBoss()->GetComponent<Rigidbody>();
		int dashDir = pAnimator->GetIsRotate() ? -1 : 1;
		Vec2 velocity = pRigid->GetVelocity();
		pRigid->SetVelocity({ dashDir * info.fDashSpeed,velocity.y });
		float fDashAttackRange = GetBoss()->GetInfo().fDashAttackRange;

		if (GetBoss()->IsPlayerInFront() && GetBoss()->IsPlayerInRange(fDashAttackRange))
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

		BossState* state = GetStateMachine()->GetState(BOSS_STATE::RECOVER);
		dynamic_cast<BossRecoverState*>(state)->SetWaitTime(1.f);
		GetStateMachine()->ChangeState(BOSS_STATE::RECOVER);
	}
}

void BossDashAttackState::Enter()
{
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"DashAttack", false);
}

void BossDashAttackState::Exit()
{
	m_bAnimationTrigger = false;
}
