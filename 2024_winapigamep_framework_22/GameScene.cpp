#include "pch.h"
#include "GameScene.h"

#include "BtnUI.h"
#include "Enemy.h"
#include "PanelUI.h"
#include "Player.h"
#include "SceneManager.h"
void ChangeScene2(DWORD_PTR, DWORD_PTR);

void GameScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	Vec2 vResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
	GET_SINGLE(Camera)->SetLookAt(vResolution / 2.f);


	Vec2 resolution = { SCREEN_WIDTH,SCREEN_HEIGHT };

	Vec2 size = { 500.f,300.f };
	UI* pPanelUI = new PanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetSize(size);
	pPanelUI->SetPos({ resolution.x - size.x,0.f });


	BtnUI* pBtnUI = new BtnUI;
	pBtnUI->SetName(L"ChildUI");
	size = { 100.f,40.f };
	pBtnUI->SetSize(size);
	pBtnUI->SetPos({ 0.f,0.f });
	pBtnUI->SetClickedCallBack(ChangeScene2, 0, 0);

	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, LAYER::UI);

	UI* pClonePanel = pPanelUI->Clone();
	Vec2 pos = pClonePanel->GetPos();
	pClonePanel->SetPos(pos + Vec2(-300.f, 0.f));
	((BtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene2, 0, 0);
	AddObject(pClonePanel, LAYER::UI);
}
void ChangeScene2(DWORD_PTR, DWORD_PTR)
{
	GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
}