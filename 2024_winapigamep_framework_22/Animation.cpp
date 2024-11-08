#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Func.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TimeManager.h"
Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
{
}
Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
	{
		m_CurFrame = m_vecAnimFrame.size() - 1;
		return;
	}
	m_fAccTime += fDT;
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame;
		if (m_CurFrame >= m_vecAnimFrame.size())
		{
			if (!m_pAnimator->GetRepeat())
				m_pAnimator->SetRepeatcnt();
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}

	}
}

void Animation::Render(HDC _hdc)
{
	Object* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	vPos = vPos + m_vecAnimFrame[m_CurFrame].vOffset;
	vPos = GET_SINGLE(Camera)->GetRenderPos(vPos);


	bool bIsRotate = m_pAnimator->GetIsRotate();
	int xDest = (int)(vPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x / 2.f);
	int yDest = (int)(vPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f);
	int wDest = (int)(m_vecAnimFrame[m_CurFrame].vSlice.x);
	int hDest = (int)(m_vecAnimFrame[m_CurFrame].vSlice.y);
	int xSrc = (int)(m_vecAnimFrame[m_CurFrame].vLT.x);
	int ySrc = (int)(m_vecAnimFrame[m_CurFrame].vLT.y);
	int wSrc = (int)(m_vecAnimFrame[m_CurFrame].vSlice.x);
	int hSrc = (int)(m_vecAnimFrame[m_CurFrame].vSlice.y);

	if (bIsRotate)
	{
		xDest += wSrc;
		wDest = -wDest;
	}
	DrawAlphaBlendedAndStretched(_hdc,
		xDest,
		yDest,
		wDest,
		hDest
		, m_pTex->GetTexDC(),
		xSrc,
		ySrc,
		wSrc,
		hSrc,
		255);

	//AlphaBlend(_hdc,
	//	xDest
	//	, yDest
	//	, wDest
	//	, hDest
	//	, m_pTex->GetTexDC()
	//	, xSrc
	//	, ySrc
	//	, wSrc
	//	, hSrc,
	//	blendFunction);

}


void Animation::DrawAlphaBlendedAndStretched(HDC hdcDest, int xDest, int yDest, int destWidth, int destHeight, HDC hdcSrc, int xSrc, int ySrc, int srcWidth, int srcHeight, BYTE transparency)
{
	HDC hdcTemp = CreateCompatibleDC(hdcDest);
	HBITMAP hbmTemp = CreateCompatibleBitmap(hdcDest, srcWidth, srcHeight);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcTemp, hbmTemp);

	BLENDFUNCTION blendFunction;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.SourceConstantAlpha = transparency;
	blendFunction.AlphaFormat = AC_SRC_ALPHA;

	TransparentBlt(hdcTemp,
		0,
		0,
		srcWidth,
		srcHeight,
		hdcSrc,
		xSrc,
		ySrc,
		srcWidth,
		srcHeight,
		RGB(255, 0, 255));

	SetStretchBltMode(hdcDest, HALFTONE);
	StretchBlt(hdcDest,
		xDest,
		yDest,
		destWidth,
		destHeight,
		hdcTemp,
		0,
		0,
		srcWidth,
		srcHeight,
		SRCCOPY);

	SelectObject(hdcTemp, hbmOld);
	DeleteObject(hbmTemp);
	DeleteDC(hdcTemp);
}

void Animation::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = GET_SINGLE(ResourceManager)->GetResPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);
	fprintf(pFile, "[Animation Name]\n");
	std::string strName = std::string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Name]\n");
	wstring pTexKey = m_pTex->GetKey();
	strName = std::string(pTexKey.begin(), pTexKey.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	wstring pPath = m_pTex->GetPath();
	strName = std::string(pPath.begin(), pPath.end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n", (int)(m_vecAnimFrame.size()));

	for (size_t i = 0; i < m_vecAnimFrame.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)(i));

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)(m_vecAnimFrame[i].vLT.x), (int)(m_vecAnimFrame[i].vLT.y));

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)(m_vecAnimFrame[i].vSlice.x), (int)(m_vecAnimFrame[i].vSlice.y));

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)(m_vecAnimFrame[i].vOffset.x), (int)(m_vecAnimFrame[i].vOffset.y));

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecAnimFrame[i].fDuration);

		fprintf(pFile, "\n\n");


	}

	fclose(pFile);
}

void Animation::Load(const wstring& _strRelativePath)
{
	wstring strFilePath = GET_SINGLE(ResourceManager)->GetResPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);


	std::string  str;
	char szBuff[256] = {};

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);
	str = szBuff;

	m_strName = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	FScanf(szBuff, pFile);
	FScanf(szBuff, pFile);

	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(strTexKey, strTexPath);

	FScanf(szBuff, pFile);
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);

	tAnimFrame frm = {};
	for (size_t i = 0; i < iFrameCount; ++i)
	{
		POINT pt = {};
		while (true)
		{
			FScanf(szBuff, pFile);

			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vSlice = pt;

			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);

				frm.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break;
			}
		}
		m_vecAnimFrame.push_back(frm);
	}

	fclose(pFile);
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, int _framecount, float _fDuration)
{
	m_pTex = _pTex;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i,
			_vSliceSize, _fDuration,{0.f,0.f} }));
	}
}
