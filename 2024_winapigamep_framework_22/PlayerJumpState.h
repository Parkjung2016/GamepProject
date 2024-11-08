#pragma once
#include "PlayerState.h"
class PlayerJumpState :
    public PlayerState
{
public:
	PlayerJumpState();
	~PlayerJumpState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

