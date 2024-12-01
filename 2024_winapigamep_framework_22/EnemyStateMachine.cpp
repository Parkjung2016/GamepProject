#include "pch.h"
#include "EnemyStateMachine.h"

#include "MyFunc.h"
#include "EnemyState.h"

EnemyStateMachine::EnemyStateMachine()
	: m_pCurState(nullptr),
	m_pOwner(nullptr),
	m_bCanChangeState(true)
{
}

EnemyStateMachine::~EnemyStateMachine()
{
	SafeDeleteMap(m_mapState);
}

void EnemyStateMachine::Update()
{
	if (nullptr != m_pCurState)
		m_pCurState->Update();
}

void EnemyStateMachine::AddState(EnemyState* _pState)
{
	EnemyState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.insert({ _pState->GetType() ,_pState });
	_pState->m_pStateMachine = this;
}

EnemyState* EnemyStateMachine::GetState(ENEMY_STATE _eState)
{

	map<ENEMY_STATE, EnemyState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;

}

void EnemyStateMachine::SetCurState(ENEMY_STATE _eState)
{
	m_pCurState = GetState(_eState);
	m_pCurState->Enter();
	assert(m_pCurState);
}

void EnemyStateMachine::ChangeState(ENEMY_STATE _eNextState)
{
	if (!m_bCanChangeState)return;
	EnemyState* pNextState = GetState(_eNextState);

	//assert(m_pCurState != pNextState);
	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}
