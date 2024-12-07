#include "pch.h"
#include "Core.h"

#include "AudioSystem.h"
#include "Camera.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "GDISelector.h"
#include "MapManager.h"
#include "Texture.h"
#include "UIManager.h"
void* buffer;
bool Core::Init(HWND _hwnd, HINSTANCE _hInst)
{
	// 변수 초기화
	m_hInst = _hInst;
	m_hWnd = _hwnd;
	m_hDC = ::GetDC(m_hWnd);

	m_pMemTex = GET_SINGLE(ResourceManager)->CreateTexture(L"BackBuffer", SCREEN_WIDTH, SCREEN_HEIGHT);

	CreateGDI();
	// === Manager Init === 
	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(AudioSystem)->Init();

	GET_SINGLE(InputManager)->Init();
	GET_SINGLE(MapManager)->Init();
	GET_SINGLE(ResourceManager)->Init();
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(UIManager)->Init();
	GET_SINGLE(Camera)->Init();

	//m_obj.SetPos(Vec2(SCREEN_WIDTH / 2
	//				,SCREEN_HEIGHT/ 2));
	//m_obj.SetSize(Vec2(100, 100));
	return true;
}
void Core::CleanUp()
{
	::ReleaseDC(m_hWnd, m_hDC);
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_colorPens[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		// Hollow 제외하고
		DeleteObject(m_colorBrushs[i]);
	}

	GET_SINGLE(AudioSystem)->Release();

	GET_SINGLE(ResourceManager)->Release();
}

void Core::Clear() const
{
	GDISelector gdi(m_pMemTex->GetTexDC(), BRUSH_TYPE::HOLLOW);
	//Rectangle(m_pMemTex->GetTexDC(), -1, -1, SCREEN_WIDTH + 1, SCREEN_HEIGHT + 1);
	::PatBlt(m_pMemTex->GetTexDC(), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);
}

void Core::GameLoop()
{

	//static int callcount = 0;
	//++callcount;
	//static int prev = GetTickCount64();
	//int cur = GetTickCount64();
	//if (cur - prev > 1000)
	//{
	//	prev = cur;
	//	callcount = 0;
	//}
	MainUpdate();
	MainRender();
	MainAfterRender();
	GET_SINGLE(EventManager)->Update();

}



void Core::MainUpdate()
{
	// === Manager Update === 
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(CollisionManager)->Update();
	GET_SINGLE(UIManager)->Update();
	GET_SINGLE(Camera)->Update();
	GET_SINGLE(AudioSystem)->Update();


}

void Core::MainRender()
{
	Clear();

	// 2. Render
	GET_SINGLE(SceneManager)->Render(m_pMemTex->GetTexDC());
	GET_SINGLE(Camera)->Render(m_pMemTex->GetTexDC());
	// 3. display	
	::BitBlt(m_hDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		m_pMemTex->GetTexDC(), 0, 0, SRCCOPY);

	//	::TransparentBlt();
	   //::StretchBlt();
	   //::PlgBlt();
	   //::AlphaBlend();
}

void Core::MainAfterRender()
{
	GET_SINGLE(SceneManager)->AfterRender();

}

void Core::CreateGDI()
{
	// HOLLOW
	m_colorBrushs[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_colorBrushs[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	m_colorBrushs[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_colorBrushs[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_colorBrushs[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_colorBrushs[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));
	//RED GREEN BLUE PEN
	m_colorPens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_colorPens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_colorPens[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_colorPens[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}
