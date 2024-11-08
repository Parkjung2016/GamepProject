#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "Func.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Scene::Release();
}

void Scene::Init()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->Start();
		}
	}
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Update();
		}
	}

}

void Scene::LateUpdate()
{
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		for (UINT j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->LateUpdate();
		}
	}
}

void Scene::Render(HDC _hdc)
{
	//for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	//{
	//	for (size_t j = 0; j < m_vecObj[i].size(); ++j)
	//	{
	//		if (!m_vecObj[i][j]->GetIsDead())
	//			m_vecObj[i][j]->Render(_hdc);
	//	}
	//}
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j++]->Render(_hdc);
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}

}

void Scene::Release()
{
	// ������Ʈ ����.
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		SafeDeleteVec(m_vecObj[i]);
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}