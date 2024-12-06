#pragma once
#include "Object.h"
//#include "Object.h"
class Object; // Ŭ���� ���漱��
class Scene
{
public:
	Scene();
	virtual ~Scene(); // ���� �Ҹ���
public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hdc);
	virtual void AfterRender();
	virtual void Release();
public:
	void AddObject(Object* _obj, LAYER _type)
	{
		m_vecObj[(UINT)_type].push_back(_obj);
		_obj->Start();
	}
	const vector<Object*>& GetLayerObjects(LAYER _type)
	{
		return m_vecObj[(UINT)_type];
	}

	vector<Object*>& GetUIObjects()
	{
		return m_vecObj[(UINT)LAYER::UI];
	}

protected:
	bool m_bIsCompleteInit;
private:
	//Object m_obj;
	//Object* m_pObj;
	vector<Object*> m_vecObj[(UINT)LAYER::END];

};

