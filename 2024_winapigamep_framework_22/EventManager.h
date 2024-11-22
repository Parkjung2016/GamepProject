#pragma once
class Object;
struct tEvent
{
	EVENT_TYPE eveType;
	DWORD_PTR lParam;
	DWORD_PTR wParam;
public:
	bool operator==(const tEvent& other)
	{
		return eveType == other.eveType && lParam == other.lParam && wParam == other.wParam;
	}
};
class EventManager
{
	DECLARE_SINGLE(EventManager);
public:
	void Update();
	void AddEvent(tEvent _tEve);
private:
	void Excute(const tEvent& _eve);
private:
	vector<tEvent> m_vecEvent;
	vector<Object*> m_vecDead;
};