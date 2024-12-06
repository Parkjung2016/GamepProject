#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "MyFunc.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "TimeManager.h"
Animation::Animation()
	: m_hdcTemp(nullptr), m_hbmTemp(nullptr), m_CurFrame(0)
	, m_fAlpha(0)
	, m_fAccTime(0.f), m_repeatcnt(0)
	, m_bFinished(false),
	m_pAnimator(nullptr), m_pTex(nullptr)
{
}

Animation::~Animation()
{
	if (m_hbmTemp) {
		DeleteObject(m_hbmTemp);
		m_hbmTemp = nullptr;
	}

	if (m_hdcTemp) {
		DeleteDC(m_hdcTemp);
		m_hdcTemp = nullptr;
	}
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
	{
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
			m_bFinished = true;
		}
		else
		{
			m_bFinished = false;
		}

	}
}

void Animation::Render(HDC _hdc)
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
	{
		m_CurFrame = m_vecAnimFrame.size() - 1;
	}
	Object* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();
	vPos = vPos + m_vecAnimFrame[m_CurFrame].vOffset;
	vPos = GET_SINGLE(Camera)->GetRenderPos(vPos);


	int xDest = (int)(vPos.x - m_vecAnimFrame[m_CurFrame].vSlice.x / 2.f);
	int yDest = (int)(vPos.y - m_vecAnimFrame[m_CurFrame].vSlice.y / 2.f);
	int wDest = (int)(m_vecAnimFrame[m_CurFrame].vSlice.x);
	int hDest = (int)(m_vecAnimFrame[m_CurFrame].vSlice.y);
	int xSrc = (int)(m_vecAnimFrame[m_CurFrame].vLT.x);
	int ySrc = (int)(m_vecAnimFrame[m_CurFrame].vLT.y);
	int wSrc = (int)(m_vecAnimFrame[m_CurFrame].vSlice.x);
	int hSrc = (int)(m_vecAnimFrame[m_CurFrame].vSlice.y);
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
		255,
		m_pAnimator->GetIsHit());

	//TransparentBlt(_hdc,
	//	xDest
	//	, yDest
	//	, wDest
	//	, hDest
	//	, m_pTex->GetTexDC()
	//	, xSrc
	//	, ySrc
	//	, wSrc
	//	, hSrc,
	//	RGB(255, 0, 255));

}


void Animation::DrawAlphaBlendedAndStretched(HDC hdcDest, int xDest, int yDest, int destWidth, int destHeight, HDC hdcSrc, int xSrc, int ySrc, int srcWidth, int srcHeight, BYTE transparency, bool isHit)
{
	if (!hdcDest) {
		cout << "Invalid hdcDest detected!\n";
		return;
	}
	m_hdcTemp = CreateCompatibleDC(hdcDest);
	if (!m_hdcTemp) {
		DWORD gdiUsage = GetGuiResources(GetCurrentProcess(), GR_GDIOBJECTS);
		cout << "Current GDI Objects in use: " << gdiUsage << endl;

		return;
	}
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = destWidth;
	bmi.bmiHeader.biHeight = -destHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* pBits = nullptr;


	m_hbmTemp = CreateDIBSection(hdcDest, &bmi, DIB_RGB_COLORS, &pBits, nullptr, 0);
	HBITMAP hbmOld = (HBITMAP)SelectObject(m_hdcTemp, m_hbmTemp);
	bool bIsRotate = m_pAnimator->GetIsRotate();

	int stretchWidth = bIsRotate ? -destWidth : destWidth;
	int xPosition = bIsRotate ? destWidth - 1 : 0;

	SetStretchBltMode(m_hdcTemp, HALFTONE);
	StretchBlt(m_hdcTemp,
		xPosition,
		0,
		stretchWidth,
		destHeight,
		hdcSrc,
		xSrc,
		ySrc,
		srcWidth,
		srcHeight,
		SRCCOPY);


	if (isHit)
	{
		DWORD* pixels = (DWORD*)pBits;
		for (int y = 0; y < destHeight; ++y)
		{
			for (int x = 0; x < destWidth; ++x)
			{
				int index = y * destWidth + x;
				DWORD color = pixels[index];

				if (color == RGB(255, 0, 255)) continue;;

				BYTE r = (color & 0x000000FF);
				BYTE g = (color & 0x0000FF00) >> 8;
				BYTE b = (color & 0x00FF0000) >> 16;

				r = max(0, r - 50);
				g = max(0, g - 50);
				b = min(255, b + 100);

				pixels[index] = (r | (g << 8) | (b << 16));

			}
		}
	}

	TransparentBlt(hdcDest,
		xDest,
		yDest,
		destWidth,
		destHeight,
		m_hdcTemp,
		0,
		0,
		destWidth,
		destHeight,
		RGB(255, 0, 255));

	SelectObject(m_hdcTemp, hbmOld);
	DeleteObject(m_hbmTemp);
	DeleteDC(m_hdcTemp);
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
