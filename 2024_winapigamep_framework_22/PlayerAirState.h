#pragma once
#include "PlayerState.h"
class PlayerAirState :
    public PlayerState
{
public:
	PlayerAirState(PLAYER_STATE _eState);
	~PlayerAirState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

