#include "pch.h"
#include "Audio.h"

#include "AudioSystem.h"
#include "Object.h"
#include "SoundEvent.h"

Audio::Audio()
{
}

Audio::~Audio()
{
	StopAllEvents();
}

void Audio::Render(HDC _hdc)
{
}


void Audio::LateUpdate()
{
	auto iter = mEvents2D.begin();
	while (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	iter = mEvents3D.begin();
	while (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	for (auto& event : mEvents3D)
	{
		if (event.IsValid() && event.IsFollowOwner)
		{
			Vec2 vPos = GetOwner()->GetPos();
			event.Set3DAttributes(vPos);
		}
	}
}

SoundEvent Audio::PlayEvent(const std::string& name, const bool& _isFollowOwner)
{
	SoundEvent e = GET_SINGLE(AudioSystem)->PlayEvent(name);
	e.IsFollowOwner = _isFollowOwner;
	if (e.Is3D())
	{
		mEvents3D.emplace_back(e);
		Vec2 vPos = GetOwner()->GetPos();
		e.Set3DAttributes(vPos);
	}
	else
	{
		mEvents2D.emplace_back(e);
	}

	return e;
}
SoundEvent Audio::PlayEvent(const std::string& name, const Vec2& _vPos, const bool& _isFollowOwner)
{
	SoundEvent e = GET_SINGLE(AudioSystem)->PlayEvent(name);
	e.IsFollowOwner = _isFollowOwner;

	if (e.Is3D())
	{
		mEvents3D.emplace_back(e);
		e.Set3DAttributes(_vPos);
	}
	else
	{
		mEvents2D.emplace_back(e);
	}

	return e;
}
void Audio::StopAllEvents()
{
	for (auto& e : mEvents2D)
	{
		e.Stop(true);
	}
	for (auto& e : mEvents3D)
	{
		e.Stop(true);
	}

	mEvents2D.clear();
	mEvents3D.clear();
}
