#include "pch.h"
#include "PlayerDeadState.h"

#include "Animation.h"
#include "Animator.h"
#include "AudioSystem.h"
#include "Collider.h"
#include "EventManager.h"
#include "Gravity.h"
#include "Health.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "TimeManager.h"

PlayerDeadState::PlayerDeadState() : PlayerState(PLAYER_STATE::DEAD)
{
}

PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::Update()
{
	Animator* pAnimator = GetPlayer()->GetComponent<Animator>();
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

void PlayerDeadState::Enter()
{
	GET_SINGLE(AudioSystem)->SetBusVolume("bus:/", 0);
	//GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
	//GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::EFFECT);

	GetStateMachine()->SetCanChangeState(false);
	GetPlayer()->GetComponent<Health>()->SetDead();
	GetPlayer()->RemoveComponent<Collider>();
	GetPlayer()->RemoveComponent<Rigidbody>();
	GetPlayer()->RemoveComponent<Gravity>();
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Dead", false);
}

void PlayerDeadState::Exit()
{
}
