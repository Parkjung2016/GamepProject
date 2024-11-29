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
	if (GET_KEYDOWN(KEY_TYPE::A))
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
	//GetPlayer()->GetComponent<Gravity>()->SetCanGravity(false);

}

void PlayerGroundState::Exit()
{
}
