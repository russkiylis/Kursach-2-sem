
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

// Глобальная переменная N (Количество отсчётов сигнала)
extern int G_N;
// Глобальная переменная F (Несущая частота сигнала)
extern int G_F;
// Глобальная переменная Fm (Частота модуляции)
extern int G_Fm;
// Глобальная переменная M (Глубина модуляции)
extern int G_M;
// Глобальная переменная масштаба графика сигнала по Х
extern double G_SignalGraph_XScale;
// Глобальная переменная масштаба графика сигнала по Y
extern int G_SignalGraph_YScale;

// Глобальная переменная масштаба графика ДПФ по Х
extern double G_DPFGraph_XScale;
// Глобальная переменная масштаба графика ДПФ по Y
extern int G_DPFGraph_YScale;
// Глобальная переменная логарифмирования графика ДПФ по Y
extern bool G_DPFGraph_IsLog;