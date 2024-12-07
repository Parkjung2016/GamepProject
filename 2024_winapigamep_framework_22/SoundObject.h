#pragma once
#include "Object.h"
#include "SoundEvent.h"

class SoundObject :
	public Object
{
public:
	SoundObject();
	~SoundObject() override;

public:
	void PlayEvent(const std::string& name);
	void Update() override;
	void Render(HDC _hdc) override;

	CLONE(SoundObject)
public:
	SoundEvent GetSoundEvent() const { return m_soundEvent; }
private:
	SoundEvent m_soundEvent;
};

