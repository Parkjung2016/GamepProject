#pragma once
#include "Enums.h"

class BossStateMachine;
class Boss;
class BossState
{
private:
	BossStateMachine* m_pStateMachine;
	BOSS_STATE m_eState;

public:
	BossStateMachine* GetStateMachine() const { return m_pStateMachine; }
	BOSS_STATE GetType() const { return m_eState; }
	Boss* GetBoss() const;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
public:
	BossState(BOSS_STATE _eState);
	virtual ~BossState();

	friend class BossStateMachine;
};

