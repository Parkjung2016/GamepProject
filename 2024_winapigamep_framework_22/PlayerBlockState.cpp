#include "pch.h"
#include "PlayerBlockState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerBlockState::PlayerBlockState() : PlayerState(PLAYER_STATE::BLOCK)
{
}

PlayerBlockState::~PlayerBlockState()
{
}

void PlayerBlockState::Update()
{
	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	Animation* currentAnim = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim();
	bool isFinishedAnimation = currentAnim->IsFinished();
	if (isFinishedAnimation)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerBlockState::Enter()
{
	GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Player/Swing", GET_SINGLE(Camera)->GetLookAt());

	GetPlayer()->SetBlocking(true);
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Block", false);

}

void PlayerBlockState::Exit()
{
	GetPlayer()->SetBlocking(false);

}
