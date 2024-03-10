#pragma once

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"
#include <vector>


// ������������ ��������� ����������
typedef struct dXY {
	double x;
	double y;
} dXY;

// ������������� ��������� ����������
typedef struct iXY {
	int x;
	int y;
} iXY;

// ���� ����� ���������
typedef struct CoordLine {
	CString value;
	double coord;
}CoordLine;

// �����, � ������� ���������� ������� ����������� ��������
class Lib_Converter {
public:
	// ����������� float � CString c 2 ������� ����� �������
	CString floatToCString_2(float &number);

	// ����������� int � CString
	CString intToCString(int& number);
};

// ����� ������ � �������������� ���������
class Lib_InteractiveBoxesData : Lib_Converter {
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
	dXY SignalCalculation(double &x);

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
	CPoint GenerateDrawablePoint(CRect& rc, dXY &calculatedPoint, int x0, int y0, bool isLog=false);

	// ��������� ����� ������� �������
	void GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// ��������� ����� ������� ���
	void GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// ��������� ����� ��������� �� �
	void GenerateXCoordLines(CRect& rc, std::vector<CoordLine>& vec);

	// ��������� ����� ��������� �� y
	void GenerateYCoordLines(CRect& rc, std::vector<CoordLine>& vec, bool isDPF);

	// ����������

	int XScale;
	int YScale;
	int LogDelta;
	int XDensity, YDensity;
	bool isLog;
};