#pragma once
#include "PlayerState.h"
class PlayerDashState :
	public PlayerState
{
public:
	PlayerDashState();
	~PlayerDashState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;

private:
	float m_fCurrentDashTime;
};

