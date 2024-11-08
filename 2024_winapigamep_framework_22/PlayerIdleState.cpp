#include "pch.h"
#include "PlayerIdleState.h"

#include "Animator.h"
#include "InputManager.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "Player.h"


PlayerIdleState::PlayerIdleState() : PlayerState(PLAYER_STATE::IDLE)
{
}

PlayerIdleState::~PlayerIdleState()
{
}

void PlayerIdleState::Update()
{
	if (GetPlayer()->GetInput() != 0)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::WALK);
	}

}

void PlayerIdleState::Enter()
{
	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	pRigid->SetVelocity({ 0,0 });

	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);


}

void PlayerIdleState::Exit()
{
}
