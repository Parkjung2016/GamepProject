#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDISelector.h"
UINT Collider::g_iNextID = 0;
Collider::Collider()
	: m_ID(g_iNextID++)
	, m_iCol(0)
	, m_vSize(30.f, 30.f),
	m_vOffsetPos(0.f, 0.f),
	m_vLatePos(0.f, 0.f)
{
}

Collider::~Collider()
{
	SetOwner(nullptr);
	m_iCol = -1;
}

void Collider::LateUpdate()
{
	const Object* pOwner = GetOwner();
	Vec2 vPos = pOwner->GetPos();
	m_vLatePos = vPos + m_vOffsetPos;
	assert(0 <= m_iCol);
}

void Collider::Render(HDC _hdc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_iCol)
		ePen = PEN_TYPE::RED;
	GDISelector pen(_hdc, ePen);
	GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPos(m_vLatePos);
	RECT_RENDER(_hdc, vRenderPos.x, vRenderPos.y,
		m_vSize.x, m_vSize.y);
}

void Collider::EnterCollision(Collider* _other)
{
	if (m_iCol < 0)return;
	++m_iCol;
	GetOwner()->EnterCollision(_other);
}

void Collider::StayCollision(Collider* _other)
{
	GetOwner()->StayCollision(_other);
}

void Collider::ExitCollision(Collider* _other)
{
	--m_iCol;
	//cout << "Exit" << endl;
	GetOwner()->ExitCollision(_other);
}
