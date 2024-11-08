#pragma once
#include "PlayerState.h"
class PlayerGroundState : public PlayerState

{
public:
	PlayerGroundState(PLAYER_STATE _eState);
	~PlayerGroundState() override;

public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

