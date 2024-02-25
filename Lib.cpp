#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"


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

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int x0, int y0)
{

	double x = x0 + calculatedPoint.x * XScale;  // Перемещение х графика в центр + масштабирование
	double y = y0 - calculatedPoint.y * YScale;  // Перемещение y графика в центр + масштабирование

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
	double sum = 0;  // Сумма значений N подсчётов графика сигнала


	// Подсчёт точек
	for (int i = 0; i < N; i++) {

		dXY DPFCalc;
		double sum = 0;
		double sin_sum = 0, cos_sum = 0;

		for (int g = 0; g < N; g++) {
			double x = double(g) / 10000000;  // Целочисленное значение i делится на 10^7 так как по условию частота подсчёта графика 10 МГц
			dXY calc = SignalCalculation(x);  // Считаем точку

			sin_sum += calc.y * sin((-2 * M_PI * i * g) /N);
			cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);

		}

		DPFCalc.x = double(i)/10000000;
		DPFCalc.y = sqrt(pow(cos_sum,2)+pow(sin_sum,2));

		CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height()-1);  // Берём посчитанную точку и преобразуем её в точку, которую можно отобразить в окне

		vec.push_back(point);  // Засовываем точку в вектор точек
	}
}
