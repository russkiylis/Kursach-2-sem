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
	str.Format(_T("%.2f"), number);  // Собственно конвертация

	return str;
}

CString Lib_Converter::intToCString(int& number)
{
	CString str;
	str.Format(_T("%d"), number);  // Собственно конвертация

	return str;
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int &delta)
{
	number -= delta;  // Изменение номера в соотвествии с размером дельты (шага изменения)

	if (number < smallest) {  // Если число меньше самого маленького доступного, то число становится самым маленьким доступным
		number = smallest;
	}
	else if (number > largest) {  // Если число больше самого большого доступного, то число становится самым большим доступным
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // Задание нового значения в editBox
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier)
{
	number -= delta*multiplier; // Изменение номера в соотвествии с размером дельты (шага изменения)

	if (number < smallest) {  // Если число меньше самого маленького доступного, то число становится самым маленьким доступным
		number = smallest;
	}
	else if (number > largest) {  // Если число больше самого большого доступного, то число становится самым большим доступным
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // Задание нового значения в editBox
}

void Lib_InteractiveBoxesData::CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox)
{
	if (number < smallest) {  // Возвращение номера в минимальное значение
		number = smallest;
	}
	else if (number > largest) {  // Возвращение номера в минимальное значение
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // Задание нового значения в editBox
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

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int x0, int y0, bool isLog)
{

	double x = x0 + calculatedPoint.x * XScale*100000;  // Перемещение х графика в центр + масштабирование
	double y;

	if (isLog) {
		y = y0-log10(calculatedPoint.y) * YScale;  // Перемещение y графика в центр + масштабирование (логарифм)
		//if (y>rc.Height()) y -= (y - rc.Height());
	}
	else {
		y = y0 - calculatedPoint.y * YScale/30;  // Перемещение y графика в центр + масштабирование
	}


	// Запись ответа
	CPoint ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// Подсчёт точек
	for (int i = 0; i < N; i++) {

		double x = double(i) /10000000;  // Целочисленное значение i делится на 10^7 так как по условию частота подсчёта графика 10 МГц
		dXY calc = SignalCalculation(x);  // Считаем точку

		CPoint point = GenerateDrawablePoint(rc, calc, 0, rc.Height() / 2);  // Берём посчитанную точку и преобразуем её в точку, которую можно отобразить в окне
		
		vec.push_back(point);  // Засовываем точку в вектор точек
	}

}

void Lib_GraphConverter::GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// Подсчёт точек
	for (int i = 0; i < N; i++) {

		dXY DPFCalc;
		double sin_sum = 0, cos_sum = 0;

		for (int g = 0; g < N; g++) {
			double x = double(g) / 10000000;  // Целочисленное значение i делится на 10^7 так как по условию частота подсчёта графика 10 МГц
			dXY calc = SignalCalculation(x);  // Считаем точку

			sin_sum += calc.y * sin((-2 * M_PI * i * g) /N);  // Подсчёт синусной составляющей Хк
			cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);  // Подсчёт косинусной составляющей Хк

		}

		DPFCalc.x = double(i)/10000000;  // Посчитанная точка х
		DPFCalc.y = sqrt(pow(cos_sum,2)+pow(sin_sum,2));  // Посчитанная точка у (корень из суммы квадратов синусной и косинусной составляющей)

		CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height()-1, isLog);  // Берём посчитанную точку и преобразуем её в точку, которую можно отобразить в окне

		vec.push_back(point);  // Засовываем точку в вектор точек
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
