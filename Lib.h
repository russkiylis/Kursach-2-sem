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

class Lib_PointCalculation {
public:
	// ������� ����������������� ��� ������ ����� ������� �������
	dXY SignalCalculation(double &x);

	// ������� ������� ���
	dXY DPFCalculation(double& N);
};

class Lib_GraphConverter : Lib_PointCalculation {
public:
	// ��������� ����� ��� ��������� ������� (������ ��������� �� ������)
	CPoint GenerateDrawablePoint(CRect& rc, dXY &calculatedPoint);

	// ��������� ����� ������� �������
	void GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec);

	// ��������� ����� ������� ���
	void GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec);
};