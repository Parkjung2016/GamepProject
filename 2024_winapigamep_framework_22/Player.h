#pragma once
#include "Interfaces.h"
#include "Object.h"

class Texture;
class PlayerStateMachine;

struct tPlayerInfo
{
	float fWalkSpeed;
	float fRunSpeed;
	float fJumpPower;
	float fAirControl;
	float fBulletSpeed;
	float fBulletKnockBackPower;
	float fBulletKnockBackDuration;
	int iBulletCountPerShot;
	int iBulletPower;
};
class Player : public Object
{
public:
	Player();
	~Player() override;
public:
	void Update() override;
	void Render(HDC _hdc) override;

	void EnterCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;

private:
	void SetInfo(const tPlayerInfo& _info) { m_tInfo = _info; }

	void UpdateInput();
	void UpdateMoveInput();
	void HandleApplyDamagedEvent();
	void HandleDeadEvent();
private:
	int m_iMoveInput;
	bool m_bIsPressRunInput;
	bool m_bIsPressMoveInput;
	Texture* m_pTex;
	PlayerStateMachine* m_pStateMachine;
	tPlayerInfo m_tInfo;

public:
	void SetStateMachine(PlayerStateMachine* _stateMachine);
	int GetMoveInput() const { return m_iMoveInput; }
	bool GetIsPressMoveInput() const { return m_bIsPressMoveInput; }
	bool GetIsPressRunInput() const { return m_bIsPressRunInput; }
	const tPlayerInfo& GetInfo() const { return m_tInfo; }
	CLONE(Player)
};

