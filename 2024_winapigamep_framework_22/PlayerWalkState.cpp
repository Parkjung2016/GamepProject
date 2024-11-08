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

	int iInput = player->GetInput();
	tPlayerInfo info = player->GetInfo();
	//Vec2 size = player->GetSize();
	//float xSize = abs(size.x);
	//size.x = xSize * -1;
	//player->SetSize(size);
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
