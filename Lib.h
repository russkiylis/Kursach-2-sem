#pragma once

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Radiosignal.h"
#include "RadiosignalDlg.h"
#include <vector>


// ����� ����� ���������
class Lib_CoordLine {
public:
	CString value;
	double coord;

	Lib_CoordLine() { value = L""; coord = 0; }
	Lib_CoordLine(CString _value, double _coord) { value = _value; coord = _coord; }
};

// ����� ������������ ���������� ���������
class Lib_dXY {
public:
	double x;
	double y;

	Lib_dXY() { x = 0; y = 0; }
	Lib_dXY(double xcoord, double ycoord) { x = xcoord; y = ycoord; }
};

// �����, � ������� ���������� ������� ����������� ��������
class Lib_ValueConverter {
public:
	// ����������� float � CString c 2 ������� ����� �������
	CString floatToCString_2(float &number);

	// ����������� int � CString
	CString intToCString(int& number);
};

// ����� ������ � �������������� ���������
class Lib_InteractiveBoxesData : Lib_ValueConverter {
public:

	// ������ ������ �� ��������� int (� ������������ � ���� ������)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta);
	// ������ ������ �� ��������� int (� ������������ � ���� ������ � ���������������� ������)
	void IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier);

	// �������� �������� int � ��� �����������
	void CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox);

};

// ����� ���������� ����� ��������
class Lib_PointCalculation {
public:
	// ������� ����������������� ��� ������ ����� ������� �������
	Lib_dXY SignalCalculation(double &x);

	// ����������

	int N;
	int F;
	int Fm;
	int M;
};

// ����� ��������� ����� ��������
class Lib_GraphConverter : public Lib_PointCalculation {
public:
	// ��������� ����� ��� ��������� ������� (������ ��������� �� ������)
	CPoint GenerateDrawablePoint(CRect& rc, Lib_dXY &calculatedPoint, int x0, int y0, bool isLog=false);

	// ��������� ����� ������� �������
	void GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// ��������� ����� ������� ���
	void GenerateGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// ��������� ����� ��������� �� �
	void GenerateXCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec);

	// ��������� ����� ��������� �� y
	void GenerateYCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec);

	// ����������

	int XScale;
	int YScale;
	int XDensity, YDensity;
	bool isLog, IsDPF;
};