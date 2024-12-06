#pragma once
#include "Object.h"

class BossStateMachine;
class Player;
class Effect;
struct tBossInfo
{
	float fSpeed;
	float fDashSpeed;
	float fHP;
	float fRecogRange;
	float fAttackRange;
	float fDashAttackRange;
	float fAttackKnockBackPower;
	float fAttackKnockBackDuration;
	int iStep2HPPercent;
	int iPower;

};
class Boss :
	public Object
{

public:
	Boss();
	~Boss() override;
public:
	float GetSpeed() const { return m_tInfo.fSpeed; }
	void SetStateMachine(BossStateMachine* _stateMachine);
	bool IsStep2() const { return m_bIsStep2; }
	bool IsPlayerInRange(float fRange) const;
	bool IsPlayerInFront();
	const tBossInfo& GetInfo() const { return m_tInfo; }
	Player* GetPlayer()const;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void AfterRender() override;
private:
	void SetInfo(const tBossInfo& _info) { m_tInfo = _info; }
	void CheckStep2();
	void EnterStep2();
	void HandleApplyDamaged();
	void HandleDead();
private:
	Texture* m_pTex;
	tBossInfo m_tInfo;
	BossStateMachine* m_pStateMachine;
	Effect* m_pStep2Effect;
	bool m_bIsStep2;
	CLONE(Boss)

};

