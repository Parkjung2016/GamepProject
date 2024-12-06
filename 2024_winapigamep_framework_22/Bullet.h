#pragma once
#include "Object.h"

class Texture;
class Player;
class Bullet : public Object
{
public:
	Bullet();
	~Bullet() override;
private:
	Player* m_pPlayer;
	Texture* m_pTex;
	Vec2 m_vDir;
	float m_fSpeed;
	float m_fKnockBackPower;
	float m_fKnockBackDuration;
	float m_fCurrentDestroyTime;
	int m_iPower;

public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other) override;
	void SetDir(const Vec2& _vDir) { m_vDir = _vDir; }
	void SetOwner(Player* _pPlayer) { m_pPlayer = _pPlayer; }
	void SetSpeed(const float& _fSpeed) { m_fSpeed = _fSpeed; }
	void SetPower(const int& _iPower) { m_iPower = _iPower; }
	void SetKnockBackDuration(const float& _fKnockBackDuration) { m_fKnockBackDuration = _fKnockBackDuration; }
	void SetKnockBackPower(const float& _fKnockBackPower) { m_fKnockBackPower = _fKnockBackPower; }

	CLONE(Bullet)
};

