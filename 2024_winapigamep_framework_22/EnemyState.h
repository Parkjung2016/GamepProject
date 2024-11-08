#pragma once

class EnemyStateMachine;
class Enemy;
class EnemyState
{
private:
	EnemyStateMachine* m_pStateMachine;
	ENEMY_STATE m_eState;

public:
	EnemyStateMachine* GetStateMachine() const { return m_pStateMachine; }
	ENEMY_STATE GetType() const { return m_eState; }
	Enemy* GetEnemy() const;

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
public:
	EnemyState(ENEMY_STATE _eState);
	virtual ~EnemyState();

	friend class EnemyStateMachine;
};

