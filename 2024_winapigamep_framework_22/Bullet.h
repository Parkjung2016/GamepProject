#pragma once
#include "Object.h"

class Texture;
class Bullet : public Object
{
public:
	Bullet();
	~Bullet() override;
private:
	Texture* m_pTex;
	Vec2 m_vDir;
	float m_fSpeed;
	int m_iPower;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other) override;
	void SetDir(const Vec2& _vDir) { m_vDir = _vDir; }
	void SetSpeed(const float& _fSpeed) { m_fSpeed = _fSpeed; }
	void SetPower(const int& _iPower) { m_iPower = _iPower; }

	CLONE(Bullet)
};

