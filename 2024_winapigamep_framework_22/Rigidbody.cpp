#include "pch.h"
#include "Rigidbody.h"

#include "Gravity.h"
#include "Object.h"
#include "TimeManager.h"

Rigidbody::Rigidbody() :
	m_fMass(1.f),
	m_fFricCoeff(200),
	m_vMaxVelocity({ 200.f,600.f })
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


	}
	m_vVelocity += m_vAccelA;

	m_vVelocity += m_vAccel * fDT;

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

	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}
	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}
	Move();
	m_vForce = Vec2(0.f, 0.f);

	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f, 0.f);

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

