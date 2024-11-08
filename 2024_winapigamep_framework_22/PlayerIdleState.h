#pragma once
#include "PlayerGroundState.h"

class PlayerIdleState : public PlayerGroundState
{
public:
	PlayerIdleState();
	~PlayerIdleState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;

};

