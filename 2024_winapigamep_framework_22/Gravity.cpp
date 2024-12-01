#include "pch.h"
#include "Gravity.h"

#include "Object.h"
#include "Rigidbody.h"

Gravity::Gravity()
	:m_bCanGravity(true)
{

}

Gravity::~Gravity()
{
}

void Gravity::LateUpdate()
{
	if (!m_bCanGravity || m_bGround)return;
	GetOwner()->GetComponent<Rigidbody>()->AddForce({ 0.f,800.f });
}

void Gravity::Render(HDC _hdc)
{

}

void Gravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		Rigidbody* pRigid = GetOwner()->GetComponent<Rigidbody>();
		Vec2 vV = pRigid->GetVelocity();
		pRigid->SetVelocity({ vV.x,0.f });
	}
}

