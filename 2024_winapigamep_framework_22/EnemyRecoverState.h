#pragma once
#include "EnemyState.h"
class EnemyRecoverState :
	public EnemyState
{
public:
	EnemyRecoverState();
	~EnemyRecoverState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
	 void SetWaitTime(float _fWaitTime) { m_fWaitTime = _fWaitTime; }
private:
	float m_fWaitTime;
	float m_fCurrentWaitTime;
};

