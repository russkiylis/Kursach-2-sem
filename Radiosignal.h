﻿
// Kursach.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#define _USE_MATH_DEFINES
#include "resource.h"		// основные символы
#include "Lib.h"
#include <math.h>
#include <vector>

// CRadiosignalApp:
// Сведения о реализации этого класса: Kursach.cpp
//

class CRadiosignalApp : public CWinApp
{
public:
	CRadiosignalApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CRadiosignalApp theApp;