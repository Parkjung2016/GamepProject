#include "pch.h"
#include "PlayerStateMachine.h"

#include "Func.h"
#include "PlayerState.h"

PlayerStateMachine::PlayerStateMachine()
	: m_pCurState(nullptr),
	m_pOwner(nullptr)
{
}

PlayerStateMachine::~PlayerStateMachine()
{
	SafeDeleteMap(m_mapState);
}

void PlayerStateMachine::Update()
{
	if (nullptr != m_pCurState)
		m_pCurState->Update();
}

void PlayerStateMachine::AddState(PlayerState* _pState)
{
	PlayerState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.insert({ _pState->GetType() ,_pState });
	_pState->m_pStateMachine = this;
}

PlayerState* PlayerStateMachine::GetState(PLAYER_STATE _eState)
{

	map<PLAYER_STATE, PlayerState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;

}

void PlayerStateMachine::SetCurState(PLAYER_STATE _eState)
{
	m_pCurState = GetState(_eState);
	m_pCurState->Enter();
	assert(m_pCurState);
}

void PlayerStateMachine::ChangeState(PLAYER_STATE _eNextState)
{
	PlayerState* pNextState = GetState(_eNextState);

	assert(m_pCurState != pNextState);
	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}
