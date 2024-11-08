#pragma once
#include "Object.h"

class EnemyStateMachine;

struct tEnemyInfo
{
	float fSpeed;
	float fHP;
	float fRecogRange;
	float fAttackRange;
	float fAttack;
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
	const tEnemyInfo& GetInfo() const { return m_tInfo; }

private:
	void SetInfo(const tEnemyInfo& _info) { m_tInfo = _info; }

public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	tEnemyInfo m_tInfo;
	EnemyStateMachine* m_pStateMachine;

	CLONE(Enemy);

	friend class EnemyFactory;
};

