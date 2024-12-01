#pragma once
#include "PlayerState.h"
class PlayerDeadState :
	public PlayerState
{
public:
	PlayerDeadState();
	~PlayerDeadState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

