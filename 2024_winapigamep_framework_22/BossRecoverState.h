#pragma once
#include "BossState.h"
class BossRecoverState :
	public BossState
{
public:
	BossRecoverState();
	~BossRecoverState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
	void SetWaitTime(float _fWaitTime) { m_fWaitTime = _fWaitTime; }

private:
	float m_fCurrentWaitTime;
	float m_fWaitTime;
};

