#pragma once
#include "EnemyStateMachine.h"
#include "Object.h"

class EnemyStateMachine;
class Player;
struct tEnemyInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttackRange;
	float fAttackKnockBackPower;
	float fAttackKnockBackDuration;
	int iPower;

};
class Enemy :
	public Object
{
public:
	Enemy();
	~Enemy() override;

public:
	float GetSpeed() const { return m_tInfo.fSpeed; }
	void FreezeMove(float _fFreezeTime)
	{
		m_pStateMachine->ChangeState(ENEMY_STATE::IDLE);
		m_fFreezeTime = _fFreezeTime;
	}
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void SetStateMachine(EnemyStateMachine* _stateMachine);
	bool IsPlayerInRange(float fRange) const;
	bool IsPlayerInFront();
	const tEnemyInfo& GetInfo() const { return m_tInfo; }
	Player* GetPlayer()const;

private:
	void SetInfo(const tEnemyInfo& _info) { m_tInfo = _info; }
	void HandleApplyDamaged() const;
	void HandleDead() const;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void AfterRender() override;
public:
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
	float m_fFreezeTime;
	Texture* m_pTex;
	tEnemyInfo m_tInfo;
	EnemyStateMachine* m_pStateMachine;

	CLONE(Enemy)

};

