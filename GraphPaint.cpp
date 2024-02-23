#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// ���������� ������� CSignalPaint
BEGIN_MESSAGE_MAP(CSignalPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CSignalPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. ����� ��� ���������
	Lib_GraphConverter converter;  // ����� �����������

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

// ���������� ������� CDPFPaint
BEGIN_MESSAGE_MAP(CDPFPaint, CStatic)
ON_WM_PAINT()
END_MESSAGE_MAP()


void CDPFPaint::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �������� ���� ��� ����������� ���������
	// �� �������� CStatic::OnPaint() ��� ��������� ���������
}
