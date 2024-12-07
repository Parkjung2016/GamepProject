#pragma once
#include "PlayerGroundState.h"

class PlayerWalkState :
    public PlayerGroundState
{

public:
	PlayerWalkState();
	~PlayerWalkState() override;
public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
private:
	bool m_bIsSoundTriggered;

};

