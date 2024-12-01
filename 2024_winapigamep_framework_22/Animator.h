#pragma once
#include "Component.h"
class Texture;
class Animation;
class Object;
class Animator : public Component
{
public:
	Animator();
	virtual ~Animator();
public:
	virtual void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
public:
	// �ִϸ��̼� �����Լ�
	void CreateAnimation(const wstring& _strName, Texture* _pTex,
		Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,
		UINT _framecount, float _fDuration);
	void LoadAnimation(const wstring& _strRelativePath);
	// �ִϸ��̼� ã���Լ�
	Animation* FindAnimation(const wstring& _strName);

	// �ִϸ��̼� �÷��� �Լ�
	void PlayAnimation(const wstring& _strName, bool _IsRepeat, int _repeatcnt = 1);
	void StopAnimation();
public:
	Animation* GetCurrentAnim() const { return m_pCurrentAnimation; }
	const bool& GetRepeat() const { return m_IsRepeat; }
	const int& GetRepeatcnt() const { return m_repeatcnt; }
	void SetRepeatcnt() { --m_repeatcnt; }
	void SetIsRotate(bool _bIsRotate) { m_IsRotate = _bIsRotate; }
	void SetIsHit(bool _bIsHit) { m_IsHit = _bIsHit; }
	bool GetIsRotate() const { return m_IsRotate; }
	bool GetIsHit() const { return m_IsHit; }
private:
	map<wstring, Animation*> m_mapAnimations;
	Animation* m_pCurrentAnimation;
	bool	m_IsRepeat;
	int		m_repeatcnt;
	bool m_IsRotate;
	bool m_IsHit;

};

