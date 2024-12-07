#include "pch.h"
#include "SoundObject.h"

#include "Audio.h"
#include "SoundEvent.h"

SoundObject::SoundObject()
{
	AddComponent<Audio>();
}

SoundObject::~SoundObject()
{
}

void SoundObject::PlayEvent(const std::string& name)
{
	m_soundEvent = GetComponent<Audio>()->PlayEvent(name);
}

void SoundObject::Update()
{
}

void SoundObject::Render(HDC _hdc)
{
}

