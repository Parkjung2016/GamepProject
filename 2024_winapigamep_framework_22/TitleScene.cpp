#include "pch.h"
#include "TitleScene.h"

#include "EnemyStateMachine.h"
#include "BtnUI.h"
#include "Object.h"
#include "SceneManager.h"
#include "PanelUI.h"
#include "UI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

void TitleScene::Init()
{
	srand((unsigned int)time(nullptr));
	Vec2 resolution = { SCREEN_WIDTH,SCREEN_HEIGHT };


	Vec2 size = { 500.f,300.f };
	UI* pPanelUI = new PanelUI(false);
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetSize(size);
	pPanelUI->SetPos({ resolution.x - size.x,0.f });


	BtnUI* pBtnUI = new BtnUI;
	pBtnUI->SetName(L"ChildUI");
	size = { 100.f,40.f };
	pBtnUI->SetSize(size);
	pBtnUI->SetPos({ 0.f,0.f });
	pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, LAYER::UI);
	Scene::Init();


}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
void TitleScene::Update()
{
	Scene::Update();
}
