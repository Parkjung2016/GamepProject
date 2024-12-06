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
	Vec2 m_vAccelA;
	Vec2 m_vVelocity;

	float m_fMass;
	float m_fFricCoeff;
public:
	void AddForce(const Vec2& _vF) { m_vForce += _vF; }
	Vec2 GetVelocity() const { return m_vVelocity; }
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() const { return m_fMass; }


	void  SetVelocity(const Vec2& _v) { m_vVelocity = _v; }
	void  AddVelocity(const Vec2& _v) { m_vVelocity += _v; }
	void  SetAccelAlpha(const Vec2& _vAccel) { m_vAccelA = _vAccel; }

private:
	void Move();


	friend class Object;
};

