#include "pch.h"
#include "PlayerGetHitState.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "PlayerStateMachine.h"

PlayerGetHitState::PlayerGetHitState() : PlayerState(PLAYER_STATE::GETHIT)
{
}

PlayerGetHitState::~PlayerGetHitState()
{
}

void PlayerGetHitState::Update()
{
	bool isFinishedAnimation = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim()->IsFinished();
	if (isFinishedAnimation)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerGetHitState::Enter()
{
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"GetHit", false);

}

void PlayerGetHitState::Exit()
{
}
