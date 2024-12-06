#include "pch.h"
#include "UIManager.h"

#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "UI.h"

void UIManager::Init()
{
	m_pFocusedUI = nullptr;
}

void UIManager::Update()
{

	m_pFocusedUI = GetFocusedUI();
	if (!m_pFocusedUI)
		return;
	UI* pTargetUI = GetTargetedUI(m_pFocusedUI);

	bool bLBDown = GET_KEYDOWN(KEY_TYPE::LBUTTON);
	bool bLBUp = GET_KEYUP(KEY_TYPE::LBUTTON);

	if (nullptr != pTargetUI && !pTargetUI->GetIsDead())
	{
		pTargetUI->MouseOn();

		if (bLBDown)
		{
			pTargetUI->MouseLBDown();
			pTargetUI->m_bLBDown = true;
		}
		else if (bLBUp)
		{
			pTargetUI->MouseLBUp();

			if (pTargetUI->m_bLBDown)
			{
				pTargetUI->MouseLBClicked();
			}

			pTargetUI->m_bLBDown = false;
		}
	}

}

void UIManager::SetFocusedUI(UI* _pUI)
{
	if (m_pFocusedUI == _pUI || nullptr == m_pFocusedUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	m_pFocusedUI = _pUI;


	if (nullptr == m_pFocusedUI)
		return;

	std::shared_ptr<Scene> pCurScene = GET_SINGLE(SceneManager)->GetCurrentScene();
	vector<Object*>& vecUI = pCurScene->GetUIObjects();

	vector<Object*>::const_iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}

	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

UI* UIManager::GetFocusedUI() const
{
	std::shared_ptr<Scene> pCurScene = GET_SINGLE(SceneManager)->GetCurrentScene();
	if (nullptr == pCurScene)return nullptr;
	vector<Object*> vecUI;
	vecUI = pCurScene->GetUIObjects();

	bool bLBDown = GET_KEYDOWN(KEY_TYPE::LBUTTON);

	UI* pFocusedUI = m_pFocusedUI;

	if (!bLBDown)
	{
		return pFocusedUI;
	}

	vector<Object*>::const_iterator targetiter = vecUI.end();
	vector<Object*>::const_iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((UI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}

	}

	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}
	pFocusedUI = ((UI*)*targetiter);
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

UI* UIManager::GetTargetedUI(UI* _pParentUI)
{
	bool bLBUp = GET_KEYUP(KEY_TYPE::LBUTTON);

	UI* pTargetUI = nullptr;

	static	list<UI*> list;
	static	vector<UI*> vecNoneTarget;

	list.clear();
	vecNoneTarget.clear();

	list.push_back(_pParentUI);

	while (!list.empty())
	{
		UI* pUI = list.front();

		list.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}


		const vector<UI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			list.push_back(vecChild[i]);
		}
	}

	if (bLBUp)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{

			vecNoneTarget[i]->m_bLBDown = false;
		}
	}

	return pTargetUI;
}
