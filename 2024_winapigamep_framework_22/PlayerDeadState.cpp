#include "pch.h"
#include "PlayerDeadState.h"

#include "Animator.h"
#include "Collider.h"
#include "Gravity.h"
#include "Health.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerDeadState::PlayerDeadState() : PlayerState(PLAYER_STATE::DEAD)
{
}

PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::Update()
{
}

void PlayerDeadState::Enter()
{
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
