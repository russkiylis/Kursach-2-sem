#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// Превращение CSignalPaint в динамический класс (для того чтобы втыкать переменные)
IMPLEMENT_DYNAMIC(CSignalPaint, CStatic)

// Обработчик событий CSignalPaint
BEGIN_MESSAGE_MAP(CSignalPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CSignalPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. Нужно для рисование
	Lib_GraphConverter converter;  // Класс конвертации
	
	// Передача в класс converter переменных для генерации графика

	converter.N = N;
	converter.F = F;
	converter.Fm = Fm;
	converter.M = M;
	converter.XScale = XScale;
	converter.YScale = YScale;

	// Получить прямоугольник окошка
	GetClientRect(&rc);

	CRgn rgn;  // Регион, в котором можно рисовать
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // Создание границ региона
	dc.SelectClipRgn(&rgn);  // Указывание, что рисовать можно только в этом регионе


	dc.FillSolidRect(rc, RGB(255, 255, 255));  // Заполнение белым

	CPen Pen(PS_SOLID, 2, RGB(250, 120, 60));  // Создание пера
	HGDIOBJ old = dc.SelectObject(Pen);  // Выбор пера

	std::vector<CPoint> points;  // Автоматический динамический массив точек

	converter.GenerateSignalGraphPoints(rc, points);  // Создание точек графика

	dc.MoveTo(points[0]);  // Перемещение "пера" в начало графика
	// Собственно рисование графика
	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}

}

// Превращение CSignalPaint в динамический класс (для того чтобы втыкать переменные)
IMPLEMENT_DYNAMIC(CDPFPaint, CStatic)

// Обработчик событий CDPFPaint
BEGIN_MESSAGE_MAP(CDPFPaint, CStatic)
ON_WM_PAINT()
END_MESSAGE_MAP()


void CDPFPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. Нужно для рисование
	Lib_GraphConverter converter;  // Класс конвертации

	// Передача в класс converter переменных для генерации графика

	converter.N = N;
	converter.F = F;
	converter.Fm = Fm;
	converter.M = M;
	converter.XScale = XScale;
	converter.YScale = YScale;
	converter.isLog = IsLog;

	// Получить прямоугольник окошка
	GetClientRect(&rc);

	CRgn rgn;  // Регион, в котором можно рисовать
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // Создание границ региона
	dc.SelectClipRgn(&rgn);  // Указывание, что рисовать можно только в этом регионе


	dc.FillSolidRect(rc, RGB(255, 255, 255));  // Заполнение белым

	CPen Pen(PS_SOLID, 2, RGB(250, 120, 60));  // Создание пера
	HGDIOBJ old = dc.SelectObject(Pen);  // Выбор пера

	std::vector<CPoint> points;  // Автоматический динамический массив точек

	converter.GenerateDPFGraphPoints(rc, points);  // Создание точек графика

	dc.MoveTo(points[0]);  // Перемещение "пера" в начало графика

	// Собственно рисование графика
	dc.LineTo(CPoint(points[0].x, rc.Height()));

	// Собственно рисование графика
	for (int i = 1; i < points.size(); i++) {
		dc.MoveTo(points[i]);
		dc.LineTo(CPoint(points[i].x, rc.Height()));
	}

}
