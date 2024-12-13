#include "pch.h"
#include "Effect.h"

#include "Animation.h"
#include "Animator.h"
#include "EventManager.h"
#include "MyFunc.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TimeManager.h"

Effect::Effect()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Effect", L"Texture\\Bullet.bmp");
}

Effect::~Effect()
{

}

void Effect::Start()
{

}

void Effect::Update()
{
	if (nullptr == m_parentObject)
	{
		if (m_fCurrentDurationTime <= m_fDurationTime)
		{
			m_fCurrentDurationTime += fDT;
		}
		else
		{
			DestroyObject();
		}
	}
	else
	{
		Vec2 vPos = m_parentObject->GetPos();
		SetPos(vPos + m_vOffset);
	}
}

void Effect::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Effect::SetEffectAnimation(Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration)
{
	AddComponent<Animator>()->CreateAnimation(L"Effect", m_pTex, _vLT, _vSliceSize, _vStep, _frameCount, _fDuration);
	GetComponent<Animator>()->PlayAnimation(L"Effect", nullptr != m_parentObject);

}

void Effect::SetAlpha(float _fAlpha)
{
	GetComponent<Animator>()->GetCurrentAnim()->SetAlpha(_fAlpha);
}

void Effect::DestroyObject()
{
	tEvent evt;

	evt.eveType = EVENT_TYPE::DELETE_OBJECT;
	evt.lParam = (DWORD_PTR)this;
	GET_SINGLE(EventManager)->AddEvent(evt);
}
