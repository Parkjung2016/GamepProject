#pragma once
#include "Scene.h"

class EditorSceneDialog;
class Texture;
class TileMap;
class EditorScene :
	public Scene
{
	friend class SceneManager;

public:
	EditorScene();
	~EditorScene() override;
public:
	void Init() override;
	void Update() override;;

private:
	EditorSceneDialog* m_TileMapDlg;


public:
	void CreateTileMap(int CountX, int CountY, int SizeX, int SizeY);
	void SetTileTexture(Texture* Texture);

public:
	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void OpenTileMapEditor();
};

