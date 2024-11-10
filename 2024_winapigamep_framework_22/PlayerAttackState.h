#pragma once
#include "PlayerState.h"
class PlayerAttackState :
    public PlayerState
{
public:
	PlayerAttackState();
	~PlayerAttackState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
};

