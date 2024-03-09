#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"

#include <initguid.h>
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

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

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int x0, int y0, bool isLog)
{

	double x = x0 + calculatedPoint.x * XScale*100000;  // ����������� � ������� � ����� + ���������������
	double y;

	if (isLog) {
		y = y0-log10(calculatedPoint.y) * YScale;  // ����������� y ������� � ����� + ��������������� (��������)
		//if (y>rc.Height()) y -= (y - rc.Height());
	}
	else {
		y = y0 - calculatedPoint.y * YScale/30;  // ����������� y ������� � ����� + ���������������
	}


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
	// ������� �����
	for (int i = 0; i < N; i++) {

		dXY DPFCalc;
		double sin_sum = 0, cos_sum = 0;

		for (int g = 0; g < N; g++) {
			double x = double(g) / 10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
			dXY calc = SignalCalculation(x);  // ������� �����

			sin_sum += calc.y * sin((-2 * M_PI * i * g) /N);  // ������� �������� ������������ ��
			cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);  // ������� ���������� ������������ ��

		}

		DPFCalc.x = double(i)/10000000;  // ����������� ����� �
		DPFCalc.y = sqrt(pow(cos_sum,2)+pow(sin_sum,2));  // ����������� ����� � (������ �� ����� ��������� �������� � ���������� ������������)

		CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height()-1, isLog);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����

		vec.push_back(point);  // ���������� ����� � ������ �����
	}

	if (isLog) {
		int max=0;
		LogDelta = 0;

		for (int i = 0; i < N; i++) {
			if (vec[i].y > max) max = vec[i].y;
		}


		if (max > rc.Height()) {
			LogDelta = max - rc.Height();
		}

		for (int i = 0; i < N; i++) {
			vec[i].y -= LogDelta;
		}
	}
}

void Lib_GraphConverter::GenerateXCoordLines(CRect& rc, std::vector<CoordLine>& vec)
{
	for (double i = 0; i < rc.Width(); i += double(XDensity)*double(XScale)/100) {

		CoordLine cl;
		cl.coord = i- double(XScale) / 100;
		double a = i / double(XScale);
		cl.value.Format(_T("%.f e-7"), i / double(XScale) * 100);
		vec.push_back(cl);
	}
}
