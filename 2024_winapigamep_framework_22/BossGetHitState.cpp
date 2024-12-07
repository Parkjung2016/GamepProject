#include "pch.h"
#include "BossGetHitState.h"

#include "Animator.h"
#include "Audio.h"
#include "Boss.h"
#include "BossRecoverState.h"
#include "BossStateMachine.h"
#include "Health.h"
#include "Rigidbody.h"
#include "TimeManager.h"

BossGetHitState::BossGetHitState() : BossState(BOSS_STATE::GETHIT),
m_fCurrentKnockBackDuration(0)
{
}

BossGetHitState::~BossGetHitState()
{
}

void BossGetHitState::Update()
{
	CombatData combatData = GetBoss()->GetComponent<Health>()->GetCombatData();
	if (m_fCurrentKnockBackDuration <= combatData.fKnockBackDuration)
	{

		GetBoss()->GetComponent<Rigidbody>()->SetVelocity(combatData.vKnockBackDir * combatData.fKnockBackPower);
		m_fCurrentKnockBackDuration += fDT;
	}
	else
	{
		GetBoss()->GetComponent<Rigidbody>()->SetVelocity({ 0,0 });
		GetStateMachine()->ChangeState(BOSS_STATE::RECOVER);

		BossState* state = GetStateMachine()->GetState(BOSS_STATE::RECOVER);
		dynamic_cast<BossRecoverState*>(state)->SetWaitTime(.3f);

	}
}

void BossGetHitState::Enter()
{
	GetBoss()->GetComponent<Audio>()->PlayEvent("event:/SFX/Zombie/ZombieImpact");

	GetBoss()->GetComponent<Animator>()->SetIsHit(true);
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"GetHit", false);
}

void BossGetHitState::Exit()
{
	GetBoss()->GetComponent<Animator>()->SetIsHit(false);
	m_fCurrentKnockBackDuration = 0;
}
