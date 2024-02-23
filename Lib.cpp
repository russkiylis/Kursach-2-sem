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
	double y = sin(2 * M_PI * G_F * x + G_M * sin(2 * M_PI * G_Fm * x));

	// Запись ответа
	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint)
{

	int x0 = rc.Width() / 2;  // Подсчёт центра по х
	int y0 = rc.Height() / 2;  // Подсчёт центра по у

	double x = x0 + calculatedPoint.x * G_SignalGraph_XScale;  // Перемещение х графика в центр + масштабирование
	double y = y0 - calculatedPoint.y * G_SignalGraph_YScale;  // Перемещение y графика в центр + масштабирование

	// Запись ответа
	CPoint ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// Подсчёт точек. Всего точек = ширина окна/масштаб по х * 10^7
	//for (int i = -(rc.Width())/G_SignalGraph_XScale* 10000000; i <= rc.Width()/G_SignalGraph_XScale* 10000000; i++) {
	for (int i = -G_N/2; i <= G_N/2; i++) {

		double x = double(i) /10000000;  // Целочисленное значение i делится на 10^7 так как по условию частота подсчёта графика 10 МГц
		dXY calc = SignalCalculation(x);  // Считаем точку

		CPoint point = GenerateDrawablePoint(rc, calc);  // Берём посчитанную точку и преобразуем её в точку, которую можно отобразить в окне
		
		vec.push_back(point);  // Засовываем точку в вектор точек
	}

}
