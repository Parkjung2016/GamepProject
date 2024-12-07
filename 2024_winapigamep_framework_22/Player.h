#pragma once
#include "Object.h"

class Texture;
class PlayerStateMachine;
class TextUI;
struct tPlayerInfo
{
	float fWalkSpeed;
	float fDashSpeed;
	float fDashDuration;
	float fRunSpeed;
	float fJumpPower;
	float fAirControl;
	float fBulletSpeed;
	float fBulletKnockBackPower;
	float fBulletKnockBackDuration;
	int iMaxBulletCount;
	int iBulletCountPerShot;
	int iBulletPower;
};
class Player : public Object
{
public:
	Player();
	~Player() override;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void AfterRender() override;
	void EnterCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;

private:
	void SetInfo(const tPlayerInfo& _info) { m_tInfo = _info; }

	void UpdateInput();
	void UpdateMoveInput();
	void HandleApplyDamagedEvent();
	void HandleDeadEvent() const;
private:
	TextUI* m_pHealthTextUI;
	TextUI* m_pBulletCountTextUI;
	TextUI* m_pCurrentDashCountTextUI;
	int m_iCurrentBulletCount;
	int m_iMoveInput;
	int m_iDashableCount;
	bool m_bIsBlocking;
	bool m_bIsPressRunInput;
	bool m_bIsPressMoveInput;
	Texture* m_pTex;
	PlayerStateMachine* m_pStateMachine;
	tPlayerInfo m_tInfo;

public:
	void SetBlocking(bool _b) { m_bIsBlocking = _b; }
	void UpdateBulletCountText();
	void AddDashableCount();
	void SubDashableCount();
	void SetStateMachine(PlayerStateMachine* _stateMachine);
	void ReloadGun();
	void FireGun();
	int GetDashableCount() const { return m_iDashableCount; }
	int GetCurrentBulletCount() const { return m_iCurrentBulletCount; }
	int GetMoveInput() const { return m_iMoveInput; }
	bool IsBlocking()const { return m_bIsBlocking; }
	bool CanFireGun() const { return m_iCurrentBulletCount > 0; }
	bool CanReloadGun() const { return m_iCurrentBulletCount < GetInfo().iMaxBulletCount; }
	bool GetIsPressMoveInput() const { return m_bIsPressMoveInput; }
	bool GetIsPressRunInput() const { return m_bIsPressRunInput; }
	const tPlayerInfo& GetInfo() const { return m_tInfo; }
	CLONE(Player)
};

