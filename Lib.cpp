#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"


CString Lib_Converter::floatToCString_2(float& number)
{
	CString str;
	str.Format(_T("%.2f"), number);

	return str;
}

CString Lib_Converter::intToCString(int& number)
{
	CString str;
	str.Format(_T("%d"), number);

	return str;
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int &delta)
{
	number -= delta;

	if (number < smallest) {
		number = smallest;
	}
	else if (number > largest) {
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier)
{
	number -= delta*multiplier;

	if (number < smallest) {
		number = smallest;
	}
	else if (number > largest) {
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));
}

void Lib_InteractiveBoxesData::CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox)
{
	if (number < smallest) {
		number = smallest;
	}
	else if (number > largest) {
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));
}

dXY Lib_PointCalculation::SignalCalculation(double& x)
{
	//Собственно посчитанная координата y
	double y = sin(2 * M_PI * G_F * x + G_M * sin(2 * M_PI * G_Fm * x));
	//double y = cos(x*G_SignalGraph_XScale) * sin(x*G_SignalGraph_XScale);

	// Запись ответа
	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint)
{

	dXY ShiftedGraph;
	ShiftedGraph = GraphShift(rc, calculatedPoint);

	CPoint ans;
	ans.y = ShiftedGraph.y;
	ans.x = ShiftedGraph.x;
	return ans;
}

dXY Lib_GraphConverter::GraphShift(CRect& rc, dXY& calculatedPoint)
{
	int x0 = rc.Width() / 2;
	int y0 = rc.Height() / 2;

	double x = x0 + calculatedPoint.x*G_SignalGraph_XScale;
	double y = y0 - calculatedPoint.y*G_SignalGraph_YScale;

	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	for (int i = -(rc.Width()); i <= rc.Width(); i++) {

		double x = double(i) /10000000;
		dXY calc = SignalCalculation(x);

		CPoint point = GenerateDrawablePoint(rc, calc);
		
		vec.push_back(point);
	}
	TRACE("%d \n", vec.size());
}
