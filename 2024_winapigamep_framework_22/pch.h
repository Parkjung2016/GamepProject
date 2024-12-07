#pragma once

// ���� include
#include "fmod_studio.hpp"
#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<ctime>
#define _USE_MATH_DEFINES
#include<math.h>

// My Header
#include "CombatData.h"
#include "Define.h"
#include "Enums.h"
#include "Vec2.h"

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")
#pragma comment(lib, "fmodstudioL_vc.lib") 
#pragma comment(lib, "fmodstudio_vc.lib")
// ���� using
using std::vector;
using std::map;
using std::list;
using std::wstring;

// ���� define
#define PI 3.14159265f
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

// ������ �ܼ�â
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>
using std::cout;
using std::endl;