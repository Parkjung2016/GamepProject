#include "pch.h"
#include "PlayerGetHitState.h"

#include "Animator.h"
#include "Audio.h"
#include "Health.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"
#include "TimeManager.h"

PlayerGetHitState::PlayerGetHitState() : PlayerState(PLAYER_STATE::GETHIT)
{
}

PlayerGetHitState::~PlayerGetHitState()
{
}

void PlayerGetHitState::Update()
{
	CombatData combatData = GetPlayer()->GetComponent<Health>()->GetCombatData();
	if (m_fCurrentKnockBackDuration <= combatData.fKnockBackDuration)
	{

		GetPlayer()->GetComponent<Rigidbody>()->SetVelocity(combatData.vKnockBackDir * combatData.fKnockBackPower);
		m_fCurrentKnockBackDuration += fDT;
	}
	else
	{
		GetPlayer()->GetComponent<Rigidbody>()->SetVelocity({ 0,0 });
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
	}
}

void PlayerGetHitState::Enter()
{
	GetPlayer()->GetComponent<Audio>()->PlayEvent("event:/SFX/Player/PlayerImpact", GET_SINGLE(Camera)->GetLookAt());

	GetPlayer()->GetComponent<Animator>()->SetIsHit(true);
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"GetHit", false);
}

void PlayerGetHitState::Exit()
{
	GetPlayer()->GetComponent<Animator>()->SetIsHit(false);
	m_fCurrentKnockBackDuration = 0;

}
