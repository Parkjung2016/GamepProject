#include "pch.h"
#include "Ground.h"

#include "Collider.h"
#include "Gravity.h"
#include "Rigidbody.h"

Ground::Ground()
{
	AddComponent<Collider>();
}

Ground::~Ground()
{
}

void Ground::Start()
{
	GetComponent<Collider>()->SetSize(GetSize());

}

void Ground::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	ComponentRender(_hdc);
}

void Ground::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetComponent<Gravity>()->SetGround(true);

		Vec2 vObjPos = _other->GetLatedUpdatedPos();
		Vec2 vObjSize = _other->GetSize();

		Vec2 vPos = GetComponent<Collider>()->GetLatedUpdatedPos();
		Vec2 vSize = GetComponent<Collider>()->GetSize();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjSize.y / 2.f + vSize.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fValue;


		pOtherObj->SetPos(vObjPos);

	}
}

void Ground::StayCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetComponent<Gravity>()->SetGround(true);

		Vec2 vObjPos = _other->GetLatedUpdatedPos();
		Vec2 vObjSize = _other->GetSize();

		Vec2 vPos = GetComponent<Collider>()->GetLatedUpdatedPos();
		Vec2 vSize = GetComponent<Collider>()->GetSize();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjSize.y / 2.f + vSize.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fValue;

		pOtherObj->SetPos(vObjPos);



	}
}

void Ground::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();

	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetComponent<Gravity>()->SetGround(false);
	}
}

void Ground::Update()
{
}


