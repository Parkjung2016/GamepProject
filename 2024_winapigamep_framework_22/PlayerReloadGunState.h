#pragma once
#include "PlayerState.h"
class PlayerReloadGunState :
	public PlayerState
{
public:
	PlayerReloadGunState();
	~PlayerReloadGunState() override;
public:
	void Update() override;
	void Enter() override;
	void Exit() override;
private:
	bool m_bAnimationTrigger;

};

