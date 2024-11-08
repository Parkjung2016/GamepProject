#pragma once
#include "PlayerState.h"
class PlayerWalkState :
    public PlayerState
{

public:
	PlayerWalkState();
	~PlayerWalkState() override;
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

};

