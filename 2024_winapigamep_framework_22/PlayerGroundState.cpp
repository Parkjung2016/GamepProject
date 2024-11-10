#include "pch.h"
#include "PlayerGroundState.h"

#include "Gravity.h"
#include "InputManager.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerGroundState::PlayerGroundState(PLAYER_STATE _eState) : PlayerState(_eState)
{
}

PlayerGroundState::~PlayerGroundState()
{
}

void PlayerGroundState::Update()
{
	float fYVelocity = GetPlayer()->GetComponent<Rigidbody>()->GetVelocity().y;
	if (fYVelocity > 0)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::FALLING);
		return;
	}

	if (GetPlayer()->GetIsPressAttackInput())
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::ATTACK);

	}
	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::JUMP);
	}
}

void PlayerGroundState::Enter()
{
}

void PlayerGroundState::Exit()
{
}
