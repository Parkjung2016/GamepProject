#include "pch.h"
#include "PlayerIdleState.h"

#include "Animator.h"
#include "Gravity.h"
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
	if (GetPlayer()->GetMoveInput() != 0)
	{
		if (GetPlayer()->GetIsPressRunInput())
			GetStateMachine()->ChangeState(PLAYER_STATE::RUN);
		else
			GetStateMachine()->ChangeState(PLAYER_STATE::WALK);
		return;
	}

	bool bIsGrounded = GetPlayer()->GetComponent<Gravity>()->IsGrounded();
	if (!bIsGrounded)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::FALLING);
	}

}

void PlayerIdleState::Enter()
{
	PlayerGroundState::Enter();

	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);


}

void PlayerIdleState::Exit()
{
}
