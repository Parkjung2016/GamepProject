#pragma once
#include "Scene.h"


class SoundObject;

class TitleScene : public Scene
{
public:
	// Scene��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
public:
	static SoundObject* GetBGMSoundObject() { return m_pBGMSoundObject; }
private:
	static	SoundObject* m_pBGMSoundObject;
};

