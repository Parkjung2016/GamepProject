#pragma once

#include "Camera.h"
#include "Component.h"
#include "Collider.h"
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Start() {};
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;
	virtual Object* Clone() = 0;
	void ComponentRender(HDC _hdc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetSize() const { return m_vSize; }
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
	const bool& GetIsDead() const { return m_IsDie; }
	void SetDead() { m_IsDie = true; }
	void SetName(wstring _name) { m_name = _name; }
	const wstring& GetName() const { return m_name; }

private:
	bool m_IsDie;
	wstring m_name;
public:
	template<typename T>
	T* AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		m_vecComponents.push_back(com);
		return com;
	}
	template<typename T>
	void RemoveComponent()
	{
		auto iter = std::find_if(m_vecComponents.begin(), m_vecComponents.end(),
			[](Component* com)
			{
				return dynamic_cast<T*>(com) != nullptr;
			});

		// 요소를 찾았다면 삭제
		if (iter != m_vecComponents.end())
		{
			delete* iter;  // 메모리 해제
			m_vecComponents.erase(iter);  // 벡터에서 제거
		}
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
private:
	//POINT m_ptPos;
	//POINT m_ptSize;
	Vec2 m_vPos;
	Vec2 m_vSize;
	vector<Component*> m_vecComponents;
};

