#pragma once

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"
#include <vector>


// Вещественные декартовы координаты
typedef struct dXY {
	double x;
	double y;
} dXY;

// Целочисленные декартовы координаты
typedef struct iXY {
	int x;
	int y;
} iXY;

// Класс, в котором содержатся функции конвертации значений
class Lib_Converter {
public:
	// Конвертация float в CString c 2 знаками после запятой
	CString floatToCString_2(float &number);

	// Конвертация int в CString
	CString intToCString(int& number);
};

// Класс работы с интерактивными объектами
class Lib_InteractiveBoxesData : Lib_Converter {
public:

	// Работа спинов со значением int (с ограничением с двух сторон)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta);
	// Работа спинов со значением int (с ограничением с двух сторон и мультипликатором дельты)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier);

	// Проверка значения int и его возвращение
	void CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox);
};

class Lib_PointCalculation {
public:
	// Подсчёт непреобразованной для вывода точки графика сигнала
	dXY SignalCalculation(double &x);

	// Подсчёт графика ДПФ
	dXY DPFCalculation(double& N);
};

class Lib_GraphConverter : Lib_PointCalculation {
public:
	// Генерация точки для рисования графика (начало координат по центру)
	CPoint GenerateDrawablePoint(CRect& rc, dXY &calculatedPoint);

	// Генерация точек графика сигнала
	void GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// Генерация точек графика ДПФ
	void GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec);
};