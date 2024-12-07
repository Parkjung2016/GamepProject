#include "pch.h"
#include "PlayerReloadGunState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"

#include "Enums.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerReloadGunState::PlayerReloadGunState() : PlayerState(PLAYER_STATE::RELOADGUN),
                                               m_bAnimationTrigger(false)
{
}

PlayerReloadGunState::~PlayerReloadGunState()
{
}

void PlayerReloadGunState::Update()
{
	Animator* animator = GetPlayer()->GetComponent<Animator>();
	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	float yVelocity = pRigid->GetVelocity().y;
	pRigid->SetVelocity({ 0.f, yVelocity });
	if (animator->GetCurrentAnim()->GetCurFrame() == 15 && !m_bAnimationTrigger)
	{
		m_bAnimationTrigger = true;
		GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Player/ReloadShotGun", GET_SINGLE(Camera)->GetLookAt());


		GetPlayer()->ReloadGun();
	}
	if (animator->GetCurrentAnim()->IsFinished())
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerReloadGunState::Enter()
{
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"ReloadGun", false);
}

void PlayerReloadGunState::Exit()
{
	m_bAnimationTrigger = false;
}
