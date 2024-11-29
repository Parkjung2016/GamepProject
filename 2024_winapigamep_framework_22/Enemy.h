#pragma once
#include "Object.h"

class EnemyStateMachine;
class Player;
struct tEnemyInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttackRange;
	int iPower;
};
class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();

public:
	float GetSpeed() const { return m_tInfo.fSpeed; }
	void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
	void SetStateMachine(EnemyStateMachine* _stateMachine);
	bool IsPlayerInRange(float fRange);
	bool IsPlayerInFront();
	const tEnemyInfo& GetInfo() const { return m_tInfo; }
	Player* GetPlayer()const;

private:
	void SetInfo(const tEnemyInfo& _info) { m_tInfo = _info; }
	void HandleApplyDamaged();
	void HandleDead();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Texture* m_pTex;
	tEnemyInfo m_tInfo;
	EnemyStateMachine* m_pStateMachine;

	CLONE(Enemy)

};

