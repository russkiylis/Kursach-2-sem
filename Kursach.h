﻿
// Kursach.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CKursachApp:
// Сведения о реализации этого класса: Kursach.cpp
//

class CKursachApp : public CWinApp
{
public:
	CKursachApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CKursachApp theApp;
