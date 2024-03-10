#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// Превращение CGraphPaint в динамический класс (для того чтобы втыкать переменные)
IMPLEMENT_DYNAMIC(CGraphPaint, CStatic)

// Обработчик событий CGraphPaint
BEGIN_MESSAGE_MAP(CGraphPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CGraphPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. Нужно для рисования
	Lib_GraphConverter converter;  // Класс конвертации
	
	// Передача в класс converter переменных для генерации графика

	converter.N = N;
	converter.F = F;
	converter.Fm = Fm;
	converter.M = M;
	converter.XScale = XScale;
	converter.YScale = YScale;
	converter.XDensity = CXDensity;
	converter.YDensity = CYDensity;
	converter.isLog = IsLog;
	converter.IsDPF = IsDPF;

	// Получить прямоугольник окошка
	GetClientRect(&rc);

	CRgn rgn;  // Регион, в котором можно рисовать
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // Создание границ региона
	dc.SelectClipRgn(&rgn);  // Указывание, что рисовать можно только в этом регионе

	dc.FillSolidRect(rc, BColor);  // Заполнение фона

#pragma region Рисование координат

	CPen CoordPen(PS_DOT, 1, CColor);  // Создание пера координат
	HGDIOBJ CoordPenSelector = dc.SelectObject(CoordPen);  // Выбор пера координат


	std::vector<Lib_CoordLine> xLines, yLines;  // Автоматические динамические массивы линий координат

	// Создание линий координат х
	converter.GenerateXCoordLines(rc, xLines);
	for (int i = 1; i < xLines.size(); i++) {
		dc.MoveTo(CPoint(xLines[i].coord, 0));
		dc.LineTo(CPoint(xLines[i].coord, rc.Height()));
	}

	// Создание линий координат y
	converter.GenerateYCoordLines(rc, yLines);
	for (int i = 1; i < yLines.size(); i++) {
		dc.MoveTo(CPoint(0, yLines[i].coord));
		dc.LineTo(CPoint(rc.Width(), yLines[i].coord));
	}
#pragma endregion

#pragma region Рисование графика

	CPen GraphPen(PS_SOLID, GWidth, GColor);  // Создание пера графика
	HGDIOBJ GraphPenSelector = dc.SelectObject(GraphPen);  // Выбор пера графика

	std::vector<CPoint> points;  // Автоматический динамический массив точек графика

	converter.GenerateGraphPoints(rc, points);  // Создание точек графика

	dc.MoveTo(points[0]);  // Перемещение "пера" в начало графика


	if (!IsDPF) { // Если мы рисуем ДПФ, то график должен быть необычным. Он должен быть в виде вертикальных линий. График сигнала должен быть обычным

		// Рисование графика сигнала
		for (int i = 1; i < points.size(); i++) {
			dc.LineTo(points[i]);
		}
	}
	else {

		// Рисование графика ДПФ
		dc.LineTo(CPoint(points[0].x, rc.Height()));
		for (int i = 1; i < points.size(); i++) {
			dc.MoveTo(points[i]);
			dc.LineTo(CPoint(points[i].x, rc.Height()));
		}
	}

#pragma endregion

#pragma region Рисование текста
	// Шрифт для Х координаты
	CFont Xfont;
	Xfont.CreateFont(12, 0, 700, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	//Шрифт для Y координаты
	CFont Yfont;
	Yfont.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	dc.SetTextColor(CColor);  // Выбор цвета для шрифта (совпадает с цветом линий координат)


	CFont* XfontSelector = dc.SelectObject(&Xfont);  // Выбор шрифта для Х координат (шрифт Х координат немного повёрнут)
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, rc.Height() - 10, xLines[i].value);  // Создание текста
	}

	CFont* YfontSelector = dc.SelectObject(&Yfont);  // Выбор шрифта для Y координат
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);  // Создание текста
	}
#pragma endregion

}
