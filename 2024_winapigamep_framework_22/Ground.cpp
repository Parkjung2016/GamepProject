#include "pch.h"
#include "Ground.h"

#include "Collider.h"
#include "Gravity.h"
#include "ResourceManager.h"
#include "Texture.h"

Ground::Ground()
{
	AddComponent<Collider>();


}

Ground::~Ground()
{
}

void Ground::Start()
{

}

void Ground::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vPos2 = GetPos2();
	Vec2 vSize = GetSize();
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPos(vPos);

	if (m_pTex != nullptr)
		BitBlt(_hdc,
			(int)vRenderPos.x,
			(int)vRenderPos.y,
			vSize.x,
			vSize.y,
			m_pTex->GetTexDC(),
			vPos2.x,
			vPos2.y,
			SRCCOPY);
	ComponentRender(_hdc);
}

void Ground::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	Gravity* gravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != gravity)
	{
		gravity->SetGround(true);

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
	Gravity* gravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != gravity)
	{
		gravity->SetGround(true);

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
	Gravity* gravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != gravity)
	{
		gravity->SetGround(false);
	}
}

void Ground::Update()
{
}

void Ground::SetTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);

}


