#pragma once
#include "PlayerAirState.h"
class PlayerFallingState :
    public PlayerAirState
{
public:
	PlayerFallingState();
	~PlayerFallingState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

