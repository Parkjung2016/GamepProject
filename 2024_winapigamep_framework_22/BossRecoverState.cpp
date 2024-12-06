#include "pch.h"
#include "BossRecoverState.h"

#include "Animator.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "Rigidbody.h"
#include "TimeManager.h"

BossRecoverState::BossRecoverState() : BossState(BOSS_STATE::RECOVER),
m_fCurrentWaitTime(0),
m_fWaitTime(1)
{
}

BossRecoverState::~BossRecoverState()
{
}

void BossRecoverState::Update()
{
	if (m_fCurrentWaitTime <= m_fWaitTime)
	{
		m_fCurrentWaitTime += fDT;
	}
	else
	{
		GetStateMachine()->ChangeState(BOSS_STATE::IDLE);
	}
}

void BossRecoverState::Enter()
{
	m_fCurrentWaitTime = 0;
	Rigidbody* pRigid = GetBoss()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
}

void BossRecoverState::Exit()
{
	m_fCurrentWaitTime = 0;

}
