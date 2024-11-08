#include "pch.h"
#include "PlayerIdleState.h"

#include "Animator.h"
#include "InputManager.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "Player.h"


PlayerIdleState::PlayerIdleState() : PlayerGroundState(PLAYER_STATE::IDLE)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Update()
{
	PlayerGroundState::Update();
	if (GetPlayer()->GetInput() != 0)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::WALK);
	}

}

void PlayerIdleState::Enter()
{
	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });

	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);


}

void PlayerIdleState::Exit()
{
}
