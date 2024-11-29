#pragma once
#include "EnemyState.h"
class EnemyTraceState :
    public EnemyState
{

public:
	EnemyTraceState();
	~EnemyTraceState() override;
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

