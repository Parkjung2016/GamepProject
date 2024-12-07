#include "pch.h"
#include "PlayerWalkState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "AudioSystem.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "SoundEvent.h"

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

	Animation* currentAnim = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim();
	size_t curFrame = currentAnim->GetCurFrame();
	if ((curFrame == 2 || curFrame == 6))
	{
		if (!m_bIsSoundTriggered)
		{

			m_bIsSoundTriggered = true;
			GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Footstep", GET_SINGLE(Camera)->GetLookAt());

		}
	}
	else
		m_bIsSoundTriggered = false;

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
