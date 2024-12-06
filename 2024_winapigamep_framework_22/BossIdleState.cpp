#include "pch.h"
#include "BossIdleState.h"

#include "Animator.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"

BossIdleState::BossIdleState() : BossState(BOSS_STATE::IDLE)
{
}

BossIdleState::~BossIdleState()
{
}

void BossIdleState::Update()
{
	Boss* pBoss = GetBoss();
	float fRecogRange = pBoss->GetInfo().fRecogRange;
	bool bPlayerIsDead = pBoss->GetPlayer()->GetComponent<Health>()->GetIsDead();

	if (!bPlayerIsDead && pBoss->IsPlayerInRange(fRecogRange))
	{
		GetStateMachine()->ChangeState(BOSS_STATE::TRACE);
	}
}

void BossIdleState::Enter()
{
	Rigidbody* pRigid = GetBoss()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
}

void BossIdleState::Exit()
{
}
