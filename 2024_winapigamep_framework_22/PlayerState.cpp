#include "pch.h"
#include "PlayerState.h"

#include "PlayerStateMachine.h"


PlayerState::PlayerState(PLAYER_STATE _eState)
	: m_pStateMachine(nullptr), m_eState(_eState)
{
}

PlayerState::~PlayerState()
{
}


Player* PlayerState::GetPlayer() const
{
	return m_pStateMachine->GetOwner();
}
