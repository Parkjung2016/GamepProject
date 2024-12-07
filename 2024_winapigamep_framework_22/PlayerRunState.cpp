#include "pch.h"
#include "PlayerRunState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
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
	Animation* currentAnim = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim();
	size_t curFrame = currentAnim->GetCurFrame();
	if ((curFrame == 4 || curFrame == 9))
	{
		if (!m_bIsSoundTriggered)
		{

			m_bIsSoundTriggered = true;
			GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Footstep", GET_SINGLE(Camera)->GetLookAt());

		}
	}
	else
		m_bIsSoundTriggered = false;
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
