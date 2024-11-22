#pragma once
#include "PlayerState.h"
class PlayerGetHitState :
	public PlayerState
{
public:
	PlayerGetHitState();
	~PlayerGetHitState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

