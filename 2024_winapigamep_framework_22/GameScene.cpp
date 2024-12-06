#include "pch.h"
#include "GameScene.h"

#include "Background.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Tile.h"
#include "InputManager.h"
#include "MapManager.h"
#include "Player.h"
#include "ResourceManager.h"
#include "TextUI.h"

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
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BOSS, LAYER::TILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BULLET, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BULLET, LAYER::BOSS);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	GET_SINGLE(Camera)->FadeOut(0);
	GET_SINGLE(Camera)->FadeIn(2.f);

	TextUI* keyGuideMoveText = new TextUI;
	keyGuideMoveText->SetText(L"Move : WASD");
	keyGuideMoveText->SetPos({ SCREEN_WIDTH - 1,0 });
	keyGuideMoveText->SetAlign(TA_RIGHT);
	AddObject(keyGuideMoveText, LAYER::UI);

	TextUI* keyGuideAttackText = new TextUI;
	keyGuideAttackText->SetText(L"Attack : A");
	keyGuideAttackText->SetPos({ SCREEN_WIDTH - 1,-50 });
	keyGuideAttackText->SetAlign(TA_RIGHT);
	AddObject(keyGuideAttackText, LAYER::UI);

	//TextUI* keyGuideJumpText = new TextUI;
	//keyGuideJumpText->SetText(L"Jump : Space");
	//keyGuideJumpText->SetPos({ SCREEN_WIDTH - 1,-400 });
	//keyGuideJumpText->SetAlign(TA_RIGHT);
	//AddObject(keyGuideJumpText, LAYER::UI);

	//TextUI* keyGuideBlockText = new TextUI;
	//keyGuideBlockText->SetText(L"Jump : X");
	//keyGuideBlockText->SetPos({ SCREEN_WIDTH - 1,-600 });
	//keyGuideBlockText->SetAlign(TA_RIGHT);
	//AddObject(keyGuideBlockText, LAYER::UI);

	Scene::Init();
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
	m_iCurrentInitCount++;
}
