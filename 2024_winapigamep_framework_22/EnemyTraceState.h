#pragma once
#include "EnemyState.h"
class EnemyTraceState :
    public EnemyState
{

private:

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	EnemyTraceState();
	~EnemyTraceState() override;
};

