#pragma once
#include "EnemyState.h"
class EnemyGetHitState :
	public EnemyState
{
public:
	EnemyGetHitState();
	~EnemyGetHitState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;

private:
	float m_fCurrentKnockBackDuration;
};

