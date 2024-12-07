#include "pch.h"
#include "ResourceManager.h"

#include "Core.h"
#include "MyFunc.h"
#include "Texture.h"
void ResourceManager::Init()
{
	::GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");
	SetWindowText(GET_SINGLE(Core)->GetHwnd(), L"Shoot");
	wstring fontPath = m_resourcePath;
	fontPath += L"Font\\NeoDunggeunmoPro-Regular.ttf";
	AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, 0);

}

Texture* ResourceManager::TextureLoad(const wstring& _key, const wstring& _path)
{
	Texture* pTex = TextureFind(_key);
	if (nullptr != pTex)
	{
		return pTex;
	}

	// 없어요 최초입니다. 만들어주세요.
	// 1. 경로 설정
	wstring texpath = m_resourcePath;
	texpath += _path;

	// 2. Texture 만들어야죠?
	pTex = new Texture;
	pTex->Load(texpath);
	pTex->SetKey(_key);
	pTex->SetPath(_path);
	m_mapTextures.insert({ _key,pTex });
	return pTex;
}

Texture* ResourceManager::CreateTexture(const wstring& _key, UINT _iWidth, UINT _iHeight)
{
	Texture* pTex = TextureFind(_key);
	if (nullptr != pTex)
		return pTex;

	pTex = new Texture;
	pTex->Create(_iWidth, _iHeight);
	pTex->SetKey(_key);

	m_mapTextures.insert({ _key,pTex });
	return pTex;
}

Texture* ResourceManager::TextureFind(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::Release()
{
	SafeDeleteMap(m_mapTextures);
	//SafeDeleteMap(m_mapSounds);
	wstring fontPath = m_resourcePath;
	fontPath += L"Font\\NeoDunggeunmoPro-Regular.ttf";
	RemoveFontResourceEx(fontPath.c_str(), FR_PRIVATE, 0);
	//// 다 쓰고 난 후 시스템 닫고 반환
	//m_pSoundSystem->close();
	//m_pSoundSystem->release();
}

//void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop, bool _isBGM)
//{
//	if (FindSound(_key))
//		return;
//	wstring strFilePath = m_resourcePath;
//	strFilePath += _path;
//
//	// wstring to string
//	std::string str;
//	str.assign(strFilePath.begin(), strFilePath.end());
//
//	// 루프할지 말지 결정
//	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
//	if (!_isLoop)
//		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
//
//	tSoundInfo* ptSound = new tSoundInfo;
//	ptSound->IsLoop = _isLoop;
//	ptSound->IsBGM = _isBGM;
//	// 사운드 객체를 만드는 것은 system임.
//							//파일경로,  FMOD_MODE, NULL, &sound
//	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
//	m_mapSounds.insert({ _key, ptSound });
//}
//
//void ResourceManager::Play(const wstring& _key)
//{
//	tSoundInfo* ptSound = FindSound(_key);
//	if (!ptSound)
//		return;
//	m_pSoundSystem->update(); // play할때 update를 주기적으로 호출해야 사운드가 정지되지 않음.
//	SOUND_CHANNEL eChannel = SOUND_CHANNEL::EFFECT;
//	if (ptSound->IsBGM)
//		eChannel = SOUND_CHANNEL::BGM;
//	// 사운드 재생 함수. &channel로 어떤 채널을 통해 재생되는지 포인터 넘김
//	m_pSoundSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);
//}
//
//void ResourceManager::Stop(SOUND_CHANNEL _channel)
//{
//	m_pChannel[(UINT)_channel]->stop();
//}
//
//void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
//{
//	// 0.0 ~ 1.0 볼륨 조절
//	m_pChannel[(UINT)_channel]->setVolume(_vol);
//}
//
//void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
//{
//	// bool값이 true면 일시정지. 단, 이 함수를 쓰려면 Createsound할때 
//// FMOD_MODE가 FMOD_LOOP_NORMAL 이어야 함.
//	m_pChannel[(UINT)_channel]->setPaused(_ispause);
//}
//
//void ResourceManager::PlayFootstepSound()
//{
//	int rdx = rand() % 9 + 1;
//	wstring soundKey = L"Footstep_";
//	soundKey += std::to_wstring(rdx);
//	Play(soundKey);
//}
//
//void ResourceManager::PlayJumpStartSound()
//{
//	int rdx = rand() % 2 + 1;
//	wstring soundKey = L"Jump_Start_";
//	soundKey += std::to_wstring(rdx);
//	std::wcout << soundKey << endl;
//	Play(soundKey);
//}
//void ResourceManager::PlayJumpLandSound()
//{
//	int rdx = rand() % 2 + 1;
//	wstring soundKey = L"Jump_Land_";
//	soundKey += std::to_wstring(rdx);
//	Play(soundKey);
//}
//
//tSoundInfo* ResourceManager::FindSound(const wstring& _key)
//{
//	map<wstring, tSoundInfo*>::iterator iter = m_mapSounds.find(_key);
//
//	if (iter == m_mapSounds.end())
//		return nullptr;
//	return iter->second;
//}
