#pragma once
#include "Component.h"
#include "SoundEvent.h"
class Audio :
	public Component
{
public:
	Audio();
	~Audio() override;
public:

	void Render(HDC _hdc) override;

	void LateUpdate() override;

	SoundEvent PlayEvent(const std::string& name, const bool& _isFollowOwner = false);
	SoundEvent PlayEvent(const std::string& name, const Vec2& _vPos, const bool& _isFollowOwner = false);
	void StopAllEvents();

private:
	std::vector<SoundEvent> mEvents2D;
	std::vector<SoundEvent> mEvents3D;
};

