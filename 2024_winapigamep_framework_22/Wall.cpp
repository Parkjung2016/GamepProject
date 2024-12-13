#include "pch.h"
#include "Wall.h"

#include "Gravity.h"
#include "ResourceManager.h"
#include "Texture.h"

Wall::Wall()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Wall", L"Texture\\Map\\Wall.bmp");
}

Wall::~Wall()
{
}

void Wall::Render(HDC _hdc)
{

	Vec2 vPos = GetPos();
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPos(vPos);
	Vec2 vSize = GetSize();

	BLENDFUNCTION bf;
	bf.AlphaFormat = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 50;
	AlphaBlend(_hdc,
		(int)(vRenderPos.x - vSize.x / 2.f),
		(int)(vRenderPos.y - vSize.y / 2.f),
		(int)vSize.x,
		(int)vSize.y,
		m_pTex->GetTexDC(),
		0,
		0,
		(int)vSize.x,
		(int)vSize.y,
		bf);
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
