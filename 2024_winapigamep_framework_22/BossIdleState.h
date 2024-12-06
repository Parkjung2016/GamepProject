#pragma once
#include "BossState.h"
class BossIdleState :
    public BossState
{
public:
	BossIdleState();
	~BossIdleState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

