#pragma once
#include <string>
class SoundEvent
{
public:
	SoundEvent();
	bool IsValid();
	void Restart();
	void Stop(bool allowFadeOut = true);
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	void SetParameterWithLabel(const std::string& name, const std::string label);

	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	bool Is3D() const;
	void Set3DAttributes(const Vec2& _vPos) const;
	bool IsFollowOwner;

protected:
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);

private:
	class AudioSystem* mSystem;
	unsigned int mID;

};