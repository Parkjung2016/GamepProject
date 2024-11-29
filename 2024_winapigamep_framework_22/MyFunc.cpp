#include "pch.h"
#include "MyFunc.h"

#include "EventManager.h"


void CreateObject(Object* _pObj, LAYER _eLayer)
{
	tEvent eve = {};
	eve.lParam = (DWORD_PTR)_pObj;
	eve.wParam = (DWORD_PTR)_eLayer;

	GET_SINGLE(EventManager)->AddEvent(eve);
}

void DeleteObject(Object* _pObj)
{
	tEvent eve = {};
	eve.eveType = EVENT_TYPE::DELETE_OBJECT;
	eve.lParam = (DWORD_PTR)_pObj;

	GET_SINGLE(EventManager)->AddEvent(eve);
}

void FScanf(char* _pOutBuff, FILE* _pFile)
{


	int i = 0;
	while (true)
	{

		char c = (char)(getc(_pFile));
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}
		_pOutBuff[i++] = c;
	}

}

void SaveWString(const std::wstring& _str, FILE* _pFile)
{
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	fwrite(&iLen, sizeof(size_t), 1, _pFile);
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(std::wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	fread(&iLen, sizeof(size_t), 1, _pFile);

	wchar_t szBuff[256] = {};
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);
	_str = szBuff;
}
