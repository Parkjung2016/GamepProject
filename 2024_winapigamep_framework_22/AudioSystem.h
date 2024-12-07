#pragma once

namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};
class SoundEvent;
class AudioSystem
{
public:
	~AudioSystem();

	void Init();
	void Release();

	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	SoundEvent PlayEvent(const std::string& name);

	void Update();

	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);

protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);

private:
	static unsigned int sNextID;


	FMOD::Studio::System* mSystem;
	FMOD::System* mLowLevelSystem;


	std::unordered_map<std::string, FMOD::Studio::Bank*> mBanks;

	std::unordered_map<std::string, FMOD::Studio::EventDescription*> mEvents;

	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*> mEventInstances;

	std::unordered_map<std::string, FMOD::Studio::Bus*> mBuses;
	DECLARE_SINGLE(AudioSystem)

};

