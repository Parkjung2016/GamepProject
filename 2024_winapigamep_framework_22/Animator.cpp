#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "MyFunc.h"

Animator::Animator()
	: m_pCurrentAnimation(nullptr)
	, m_IsRepeat(false)
{
}

Animator::~Animator()
{
	SafeDeleteMap(m_mapAnimations);
}

void Animator::LateUpdate()
{
	if (nullptr != m_pCurrentAnimation)
		m_pCurrentAnimation->Update();
}

void Animator::Render(HDC _hdc)
{
	if (nullptr != m_pCurrentAnimation)
		m_pCurrentAnimation->Render(_hdc);
}

void Animator::CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _framecount, float _fDuration)
{
	Animation* pAnim = FindAnimation(_strName);
	if (pAnim != nullptr)
		return;

	pAnim = new Animation;
	pAnim->SetName(_strName);
	pAnim->SetAnimator(this);
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _framecount, _fDuration);
	m_mapAnimations.insert({ _strName,pAnim });
}

void Animator::LoadAnimation(const wstring& _strRelativePath)
{
	Animation* pAnim = new Animation;
	pAnim->Load(_strRelativePath);

	pAnim->SetAnimator(this);
	m_mapAnimations.insert({ pAnim->GetName(), pAnim });
}

Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnimations.find(_strName);
	if (iter == m_mapAnimations.end())
		return nullptr;
	return iter->second;
}

void Animator::PlayAnimation(const wstring& _strName, bool _IsRepeat, int _repeatcnt)
{
	m_pCurrentAnimation = FindAnimation(_strName);
	m_pCurrentAnimation->ResetFinished();
	m_pCurrentAnimation->SetFrame(0);
	m_IsRepeat = _IsRepeat;
	m_repeatcnt = _repeatcnt;
}

void Animator::StopAnimation()
{
	m_pCurrentAnimation = nullptr;
}


