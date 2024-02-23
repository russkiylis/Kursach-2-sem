#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// Обработчик событий CSignalPaint
BEGIN_MESSAGE_MAP(CSignalPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CSignalPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. Нужно для рисование
	Lib_GraphConverter converter;  // Класс конвертации

	GetClientRect(&rc);

	CRgn rgn;
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	dc.SelectClipRgn(&rgn);

	dc.FillSolidRect(rc, RGB(255, 255, 255));

	std::vector<CPoint> points;

	converter.GenerateSignalGraphPoints(rc, points);

	dc.MoveTo(points[0]);

	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}

}

// Обработчик событий CDPFPaint
BEGIN_MESSAGE_MAP(CDPFPaint, CStatic)
ON_WM_PAINT()
END_MESSAGE_MAP()


void CDPFPaint::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: добавьте свой код обработчика сообщений
	// Не вызывать CStatic::OnPaint() для сообщений рисования
}
