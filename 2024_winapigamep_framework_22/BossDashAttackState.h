#pragma once
#include "BossState.h"
class BossDashAttackState :
    public BossState
{
public:
	BossDashAttackState();
	~BossDashAttackState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	bool m_bAnimationTrigger;
};

