#include "pch.h"
#include "TitleScene.h"

#include <functional>

#include "Audio.h"
#include "AudioSystem.h"
#include "Background.h"
#include "EnemyStateMachine.h"
#include "BtnUI.h"
#include "EventManager.h"

#include "Object.h"
#include "PanelUI.h"
#include "SoundObject.h"
#include "UI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);
SoundObject* TitleScene::m_pBGMSoundObject;
void TitleScene::Init()
{
	GET_SINGLE(AudioSystem)->SetBusVolume("bus:/", 1);

	GET_SINGLE(Camera)->SetTarget(nullptr);
	GET_SINGLE(Camera)->SetLookAt({ 0,0 });
	GET_SINGLE(Camera)->FadeIn(1.f);
	m_pBGMSoundObject = new SoundObject;
	m_pBGMSoundObject->PlayEvent("event:/Music/TitleBGM");
	AddObject(m_pBGMSoundObject, LAYER::DEFAULT);


	srand((unsigned int)time(nullptr));
	Vec2 size = { 500.f,450.f };
	PanelUI* pPanelUI = new PanelUI();
	pPanelUI->SetIgnored();
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetTexture(L"Panel", L"Texture\\UI\\Panel.bmp");
	pPanelUI->SetSize(size);
	pPanelUI->SetPos({ SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f });


	BtnUI* pBtnUI = new BtnUI;
	pBtnUI->SetNormalTexture(L"StartButton", L"Texture\\UI\\StartButton.bmp");
	pBtnUI->SetPressTexture(L"StartButton_Press", L"Texture\\UI\\StartButton_Press.bmp");
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetPos({ 0,0 });
	pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, LAYER::UI);


	Background* pBackground = new Background;
	pBackground->SetTexture(L"TitleBackground", L"Texture\\TitleBackground.bmp");
	pBackground->SetPos({ -pBackground->GetSize().x / 2.f,pBackground->GetSize().y / 2.f });
	AddObject(pBackground, LAYER::BACKGROUND);
	Scene::Init();


}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	TitleScene::GetBGMSoundObject()->GetComponent<Audio>()->StopAllEvents();
	tEvent evt;
	evt.lParam = (DWORD_PTR)SCENE_TYPE::InGame;
	evt.eveType = EVENT_TYPE::SCENE_CHANGE;
	GET_SINGLE(EventManager)->AddEvent(evt);
}
void TitleScene::Update()
{
	Scene::Update();
}
