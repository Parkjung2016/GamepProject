#pragma once
#include "Enums.h"

class Enemy;
class EnemyState;
class EnemyStateMachine
{
private:
	map<ENEMY_STATE, EnemyState*> m_mapState;
	EnemyState* m_pCurState;
	Enemy* m_pOwner;
	bool m_bCanChangeState;
public:
	void Update();

public:
	void AddState(EnemyState* _pState);
	EnemyState* GetState(ENEMY_STATE _eState);
	void SetCurState(ENEMY_STATE _eState);
	void ChangeState(ENEMY_STATE _eNextState);
	void SetCanChangeState(bool _b) { m_bCanChangeState = _b; }
	Enemy* GetOwner() const { return m_pOwner; }
public:
	EnemyStateMachine();
	~EnemyStateMachine();

	friend class Enemy;
};

