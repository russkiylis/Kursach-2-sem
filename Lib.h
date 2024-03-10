#pragma once

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Radiosignal.h"
#include "RadiosignalDlg.h"
#include <vector>


// Класс линии координат
class Lib_CoordLine {
public:
	CString value;
	double coord;

	Lib_CoordLine() { value = L""; coord = 0; }
	Lib_CoordLine(CString _value, double _coord) { value = _value; coord = _coord; }
};

// Класс вещественных декартовых координат
class Lib_dXY {
public:
	double x;
	double y;

	Lib_dXY() { x = 0; y = 0; }
	Lib_dXY(double xcoord, double ycoord) { x = xcoord; y = ycoord; }
};

// Класс, в котором содержатся функции конвертации значений
class Lib_ValueConverter {
public:
	// Конвертация float в CString c 2 знаками после запятой
	CString floatToCString_2(float &number);

	// Конвертация int в CString
	CString intToCString(int& number);
};

// Класс работы с интерактивными объектами
class Lib_InteractiveBoxesData : Lib_ValueConverter {
public:

	// Работа спинов со значением int (с ограничением с двух сторон)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta);
	// Работа спинов со значением int (с ограничением с двух сторон и мультипликатором дельты)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier);

	// Проверка значения int и его возвращение
	void CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox);

};

// Класс вычислений точек графиков
class Lib_PointCalculation {
public:
	// Подсчёт непреобразованной для вывода точки графика сигнала
	Lib_dXY SignalCalculation(double &x);

	// Переменные

	int N;
	int F;
	int Fm;
	int M;
};

// Класс генерации точек графиков
class Lib_GraphConverter : public Lib_PointCalculation {
public:
	// Генерация точки для рисования графика (начало координат по центру)
	CPoint GenerateDrawablePoint(CRect& rc, Lib_dXY &calculatedPoint, int x0, int y0, bool isLog=false);

	// Генерация точек графика сигнала
	void GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// Генерация точек графика ДПФ
	void GenerateGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// Генерация линий координат по х
	void GenerateXCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec);

	// Генерация линий координат по y
	void GenerateYCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec);

	// Переменные

	int XScale;
	int YScale;
	int XDensity, YDensity;
	bool isLog, IsDPF;
};