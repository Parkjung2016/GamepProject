#include "pch.h"
#include "GameScene.h"

#include "AudioSystem.h"
#include "Background.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "MapManager.h"
#include "SoundEvent.h"
#include "SoundObject.h"
#include "TextUI.h"
#include "TitleScene.h"

GameScene::GameScene()
	: m_pPlayer(nullptr),
	m_iCurrentInitCount(0)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	GET_SINGLE(MapManager)->LoadMap(L"Json\\Tileset.json"); // ¸Ê ·Îµå
	m_pBGMSoundObject = new SoundObject;
	m_pBGMSoundObject->PlayEvent("event:/Music/GameBGM");
	AddObject(m_pBGMSoundObject, LAYER::DEFAULT);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BOSS, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BULLET, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BULLET, LAYER::BOSS);
	GET_SINGLE(Camera)->FadeOut(0);
	GET_SINGLE(Camera)->FadeIn(2.f);

	TextUI* keyGuideMoveText = new TextUI;
	keyGuideMoveText->SetText(L"Move : Arrows");
	keyGuideMoveText->SetPos({ SCREEN_WIDTH - 1,0 });
	keyGuideMoveText->SetAlign(TA_RIGHT);
	AddObject(keyGuideMoveText, LAYER::UI);

	TextUI* keyGuideAttackText = new TextUI;
	keyGuideAttackText->SetText(L"Attack : A");
	keyGuideAttackText->SetPos({ SCREEN_WIDTH - 1,25 });
	keyGuideAttackText->SetAlign(TA_RIGHT);
	AddObject(keyGuideAttackText, LAYER::UI);

	TextUI* keyGuideJumpText = new TextUI;
	keyGuideJumpText->SetText(L"Jump : Space");
	keyGuideJumpText->SetPos({ SCREEN_WIDTH - 1,50 });
	keyGuideJumpText->SetAlign(TA_RIGHT);
	AddObject(keyGuideJumpText, LAYER::UI);

	TextUI* keyGuideBlockText = new TextUI;
	keyGuideBlockText->SetText(L"Block : X");
	keyGuideBlockText->SetPos({ SCREEN_WIDTH - 1,75 });
	keyGuideBlockText->SetAlign(TA_RIGHT);
	AddObject(keyGuideBlockText, LAYER::UI);




	Scene::Init();
	m_iCurrentInitCount = 0;
	m_bIsCompleteInit = false;

}

void GameScene::Update()
{
	if (!m_bIsCompleteInit)return;
	Scene::Update();

}

void GameScene::LateUpdate()
{

	Scene::LateUpdate();
}


void GameScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
}

void GameScene::AfterRender()
{
	Scene::AfterRender();
	if (m_iCurrentInitCount >= 100 && !m_bIsCompleteInit)
	{
		m_bIsCompleteInit = true;
	}
	else
	{
		m_iCurrentInitCount++;
	}
}
