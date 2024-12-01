#include "pch.h"
#include "PlayerRunState.h"

#include "Animator.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerRunState::PlayerRunState() : PlayerGroundState(PLAYER_STATE::RUN)
{
}

PlayerRunState::~PlayerRunState()
{
}

void PlayerRunState::Update()
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
	if (!GetPlayer()->GetIsPressRunInput())
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::WALK);
		return;
	}
	tPlayerInfo info = player->GetInfo();
	player->GetComponent<Animator>()->SetIsRotate(iInput == -1);
	Vec2 velocity = pRigid->GetVelocity();
	pRigid->SetVelocity({ info.fRunSpeed * iInput,velocity.y });

}

void PlayerRunState::Enter()
{
	PlayerGroundState::Enter();

	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Run", true);
}

void PlayerRunState::Exit()
{
}
