#pragma once
#include "PlayerState.h"
class PlayerFallingState :
    public PlayerState
{
public:
	PlayerFallingState();
	~PlayerFallingState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

