#pragma once
#include "BossState.h"
class BossAttackState :
	public BossState
{
public:
	BossAttackState();
	~BossAttackState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	bool m_bAnimationTrigger;

};

