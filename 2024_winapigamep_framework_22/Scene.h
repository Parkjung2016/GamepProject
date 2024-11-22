#pragma once
//#include "Object.h"
class Object; // 클래스 전방선언
class TileMap;
class Scene
{
public:
	Scene();
	virtual ~Scene(); // 가상 소멸자
public:
	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC _hdc);
	virtual void Release();
public:
	void AddObject(Object* _obj, LAYER _type)
	{
		m_vecObj[(UINT)_type].push_back(_obj);
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
	TileMap* m_TileMap;
public:
	void SetTileMap(TileMap* TileMap);
	TileMap* GetTileMap() const { m_TileMap; }
private:
	//Object m_obj;
	//Object* m_pObj;
	vector<Object*> m_vecObj[(UINT)LAYER::END];

};

