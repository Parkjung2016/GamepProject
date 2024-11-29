#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "MyFunc.h"

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
			if (nullptr != m_vecObj[i][j] && !m_vecObj[i][j]->GetIsDead())
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
	auto camera = GET_SINGLE(Camera);
	for (UINT i = 0; i < (UINT)LAYER::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			auto* obj = m_vecObj[i][j];
			if (!obj->GetIsDead())
			{
				Vec2 objRenderPos = camera->GetRenderPos(obj->GetPos());

				if (objRenderPos.x + obj->GetSize().x > 0 && objRenderPos.y < SCREEN_WIDTH && objRenderPos.y + obj->GetSize().y > 0 && objRenderPos.y < SCREEN_HEIGHT)
				{
					obj->Render(_hdc);

				}
				++j;
			}
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}

}

void Scene::Release()
{
	// 오브젝트 삭제.
	for (size_t i = 0; i < (UINT)LAYER::END; i++)
	{
		SafeDeleteVec(m_vecObj[i]);
	}
	GET_SINGLE(CollisionManager)->CheckReset();
}
