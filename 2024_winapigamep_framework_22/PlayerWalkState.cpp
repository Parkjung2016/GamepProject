#include "pch.h"
#include "PlayerWalkState.h"

#include "Animator.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerWalkState::PlayerWalkState() : PlayerGroundState(PLAYER_STATE::WALK)
{
}

PlayerWalkState::~PlayerWalkState()
{
}

void PlayerWalkState::Update()
{
	PlayerGroundState::Update();
	Player* player = GetPlayer();
	Rigidbody* pRigid = player->GetComponent<Rigidbody>();

	int iInput = player->GetMoveInput();
	if (iInput == 0)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
		return;
	}
	if (GetPlayer()->GetIsPressRunInput())
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::RUN);
		return;
	}
	tPlayerInfo info = player->GetInfo();
	player->GetComponent<Animator>()->SetIsRotate(iInput == -1);
	Vec2 velocity = pRigid->GetVelocity();
	pRigid->SetVelocity({ info.fWalkSpeed * iInput,velocity.y });

}

void PlayerWalkState::Enter()
{
	PlayerGroundState::Enter();

	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Walk", true);
}

void PlayerWalkState::Exit()
{
}
