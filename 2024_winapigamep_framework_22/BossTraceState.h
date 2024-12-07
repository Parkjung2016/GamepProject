#pragma once
#include "BossState.h"
class BossTraceState :
	public BossState
{
public:
	BossTraceState();
	~BossTraceState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	bool m_bIsSoundTriggered;
};

