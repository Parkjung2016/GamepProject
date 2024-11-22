#pragma once
class EditorScene;
class EditorSceneDialog
{
	friend class EditorScene;

private:
	EditorSceneDialog();
	~EditorSceneDialog();

private:
	EditorScene* m_Scene;
	HWND	m_hDlg;
	HWND	m_hTextureListBox;
	int		m_SelectTextureIndex;
	TCHAR	m_SelectTextureName[128];
	std::shared_ptr<class Texture>	m_SelectTexture;

public:
	bool Init();
	void CreateTileMap();
	void LoadTexture();
	void SelectTexture();
public:
	static EditorSceneDialog* s_Dlg;
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

