#pragma once
#include "Component.h"


class Object;
class Rigidbody : public Component
{
public:
	Rigidbody();
	~Rigidbody() override;
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;

private:

	Vec2 m_vForce;
	Vec2 m_vAccel;
	Vec2 m_vVelocity;

	float m_fMass;
	float m_fFricCoeff;
	float m_fMaxSpeed;

public:
	void AddForce(const Vec2& _vF) { m_vForce += _vF; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() const { return m_fMass; }

	void  SetVelocity(const Vec2& _v) { m_vVelocity = _v; }
	void  AddVelocity(const Vec2& _v) { m_vVelocity += _v; }
	void  SetMaxVelocity(float _v) { m_fMaxSpeed = _v; }
private:
	void Move();


	friend class Object;
};

