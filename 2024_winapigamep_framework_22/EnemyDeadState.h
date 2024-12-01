#pragma once
#include "EnemyState.h"
class EnemyDeadState :
    public EnemyState
{
public:
	EnemyDeadState();
	~EnemyDeadState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;

private:
	float m_fCurrentDestroyTime;
	float m_fDestroyTime;
};

