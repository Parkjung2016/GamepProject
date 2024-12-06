#pragma once
#include "PlayerState.h"

class PlayerBlockState : public PlayerState
{
public:
	PlayerBlockState();
	~PlayerBlockState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

