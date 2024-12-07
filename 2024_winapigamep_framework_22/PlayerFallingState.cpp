#include "pch.h"
#include "PlayerFallingState.h"

#include "Animator.h"
#include "Audio.h"
#include "Gravity.h"
#include "Player.h"
#include "PlayerStateMachine.h"

PlayerFallingState::PlayerFallingState() : PlayerAirState(PLAYER_STATE::FALLING)
{
}

PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update()
{
	PlayerAirState::Update();
	bool bIsGrounded = GetPlayer()->GetComponent<Gravity>()->IsGrounded();
	if (bIsGrounded)
	{
		GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Footstep", GET_SINGLE(Camera)->GetLookAt());

		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerFallingState::Enter()
{
	GetPlayer()->GetComponent<Gravity>()->SetCanGravity(true);

	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"JumpDown", false);

}

void PlayerFallingState::Exit()
{
}
