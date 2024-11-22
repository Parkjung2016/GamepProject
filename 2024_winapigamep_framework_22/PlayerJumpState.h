#pragma once
#include "PlayerAirState.h"
class PlayerJumpState :
    public PlayerAirState
{
public:
	PlayerJumpState();
	~PlayerJumpState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;

};

