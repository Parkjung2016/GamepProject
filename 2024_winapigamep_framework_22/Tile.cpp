#include "pch.h"
#include "Tile.h"

#include "Collider.h"
#include "Gravity.h"
#include "ResourceManager.h"
#include "Texture.h"

Tile::Tile() :
	m_bIsTransparent(false),
	m_iTileId(0),
	m_pTex(nullptr)
{
}

Tile::~Tile()
{
}

void Tile::Start()
{
	Vec2 vPos = GetPos();

}

void Tile::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vPos2 = GetPos2();
	Vec2 vSize = GetSize();
	Vec2 vRenderPos = GET_SINGLE(Camera)->GetRenderPos(vPos);
	if (m_bIsTransparent)
	{

		TransparentBlt(_hdc,
			(int)(vRenderPos.x - vSize.x / 2.f),
			(int)(vRenderPos.y - vSize.y / 2.f),
			(int)vSize.x,
			(int)vSize.y,
			m_pTex->GetTexDC(),
			(int)vPos2.x,
			(int)vPos2.y,
			(int)vSize.x,
			(int)vSize.y,
			RGB(255, 0, 255));
	}
	else
	{
		BitBlt
		(
			_hdc,
			(int)(vRenderPos.x - vSize.x / 2.f),
			(int)(vRenderPos.y - vSize.y / 2.f),
			(int)vSize.x,
			(int)vSize.y,
			m_pTex->GetTexDC(),
			(int)vPos2.x,
			(int)vPos2.y,
			SRCCOPY
		);
	}
	ComponentRender(_hdc);
}

void Tile::EnterCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{
		pGravity->SetGround(true);

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

void Tile::StayCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{
		Vec2 vObjPos = _other->GetLatedUpdatedPos();
		Vec2 vObjSize = _other->GetSize();

		Vec2 vPos = GetComponent<Collider>()->GetLatedUpdatedPos();
		Vec2 vSize = GetComponent<Collider>()->GetSize();

		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjSize.y / 2.f + vSize.y / 2.f) - fLen;

		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= fValue;

		pGravity->SetGround(true);
		pOtherObj->SetPos(vObjPos);

	}
}

void Tile::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	Gravity* pGravity = pOtherObj->GetComponent<Gravity>();
	if (nullptr != pGravity)
	{
		pGravity->SetGround(false);
	}
}

void Tile::Update()
{
}

void Tile::SetTexture(const wstring& _wKey, const wstring& _wPath)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(_wKey, _wPath);

}


