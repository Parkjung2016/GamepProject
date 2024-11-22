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
	tPlayerInfo info = player->GetInfo();
	if (iInput != 0)
	{
		player->GetComponent<Animator>()->SetIsRotate(iInput == -1);
	}
	Vec2 velocity = pRigid->GetVelocity();
	pRigid->SetVelocity({ iInput * info.fWalkSpeed,velocity.y });
	if (iInput == 0)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerWalkState::Enter()
{
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Walk", true);
}

void PlayerWalkState::Exit()
{
}
