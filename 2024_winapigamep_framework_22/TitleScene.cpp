#include "pch.h"
#include "TitleScene.h"

#include "EnemyStateMachine.h"
#include "BtnUI.h"
#include "EventManager.h"

#include "InputManager.h"
#include "Object.h"
#include "SceneManager.h"
#include "PanelUI.h"
#include "UI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

void TitleScene::Init()
{
	GET_SINGLE(Camera)->FadeIn(1.f);

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
	Scene::Init();


}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	tEvent evt;
	evt.lParam = (DWORD_PTR)SCENE_TYPE::InGame;
	evt.eveType = EVENT_TYPE::SCENE_CHANGE;
	GET_SINGLE(EventManager)->AddEvent(evt);
}
void TitleScene::Update()
{
	Scene::Update();
}
