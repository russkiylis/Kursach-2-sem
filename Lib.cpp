#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Radiosignal.h"
#include "RadiosignalDlg.h"

#include <initguid.h>
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

CString Lib_ValueConverter::floatToCString_2(float& number)
{
	CString str;
	str.Format(_T("%.2f"), number);  // ���������� �����������

	return str;
}

CString Lib_ValueConverter::intToCString(int& number)
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

Lib_dXY Lib_PointCalculation::SignalCalculation(double& x)
{
	//���������� ����������� ���������� y
	double y = sin(2 * M_PI * F * x + M * sin(2 * M_PI * Fm * x));

	return Lib_dXY(x,y);
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, Lib_dXY& calculatedPoint, int x0, int y0, bool isLog)
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

	return CPoint(x,y);
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{


}

void Lib_GraphConverter::GenerateGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	if (IsDPF){
		// ������� �����
		for (int i = 0; i < N; i++) {

			Lib_dXY DPFCalc;
			double sin_sum = 0, cos_sum = 0;

			for (int g = 0; g < N; g++) {
				double x = double(g) / 10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
				Lib_dXY calc = SignalCalculation(x);  // ������� �����

				sin_sum += calc.y * sin((-2 * M_PI * i * g) / N);  // ������� �������� ������������ ��
				cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);  // ������� ���������� ������������ ��

			}

			DPFCalc.x = double(i) / 10000000;  // ����������� ����� �
			DPFCalc.y = sqrt(pow(cos_sum, 2) + pow(sin_sum, 2));  // ����������� ����� � (������ �� ����� ��������� �������� � ���������� ������������)

			CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height(), isLog);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����

			vec.push_back(point);  // ���������� ����� � ������ �����
		}
	}
	else {
		// ������� �����
		for (int i = 0; i < N; i++) {

			double x = double(i) / 10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
			Lib_dXY calc = SignalCalculation(x);  // ������� �����

			CPoint point = GenerateDrawablePoint(rc, calc, 0, rc.Height() / 2);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����

			vec.push_back(point);  // ���������� ����� � ������ �����
		}
	}
}

void Lib_GraphConverter::GenerateXCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec)
{
	for (double i = 0; i < rc.Width(); i += double(XDensity)*double(XScale)/100) {

		Lib_CoordLine cl;
		cl.coord = i- double(XScale) / 100;  // ���������� ����� �� �
		cl.value.Format(_T("%.f e-7"), i / double(XScale) * 100);  // ��������� ��������
		vec.push_back(cl);  // ����������� � ������ �����
	}
}

void Lib_GraphConverter::GenerateYCoordLines(CRect& rc, std::vector<Lib_CoordLine>& vec)
{
	if (!IsDPF) {  // ���� �� ���
		for (double i = rc.Height() / 2; i < rc.Height(); i += double(YDensity) * double(YScale) / 3000) {

			Lib_CoordLine cl, mcl;
			cl.coord = i;
			cl.value.Format(_T("%.2f"), -(i - (rc.Height() / 2)) * 30 / YScale);
			vec.push_back(cl);
		}

		for (double i = rc.Height() / 2; i > 0; i -= double(YDensity) * double(YScale) / 3000) {

			Lib_CoordLine cl, mcl;
			cl.coord = i;
			cl.value.Format(_T("%.2f"), -(i - (rc.Height() / 2)) * 30 / YScale);
			if (cl.value == L"-0.00") cl.value = L"0.00";
			vec.push_back(cl);
		}
	}
	else{
		if (!isLog) {
			for (double i = rc.Height(); i > 0; i -= double(YDensity) * double(YScale) / 30) {
				Lib_CoordLine cl;
				cl.coord = i;
				cl.value.Format(_T("%.2f"), -(i - rc.Height()) / YScale*30);
				if (cl.value == L"-0.00") cl.value = L"";
				vec.push_back(cl);
			}
		}
		else {
			for (double i = rc.Height(); i > 0; i -= double(YDensity) * double(YScale)/30) {
				Lib_CoordLine cl;
				cl.coord = i;

				double k = -(i - rc.Height()) / (double)YScale;
				cl.value.Format(_T("%.2f"), pow(double(10), k));
				if (cl.value == L"-0.00") cl.value = L"";
				vec.push_back(cl);
			}
		}
	}
}
