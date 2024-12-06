#include "pch.h"
#include "BossDeadState.h"

#include "Animation.h"
#include "Animator.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "EventManager.h"
#include "Gravity.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"
#include "TimeManager.h"

BossDeadState::BossDeadState() : BossState(BOSS_STATE::DEAD)
{
}

BossDeadState::~BossDeadState()
{
}

void BossDeadState::Update()
{
	Animator* pAnimator = GetBoss()->GetPlayer()->GetComponent<Animator>();
	if (!pAnimator->GetCurrentAnim()->IsFinished())return;


	if (m_bTriggered)
	{
		if (m_fCurrentChangeSceneTime <= 2)
		{
			m_fCurrentChangeSceneTime += fDT;
		}
		else
		{
			tEvent evt;
			evt.lParam = (DWORD_PTR)SCENE_TYPE::Title;
			evt.eveType = EVENT_TYPE::SCENE_CHANGE;
			GET_SINGLE(EventManager)->AddEvent(evt);
		}
	}
	if (m_fCurrentDestroyTime <= 1.5f)
	{
		m_fCurrentDestroyTime += fDT;
	}
	else if (!m_bTriggered)
	{
		m_bTriggered = true;
		GET_SINGLE(Camera)->FadeOut(1.f);
	}
}

void BossDeadState::Enter()
{
	GetStateMachine()->SetCanChangeState(false);
	GetBoss()->GetComponent<Health>()->SetDead();
	GetBoss()->RemoveComponent<Collider>();
	GetBoss()->RemoveComponent<Rigidbody>();
	GetBoss()->RemoveComponent<Gravity>();
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"Dead", false);
}

void BossDeadState::Exit()
{
}
