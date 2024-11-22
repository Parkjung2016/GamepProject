#include "pch.h"
#include "EditorScene.h"

#include "EditorSceneDialog.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Player.h"
#include "TileMap.h"

EditorScene::EditorScene()
	: m_TileMapDlg(nullptr)
{
	GET_SINGLE(GameManager)->SetEditorMode(true);
}

EditorScene::~EditorScene()
{
	GET_SINGLE(GameManager)->SetEditorMode(false);

	delete m_TileMapDlg;
}

void EditorScene::Init()
{
	Scene::Init();
}

void EditorScene::Update()
{
	Scene::Update();

	if (GET_KEYDOWN(KEY_TYPE::DOWN))
	{
		OpenTileMapEditor();
	}
}

void EditorScene::CreateTileMap(int CountX, int CountY, int SizeX, int SizeY)
{
	if (!m_TileMap)
	{
		m_TileMap = new TileMap;
		m_TileMap->SetName(L"EditTileMap");
		AddObject(m_TileMap, LAYER::BACKGROUND);
	}


	m_TileMap->CreateTile(CountX, CountY, Vec2((float)SizeX, (float)SizeY));
}

void EditorScene::SetTileTexture(Texture* Texture)
{
}

void EditorScene::MoveLeft()
{
}

void EditorScene::MoveRight()
{
}

void EditorScene::MoveUp()
{
}

void EditorScene::MoveDown()
{
}

void EditorScene::OpenTileMapEditor()
{
	m_TileMapDlg = new EditorSceneDialog;
	m_TileMapDlg->Init();
	m_TileMapDlg->m_Scene = this;
}
