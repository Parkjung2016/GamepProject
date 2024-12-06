#include "pch.h"
#include "BossState.h"

#include "BossStateMachine.h"


BossState::BossState(BOSS_STATE _eState)
	: m_pStateMachine(nullptr), m_eState(_eState)
{
}

BossState::~BossState()
{
}


Boss* BossState::GetBoss() const
{
	return m_pStateMachine->GetOwner();
}
