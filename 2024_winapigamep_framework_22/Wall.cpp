#include "pch.h"
#include "Wall.h"

#include "Gravity.h"

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Wall::Update()
{
}

void Wall::EnterCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{

		Vec2 vObjPos = _other->GetLatedUpdatedPos();
		Vec2 vObjSize = _other->GetSize();

		Vec2 vPos = GetComponent<Collider>()->GetLatedUpdatedPos();
		Vec2 vSize = GetComponent<Collider>()->GetSize();

		float fLenX = abs(vObjPos.x - vPos.x);
		float fValueX = (vObjSize.x / 2.f + vSize.x / 2.f) - fLenX;

		if (vObjPos.x > vPos.x)
		{
			vObjPos.x += fValueX; 
		}
		else
		{
			vObjPos.x -= fValueX; 
		}
		vObjPos.y = _other->GetOwner()->GetPos().y;
		pOtherObj->SetPos(vObjPos);
	}
}

void Wall::StayCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{
		Vec2 vObjPos = _other->GetLatedUpdatedPos();
		Vec2 vObjSize = _other->GetSize();

		Vec2 vPos = GetComponent<Collider>()->GetLatedUpdatedPos();
		Vec2 vSize = GetComponent<Collider>()->GetSize();

		float fLenX = abs(vObjPos.x - vPos.x);
		float fValueX = (vObjSize.x / 2.f + vSize.x / 2.f) - fLenX;

		if (vObjPos.x > vPos.x)
		{
			vObjPos.x += fValueX; 
		}
		else
		{
			vObjPos.x -= fValueX; 
		}
		vObjPos.y = _other->GetOwner()->GetPos().y;
		pOtherObj->SetPos(vObjPos);

	}
}

void Wall::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{
	}
}
