#include "pch.h"
#include "PlayerGroundState.h"

#include "InputManager.h"
#include "PlayerStateMachine.h"

PlayerGroundState::PlayerGroundState(PLAYER_STATE _eState) : PlayerState(_eState)
{
}

PlayerGroundState::~PlayerGroundState()
{
}

void PlayerGroundState::Update()
{
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
