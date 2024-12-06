#include "pch.h"
#include "PlayerDashState.h"

#include "Animator.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "TimeManager.h"

PlayerDashState::PlayerDashState() : PlayerState(PLAYER_STATE::DASH)
{
}

PlayerDashState::~PlayerDashState()
{
}

void PlayerDashState::Update()
{
	auto info = GetPlayer()->GetInfo();

	if (m_fCurrentDashTime <= info.fDashDuration)
	{
		m_fCurrentDashTime += fDT;
		Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
		int dashDir = GetPlayer()->GetComponent<Animator>()->GetIsRotate() ? -1 : 1;
		Vec2 velocity = pRigid->GetVelocity();
		pRigid->SetVelocity({ dashDir * info.fDashSpeed,velocity.y });
	}
	else
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}

}

void PlayerDashState::Enter()
{
	GetPlayer()->SubDashableCount();
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Dash", false);
}

void PlayerDashState::Exit()
{
	m_fCurrentDashTime = 0;
}
