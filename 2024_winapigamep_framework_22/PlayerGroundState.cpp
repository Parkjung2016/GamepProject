#include "pch.h"
#include "PlayerGroundState.h"

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
	if (GetPlayer()->CanReloadGun() && GET_KEYDOWN(KEY_TYPE::R))
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::RELOADGUN);
		return;
	}
	if (GetPlayer()->CanFireGun() && GET_KEYDOWN(KEY_TYPE::A))
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::ATTACK);
		return;
	}
	if (GET_KEYDOWN(KEY_TYPE::X))
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::BLOCK);
		return;
	}
	if (GetPlayer()->GetDashableCount() > 0 && GET_KEYDOWN(KEY_TYPE::C))
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::DASH);
		return;
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
