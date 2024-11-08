#include "pch.h"
#include "PlayerJumpState.h"

#include "Player.h"
#include "Rigidbody.h"

PlayerJumpState::PlayerJumpState() : PlayerState(PLAYER_STATE::JUMP)
{
}

PlayerJumpState::~PlayerJumpState()
{
}

void PlayerJumpState::Update()
{
}

void PlayerJumpState::Enter()
{
	float fJumpPower = GetPlayer()->GetInfo().fJumpPower;
	GetPlayer()->GetComponent<Rigidbody>()->AddForce({ 0.f,fJumpPower });
}

void PlayerJumpState::Exit()
{
}
