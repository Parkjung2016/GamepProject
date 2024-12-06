#include "pch.h"
#include "BossStateMachine.h"

#include "BossState.h"
#include "MyFunc.h"

BossStateMachine::BossStateMachine()
	: m_pCurState(nullptr),
	m_pOwner(nullptr),
	m_bCanChangeState(true)
{
}

BossStateMachine::~BossStateMachine()
{
	SafeDeleteMap(m_mapState);
}

void BossStateMachine::Update()
{
	if (nullptr != m_pCurState)
		m_pCurState->Update();
}

void BossStateMachine::AddState(BossState* _pState)
{
	BossState* pState = GetState(_pState->GetType());
	assert(!pState);

	m_mapState.insert({ _pState->GetType() ,_pState });
	_pState->m_pStateMachine = this;
}

BossState* BossStateMachine::GetState(BOSS_STATE _eState)
{

	map<BOSS_STATE, BossState*>::iterator iter = m_mapState.find(_eState);
	if (iter == m_mapState.end())
		return nullptr;

	return iter->second;

}

void BossStateMachine::SetCurState(BOSS_STATE _eState)
{
	m_pCurState = GetState(_eState);
	m_pCurState->Enter();
	assert(m_pCurState);
}

void BossStateMachine::ChangeState(BOSS_STATE _eNextState)
{
	if (!m_bCanChangeState)return;
	BossState* pNextState = GetState(_eNextState);

	//assert(m_pCurState != pNextState);
	m_pCurState->Exit();
	m_pCurState = pNextState;
	m_pCurState->Enter();
}
