#pragma once
// GameManager
//SAFE_DELETE()
// µø¿˚ ΩÃ±€≈Ê(¥Ÿ¿Ã≥™πÕ ΩÃ±€≈Ê)
// ¡§¿˚ ΩÃ±€≈Ê
#include "Define.h"
//#include "Object.h"

class Texture;
class Core
{
	DECLARE_SINGLE(Core)
public:
	bool Init(HWND _hwnd, HINSTANCE _hInst);
	void GameLoop();
	void CleanUp();
	void Clear() const;
private:
	void MainUpdate();
	void MainRender();
	void CreateGDI();


public:
	HINSTANCE GetWindowInstance()	const { return m_hInst; }


	const HWND& GetHwnd() const { return m_hWnd; }
	// ¿Ã∏ß πŸ≤Ÿ±‚
	const HDC& GetMainDC() const { return m_hDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _eType)
	{
		return m_colorBrushs[(UINT)_eType];
	}
	const HPEN& GetPen(PEN_TYPE _eType)
	{
		return m_colorPens[(UINT)_eType];
	}

private:
	HINSTANCE m_hInst;
	HBRUSH m_colorBrushs[(UINT)BRUSH_TYPE::END] = {};
	HPEN m_colorPens[(UINT)PEN_TYPE::END] = {};
	HWND m_hWnd;
	HDC  m_hDC; // Main DC

	Texture* m_pMemTex;

};
