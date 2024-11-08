#include "pch.h"
#include "Rigidbody.h"

#include "Object.h"
#include "TimeManager.h"

Rigidbody::Rigidbody() :
	m_fMass(1.f),
	m_fFricCoeff(200),
	m_fMaxSpeed(100.f)
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::LateUpdate()
{

	float fForce = m_vForce.Length();

	if (0.f != fForce)
	{
		m_vForce.Normalize();

		float fAccel = fForce / m_fMass;

		m_vAccel = m_vForce * fAccel;

		m_vVelocity += m_vAccel * fDT;

	}

	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();
		Vec2 vFriction = vFricDir * m_fFricCoeff * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{

			m_vVelocity = { 0.f,0.f };
		}
		else
		{
			m_vVelocity += vFriction;

		}
	}

	if (m_fMaxSpeed < m_vVelocity.Length())
	{
		m_vVelocity.Normalize();
		m_vVelocity *= m_fMaxSpeed;
	}

	Move();
	m_vForce = Vec2(0.f, 0.f);
}

void Rigidbody::Render(HDC _hdc)
{
}

void Rigidbody::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed)
	{

		Vec2 vDir = m_vVelocity;
		vDir.Normalize();


		Vec2 vPos = GetOwner()->GetPos();

		vPos += m_vVelocity * fDT;

		GetOwner()->SetPos(vPos);
	}
}
