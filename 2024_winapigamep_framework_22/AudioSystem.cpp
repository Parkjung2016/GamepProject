#include "pch.h"
#include "AudioSystem.h"

#include "Camera.h"
#include "SoundEvent.h"
unsigned int AudioSystem::sNextID = 0;

AudioSystem::~AudioSystem()
{

}

void AudioSystem::Init()
{

	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK)
	{
		return;
	}

	result = mSystem->initialize(
		512,                        
		FMOD_STUDIO_INIT_NORMAL,    
		FMOD_INIT_NORMAL,           
		nullptr                     
	);
	if (result != FMOD_OK)
	{
		return;
	}

	result = mSystem->getCoreSystem(&mLowLevelSystem);
	if (result != FMOD_OK)
	{
		return;
	}

	LoadBank("Resource/FMODBank/Desktop/Master.strings.bank");
	LoadBank("Resource/FMODBank/Desktop/Master.bank");
	LoadBank("Resource/FMODBank/Desktop/BGM.bank");
	LoadBank("Resource/FMODBank/Desktop/UI.bank");
	LoadBank("Resource/FMODBank/Desktop/SFX.bank");

}

void AudioSystem::Release()
{
	mSystem->release();
}

void AudioSystem::LoadBank(const std::string& name)
{
	if (mBanks.find(name) != mBanks.end())
	{
		return;
	}

	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		name.c_str(),
		FMOD_STUDIO_LOAD_BANK_NORMAL,
		&bank
	);
	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		mBanks.emplace(name, bank);
		bank->loadSampleData();
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			std::vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (auto e : events)
			{
				e->getPath(eventName, maxPathLength, nullptr);
				mEvents.emplace(eventName, e);
			}
		}
	}

	int numBuses = 0;
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		std::vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (auto bus : buses)
		{
			bus->getPath(busName, 512, nullptr);
			mBuses.emplace(busName, bus);
		}
	}
}

void AudioSystem::UnloadBank(const std::string& name)
{
	auto iter = mBanks.find(name);
	if (iter != mBanks.end())
	{
		return;
	}

	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		std::vector<FMOD::Studio::EventDescription*> events(numEvents);
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512];
		for (auto e : events)
		{
			e->getPath(eventName, 512, nullptr);
			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}

	int numBuses = 0;
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		std::vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (auto bus : buses)
		{
			bus->getPath(busName, 512, nullptr);
			auto busi = mBuses.find(busName);
			if (busi != mBuses.end())
			{
				mBuses.erase(busi);
			}
		}
	}

	bank->unloadSampleData();
	bank->unload();
	mBanks.erase(iter);
}
void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : mBanks)
	{
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	mBanks.clear();
	mEvents.clear();
}
SoundEvent AudioSystem::PlayEvent(const std::string& name)
{
	unsigned int retID = 0;
	auto iter = mEvents.find(name);
	if (iter != mEvents.end())
	{
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			event->start();
			sNextID++;
			retID = sNextID;
			mEventInstances.emplace(retID, event);

		}
	}
	return SoundEvent(this, retID);
}
void AudioSystem::Update()
{

	std::vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		FMOD::Studio::EventInstance* e = iter.second;
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			e->release();
			done.emplace_back(iter.first);
		}
	}

	for (auto id : done)
	{
		mEventInstances.erase(id);
	}
	Vec2 vCameraPos = GET_SINGLE(Camera)->GetLookAt();
	FMOD_3D_ATTRIBUTES attr;
	attr.forward = { 1.f,0.f,0.f };
	attr.up = { 0.f,-1.f,0.f };
	attr.position = { vCameraPos.x,vCameraPos.y,0 };

	mSystem->setListenerAttributes(0, &attr);
	mSystem->update();
}


float AudioSystem::GetBusVolume(const std::string& name) const
{
	float retVal = 0.f;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getVolume(&retVal);
	}
	return retVal;
}
bool AudioSystem::GetBusPaused(const std::string& name) const
{
	bool retVal = false;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getPaused(&retVal);
	}
	return retVal;
}

void AudioSystem::SetBusVolume(const std::string& name, float volume)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setVolume(volume);
	}
}

void AudioSystem::SetBusPaused(const std::string& name, bool pause)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setPaused(pause);
	}
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}