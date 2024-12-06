#include "pch.h"
#include "PlayerBlockState.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "PlayerStateMachine.h"

PlayerBlockState::PlayerBlockState() : PlayerState(PLAYER_STATE::BLOCK)
{
}

PlayerBlockState::~PlayerBlockState()
{
}

void PlayerBlockState::Update()
{
	Animation* currentAnim = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim();
	bool isFinishedAnimation = currentAnim->IsFinished();
	if (isFinishedAnimation)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
		return;
	}
}

void PlayerBlockState::Enter()
{
	GetPlayer()->SetBlocking(true);
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Block", false);

}

void PlayerBlockState::Exit()
{
	GetPlayer()->SetBlocking(false);

}
