#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "Texture.h"


void Camera::Init()
{
	m_pTargetObj = nullptr;
	m_fTime = .5f;
	m_fSpeed = 0.f;
	m_fAccTime = 0.f;
	m_bIsShaking = false;

	m_pVeilTex = GET_SINGLE(ResourceManager)->CreateTexture(L"CameraVeil", SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Camera::Update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->GetIsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
			m_vLookAt = m_pTargetObj->GetPos();
	}

	CalDiff();
}

void Camera::Render(HDC _hdc)
{
	if (m_listCamEffect.empty())
		return;

	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDT;

	float fRatio = 0.f;
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;


	int iAlpha = 0;

	if (CAM_EFFECT::FADE_OUT == effect.eEffect)
	{
		iAlpha = (int)(255.f * fRatio);
	}
	else 	if (CAM_EFFECT::FADE_IN == effect.eEffect)
	{
		iAlpha = (int)(255.f * (1.f - fRatio));
	}
	BLENDFUNCTION bf = {};

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_hdc, 0, 0
		, (int)m_pVeilTex->GetWidth()
		, (int)m_pVeilTex->GetHeight()
		, m_pVeilTex->GetTexDC()
		, 0, 0
		, (int)m_pVeilTex->GetWidth()
		, (int)m_pVeilTex->GetHeight(), bf);

	if (effect.fDuration < effect.fCurTime)
	{
		m_listCamEffect.pop_front();
	}
}

void Camera::Shake(float _fShakeIntensity, float _fShakeTime)
{
	m_bIsShaking = true;
	m_fShakeTimeLeft = _fShakeTime;
	m_fShakeIntensity = _fShakeIntensity;
}

void Camera::CalDiff()
{
	if (m_bIsShaking)
	{
		if (m_fShakeTimeLeft > 0.f)
		{
			m_fShakeTimeLeft -= fDT;

			float shakeOffsetX = (rand() % 200 - 100) * m_fShakeIntensity;
			float shakeOffsetY = (rand() % 200 - 100) * m_fShakeIntensity;
			m_vCurLookAt.x = m_vPrevShakeLookAt.x + shakeOffsetX;
			m_vCurLookAt.y = m_vPrevShakeLookAt.y + shakeOffsetY;

			//m_fShakeIntensity *= 0.9f;

		}
		else
		{
			m_bIsShaking = false;
			m_vCurLookAt = m_vPrevShakeLookAt;
		}
	}
	else
	{

		m_fAccTime += fDT;
		if (m_fTime <= m_fAccTime)
		{
			m_vCurLookAt = m_vLookAt;
		}
		else
		{
			Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;

			if (vLookDir.IsZero())
			{
				m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
			}
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
		}

	}


	Vec2 vResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
	Vec2 vCenter = vResolution / 2;
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
