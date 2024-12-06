#include "pch.h"
#include "EventManager.h"

#include "MyFunc.h"
#include "Object.h"
#include "Scene.h"
#include "SceneManager.h"
#include "UIManager.h"

void EventManager::Update()
{
	// 이전 프레임에서 등록해둔
	SafeDeleteVec(m_vecDead);

	for (auto& eve : m_vecEvent)
		Excute(eve);
	m_vecEvent.clear();
}

void EventManager::AddEvent(tEvent _tEve)
{
	if (std::find(m_vecEvent.begin(), m_vecEvent.end(), _tEve) == m_vecEvent.end())
	{
		m_vecEvent.push_back(_tEve);
	}
}


void EventManager::Excute(const tEvent& _eve)
{
	switch (_eve.eveType)
	{
	case EVENT_TYPE::DELETE_OBJECT:
	{
		Object* pDeadObj = (Object*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
	break;
	case EVENT_TYPE::CREATE_OBJECT:
	{
		Object* pNewObj = (Object*)_eve.lParam;
		LAYER eType = (LAYER)_eve.wParam;

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pNewObj, eType);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		SCENE_TYPE sceneType = (SCENE_TYPE)_eve.lParam;
		wstring sceneName = SceneNames[(byte)sceneType];
		GET_SINGLE(UIManager)->SetFocusedUI(nullptr);
		GET_SINGLE(SceneManager)->LoadScene(sceneName);
	}
	break;
	}
}
