#include "pch.h"
#include "EditorSceneDialog.h"

#include "Core.h"
#include "EditorScene.h"
#include "GameManager.h"
#include "Resource.h"
#include "ResourceManager.h"

EditorSceneDialog* EditorSceneDialog::s_Dlg = nullptr;
EditorSceneDialog::EditorSceneDialog()
	: m_Scene(nullptr)
{
	s_Dlg = this;
}

EditorSceneDialog::~EditorSceneDialog()
{
	s_Dlg = nullptr;
}

bool EditorSceneDialog::Init()
{
	//â ����
	HINSTANCE hInst=GET_SINGLE(Core)->GetWindowInstance();
	HWND hwnd=GET_SINGLE(Core)->GetHwnd();
	m_hDlg = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG_TILEMAPEDIT), hwnd, EditorSceneDialog::WndProc);

	//â ���
	ShowWindow(m_hDlg, SW_SHOW);

	//�Է¶��� �⺻���� �⺻ �̹����� ����.
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, 40, FALSE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, 40, FALSE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, 20, FALSE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, 27, FALSE);


	return true;
}

void EditorSceneDialog::CreateTileMap()
{
	BOOL Result = FALSE;

	unsigned int CountX = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTX, &Result, false);
	unsigned int CountY = GetDlgItemInt(m_hDlg, IDC_EDIT_COUNTY, &Result, false);
	unsigned int SizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEX, &Result, false);
	unsigned int SizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_SIZEY, &Result, false);

	m_Scene->CreateTileMap(CountX, CountY, SizeX, SizeY);
	Texture* tileTex=GET_SINGLE(ResourceManager)->TextureLoad(L"Tile", L"Texture\\Map\\Tiles.bmp");

	m_Scene->SetTileTexture(tileTex);
}

void EditorSceneDialog::LoadTexture()
{
}

void EditorSceneDialog::SelectTexture()
{
}

LRESULT EditorSceneDialog::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//CLOSE �޽��� -> â �ݱ� �޽��� ����
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
		//â �ݱ� �޽��� -> �޽��� ������ false�� �ٲ㼭 �ߴܽ�Ŵ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CREATE:
			s_Dlg->CreateTileMap();
			break;
		}
		break;

	default:
		break;
	}


	return 0;
}
