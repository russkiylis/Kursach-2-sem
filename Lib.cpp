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
	double y = sin(2 * M_PI * F * x + M * sin(2 * M_PI * Fm * x));

	// Запись ответа
	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int xScale, int yScale)
{
	dXY ShiftedGraph;
	ShiftedGraph = GraphShift(rc, calculatedPoint, xScale, yScale);

	CPoint ans;
	ans.y = ShiftedGraph.y * yScale;
	ans.x = ShiftedGraph.x * xScale;
	return CPoint();
}

dXY Lib_GraphConverter::GraphShift(CRect& rc, dXY& calculatedPoint, int xScale, int yScale)
{
	int x0 = rc.Width() / 2;
	int y0 = rc.Height() / 2;

	double x = x0 + calculatedPoint.x * xScale;
	double y = y0 - calculatedPoint.y * yScale;

	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec, int xScale, int yScale)
{
	for (int i = 1; i <= rc.Width(); i++) {

		double x = i / xScale;
		dXY calc = SignalCalculation(x);

		CPoint point = GenerateDrawablePoint(rc, calc, xScale, yScale);
		
		vec.push_back(point);
	}
}
