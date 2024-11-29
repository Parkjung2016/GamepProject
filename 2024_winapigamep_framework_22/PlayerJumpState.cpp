#include "pch.h"
#include "PlayerJumpState.h"
#include "Animator.h"
#include "Gravity.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerJumpState::PlayerJumpState() : PlayerAirState(PLAYER_STATE::JUMP)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Update()
{
	PlayerAirState::Update();
	float fYVelocity = GetPlayer()->GetComponent<Rigidbody>()->GetVelocity().y;
	if (fYVelocity > 5)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::FALLING);
		return;
	}

	bool bIsGrounded = GetPlayer()->GetComponent<Gravity>()->IsGrounded();
	if (bIsGrounded)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerJumpState::Enter()
{
	PlayerAirState::Enter();
	float fJumpPower = -GetPlayer()->GetInfo().fJumpPower;
	GetPlayer()->GetComponent<Rigidbody>()->AddVelocity({ 0.f,fJumpPower });
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"JumpUp", false);

}

void PlayerJumpState::Exit()
{

}
