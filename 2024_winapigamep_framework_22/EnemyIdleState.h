#pragma once
#include "EnemyState.h"

class EnemyIdleState :
	public EnemyState
{
public:
	EnemyIdleState();
	~EnemyIdleState() override;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

