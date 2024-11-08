#pragma once
#include "PlayerState.h"

class PlayerIdleState : public PlayerState
{
public:
	PlayerIdleState();
	~PlayerIdleState() override;
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

