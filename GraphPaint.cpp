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
	converter.XDensity = CXDensity;
	converter.YDensity = CYDensity;

	// Получить прямоугольник окошка
	GetClientRect(&rc);

	CRgn rgn;  // Регион, в котором можно рисовать
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // Создание границ региона
	dc.SelectClipRgn(&rgn);  // Указывание, что рисовать можно только в этом регионе



	dc.FillSolidRect(rc, BColor);  // Заполнение фона

#pragma region Рисование координат
	CPen CoordPen(PS_DOT, 1, CColor);  // Создание пера координат
	HGDIOBJ old1 = dc.SelectObject(CoordPen);  // Выбор пера координат


	std::vector<CoordLine> xLines, yLines;  // Автоматический динамический массив линий координат
	converter.GenerateXCoordLines(rc, xLines);

	for (int i = 1; i < xLines.size(); i++) {
		dc.MoveTo(CPoint(xLines[i].coord, 0));
		dc.LineTo(CPoint(xLines[i].coord, rc.Height()));
	}

	converter.GenerateYCoordLines(rc, yLines, false);
	for (int i = 1; i < yLines.size(); i++) {
		dc.MoveTo(CPoint(0, yLines[i].coord));
		dc.LineTo(CPoint(rc.Width(), yLines[i].coord));
	}
#pragma endregion

#pragma region Рисование графика
	CPen GraphPen(PS_SOLID, GWidth, GColor);  // Создание пера графика
	HGDIOBJ old = dc.SelectObject(GraphPen);  // Выбор пера графика

	std::vector<CPoint> points;  // Автоматический динамический массив точек графика

	converter.GenerateSignalGraphPoints(rc, points);  // Создание точек графика

	dc.MoveTo(points[0]);  // Перемещение "пера" в начало графика
	// Собственно рисование графика
	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}
#pragma endregion

#pragma region Рисование текста
	// Шрифт для Х координаты
	CFont Xfont;
	Xfont.CreateFont(
		12,  //nHeight
		0,  //nWidth
		700,  //nEscapement
		0,  //nOrientation
		FW_NORMAL,  //nWeight
		FALSE,  //bItalic
		FALSE,  //bUnderline
		0,  //cStrikeOut
		ANSI_CHARSET,  //nCharSet
		OUT_DEFAULT_PRECIS,  //nOutPrecision
		CLIP_DEFAULT_PRECIS,  //nClipPrecision
		DEFAULT_QUALITY,  //nQuality
		DEFAULT_PITCH | FF_SWISS,  //nPitchAndFamily
		_T("Arial")  //lpszFacename
	);

	//Шрифт для Y координаты
	CFont Yfont;
	Yfont.CreateFont(
		12,  //nHeight
		0,  //nWidth
		0,  //nEscapement
		0,  //nOrientation
		FW_NORMAL,  //nWeight
		FALSE,  //bItalic
		FALSE,  //bUnderline
		0,  //cStrikeOut
		ANSI_CHARSET,  //nCharSet
		OUT_DEFAULT_PRECIS,  //nOutPrecision
		CLIP_DEFAULT_PRECIS,  //nClipPrecision
		DEFAULT_QUALITY,  //nQuality
		DEFAULT_PITCH | FF_SWISS,  //nPitchAndFamily
		_T("Arial")  //lpszFacename
	);
	dc.SetTextColor(CColor);
	CFont* def_font1 = dc.SelectObject(&Xfont);  // Выбор шрифта
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, rc.Height() - 10, xLines[i].value);
	}

	CFont* def_font = dc.SelectObject(&Yfont);  // Выбор шрифта
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);
	}
#pragma endregion
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
	converter.XDensity = CXDensity;
	converter.YDensity = CYDensity;

	// Получить прямоугольник окошка
	GetClientRect(&rc);

	CRgn rgn;  // Регион, в котором можно рисовать
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // Создание границ региона
	dc.SelectClipRgn(&rgn);  // Указывание, что рисовать можно только в этом регионе



	dc.FillSolidRect(rc, BColor);  // Заполнение фона



#pragma region Рисование координат
	CPen CoordPen(PS_DOT, 1, CColor);  // Создание пера координат
	HGDIOBJ old1 = dc.SelectObject(CoordPen);  // Выбор пера координат


	std::vector<CoordLine> xLines, yLines;  // Автоматический динамический массив линий координат
	converter.GenerateXCoordLines(rc, xLines);

	for (int i = 1; i < xLines.size(); i++) {
		dc.MoveTo(CPoint(xLines[i].coord, 0));
		dc.LineTo(CPoint(xLines[i].coord, rc.Height()));
	}

	converter.GenerateYCoordLines(rc, yLines, true);
	for (int i = 1; i < yLines.size(); i++) {
		dc.MoveTo(CPoint(0, yLines[i].coord));
		dc.LineTo(CPoint(rc.Width(), yLines[i].coord));
	}
#pragma endregion

#pragma region Рисование графика
	CPen GraphPen(PS_SOLID, GWidth, GColor);  // Создание пера графика
	HGDIOBJ old = dc.SelectObject(GraphPen);  // Выбор пера графика

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
#pragma endregion

#pragma region Рисование текста
	// Шрифт для Х координаты
	CFont Xfont;
	Xfont.CreateFont(
		12,  //nHeight
		0,  //nWidth
		700,  //nEscapement
		0,  //nOrientation
		FW_NORMAL,  //nWeight
		FALSE,  //bItalic
		FALSE,  //bUnderline
		0,  //cStrikeOut
		ANSI_CHARSET,  //nCharSet
		OUT_DEFAULT_PRECIS,  //nOutPrecision
		CLIP_DEFAULT_PRECIS,  //nClipPrecision
		DEFAULT_QUALITY,  //nQuality
		DEFAULT_PITCH | FF_SWISS,  //nPitchAndFamily
		_T("Arial")  //lpszFacename
	);

	//Шрифт для Y координаты
	CFont Yfont;
	Yfont.CreateFont(
		12,  //nHeight
		0,  //nWidth
		0,  //nEscapement
		0,  //nOrientation
		FW_NORMAL,  //nWeight
		FALSE,  //bItalic
		FALSE,  //bUnderline
		0,  //cStrikeOut
		ANSI_CHARSET,  //nCharSet
		OUT_DEFAULT_PRECIS,  //nOutPrecision
		CLIP_DEFAULT_PRECIS,  //nClipPrecision
		DEFAULT_QUALITY,  //nQuality
		DEFAULT_PITCH | FF_SWISS,  //nPitchAndFamily
		_T("Arial")  //lpszFacename
	);
	dc.SetTextColor(CColor);
	CFont* def_font1 = dc.SelectObject(&Xfont);  // Выбор шрифта
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, 40, xLines[i].value);
	}

	CFont* def_font = dc.SelectObject(&Yfont);  // Выбор шрифта
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);
	}
#pragma endregion
}
