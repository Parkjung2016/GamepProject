#pragma once
class Animator;
class Texture;
struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
	Vec2 vOffset;
};
class Animation
{
public:
	Animation();
	~Animation();
public:
	void Update();
	void Render(HDC _hdc);
public:
	void Save(const wstring& _strRelativePath);
	void Load(const wstring& _strRelativePath);
public:
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize,
		Vec2 _vStep, int _framecount, float _fDuration);
public:
	const wstring& GetName() const { return m_strName; }
	bool IsFinished() const { return m_bFinished; }
	void ResetFinished() { m_bFinished = false; }
	void SetName(wstring _name) { m_strName = _name; }
	void SetAnimator(Animator* _animator) { m_pAnimator = _animator; }
	void SetFrame(int _frame) { m_CurFrame = _frame; }
	void SetFrameOffset(int _index, Vec2 _offset) { m_vecAnimFrame[_index].vOffset = _offset; }
	void SetAlpha(float _alpha) { m_fAlpha = _alpha; }
	const UINT GetCurFrame() const { return m_CurFrame; }
	const size_t& GetMaxFrame() { return m_vecAnimFrame.size(); }

private:
	void DrawAlphaBlendedAndStretched(HDC hdcDest,
		int xDest,
		int yDest,
		int destWidth,
		int destHeight,
		HDC hdcSrc,
		int xSrc,
		int ySrc,
		int srcWidth,
		int srcHeight,
		BYTE transparency,
		bool isHit);
private:
	HDC m_hdcTemp;       // DC 핸들
	HBITMAP m_hbmTemp;   // 비트맵 핸들
	UINT   m_CurFrame; // 현재 프레임
	float m_fAlpha;
	float  m_fAccTime; // 누적 시간
	int	   m_repeatcnt; // 반복 횟수
	bool m_bFinished;
	wstring m_strName;
	Animator* m_pAnimator;
	Texture* m_pTex; // 애니메이션 텍스처
	vector<tAnimFrame> m_vecAnimFrame;
};

