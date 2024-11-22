#pragma once
#include "EnemyState.h"
class EnemyAttackState :
	public EnemyState
{
public:
	EnemyAttackState();
	~EnemyAttackState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;

private:
	bool _animationTrigger;
};

