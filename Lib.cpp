#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"


CString Lib_Converter::floatToCString_2(float& number)
{
	CString str;
	str.Format(_T("%.2f"), number);  // ���������� �����������

	return str;
}

CString Lib_Converter::intToCString(int& number)
{
	CString str;
	str.Format(_T("%d"), number);  // ���������� �����������

	return str;
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int &delta)
{
	number -= delta;  // ��������� ������ � ����������� � �������� ������ (���� ���������)

	if (number < smallest) {  // ���� ����� ������ ������ ���������� ����������, �� ����� ���������� ����� ��������� ���������
		number = smallest;
	}
	else if (number > largest) {  // ���� ����� ������ ������ �������� ����������, �� ����� ���������� ����� ������� ���������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier)
{
	number -= delta*multiplier; // ��������� ������ � ����������� � �������� ������ (���� ���������)

	if (number < smallest) {  // ���� ����� ������ ������ ���������� ����������, �� ����� ���������� ����� ��������� ���������
		number = smallest;
	}
	else if (number > largest) {  // ���� ����� ������ ������ �������� ����������, �� ����� ���������� ����� ������� ���������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

void Lib_InteractiveBoxesData::CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox)
{
	if (number < smallest) {  // ����������� ������ � ����������� ��������
		number = smallest;
	}
	else if (number > largest) {  // ����������� ������ � ����������� ��������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

dXY Lib_PointCalculation::SignalCalculation(double& x)
{
	//���������� ����������� ���������� y
	double y = sin(2 * M_PI * F * x + M * sin(2 * M_PI * Fm * x));

	// ������ ������
	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int x0, int y0)
{

	double x = x0 + calculatedPoint.x * XScale;  // ����������� � ������� � ����� + ���������������
	double y = y0 - calculatedPoint.y * YScale;  // ����������� y ������� � ����� + ���������������

	// ������ ������
	CPoint ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// ������� �����
	for (int i = 0; i < N; i++) {

		double x = double(i) /10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
		dXY calc = SignalCalculation(x);  // ������� �����

		CPoint point = GenerateDrawablePoint(rc, calc, 0, rc.Height() / 2);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����
		
		vec.push_back(point);  // ���������� ����� � ������ �����
	}

}

void Lib_GraphConverter::GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	double sum = 0;  // ����� �������� N ��������� ������� �������


	// ������� �����
	for (int i = 0; i < N; i++) {

		dXY DPFCalc;
		double sum = 0;
		double sin_sum = 0, cos_sum = 0;

		for (int g = 0; g < N; g++) {
			double x = double(g) / 10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
			dXY calc = SignalCalculation(x);  // ������� �����

			sin_sum += calc.y * sin((-2 * M_PI * i * g) /N);
			cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);

		}

		DPFCalc.x = double(i)/10000000;
		DPFCalc.y = sqrt(pow(cos_sum,2)+pow(sin_sum,2));

		CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height()-1);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����

		vec.push_back(point);  // ���������� ����� � ������ �����
	}
}
