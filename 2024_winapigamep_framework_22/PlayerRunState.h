#pragma once
#include "PlayerGroundState.h"
class PlayerRunState :
    public PlayerGroundState
{
public:
	PlayerRunState();
	~PlayerRunState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

