#pragma once
#include "BossState.h"
class BossDeadState :
	public BossState
{
public:
	BossDeadState();
	~BossDeadState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	float m_fCurrentChangeSceneTime;
	float m_fCurrentDestroyTime;
	bool m_bTriggered;
};

