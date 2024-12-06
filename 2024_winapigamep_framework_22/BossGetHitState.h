#pragma once
#include "BossState.h"
class BossGetHitState :
	public BossState
{
public:
	BossGetHitState();
	~BossGetHitState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	float m_fCurrentKnockBackDuration;
};

