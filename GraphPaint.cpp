#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// ����������� CGraphPaint � ������������ ����� (��� ���� ����� ������� ����������)
IMPLEMENT_DYNAMIC(CGraphPaint, CStatic)

// ���������� ������� CGraphPaint
BEGIN_MESSAGE_MAP(CGraphPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CGraphPaint::OnPaint()
{
	CPaintDC dc(this);  // Device context. ����� ��� ���������
	Lib_GraphConverter converter;  // ����� �����������
	
	// �������� � ����� converter ���������� ��� ��������� �������

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

	// �������� ������������� ������
	GetClientRect(&rc);

	CRgn rgn;  // ������, � ������� ����� ��������
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // �������� ������ �������
	dc.SelectClipRgn(&rgn);  // ����������, ��� �������� ����� ������ � ���� �������

	dc.FillSolidRect(rc, BColor);  // ���������� ����

#pragma region ��������� ���������

	CPen CoordPen(PS_DOT, 1, CColor);  // �������� ���� ���������
	HGDIOBJ CoordPenSelector = dc.SelectObject(CoordPen);  // ����� ���� ���������


	std::vector<Lib_CoordLine> xLines, yLines;  // �������������� ������������ ������� ����� ���������

	// �������� ����� ��������� �
	converter.GenerateXCoordLines(rc, xLines);
	for (int i = 1; i < xLines.size(); i++) {
		dc.MoveTo(CPoint(xLines[i].coord, 0));
		dc.LineTo(CPoint(xLines[i].coord, rc.Height()));
	}

	// �������� ����� ��������� y
	converter.GenerateYCoordLines(rc, yLines);
	for (int i = 1; i < yLines.size(); i++) {
		dc.MoveTo(CPoint(0, yLines[i].coord));
		dc.LineTo(CPoint(rc.Width(), yLines[i].coord));
	}
#pragma endregion

#pragma region ��������� �������

	CPen GraphPen(PS_SOLID, GWidth, GColor);  // �������� ���� �������
	HGDIOBJ GraphPenSelector = dc.SelectObject(GraphPen);  // ����� ���� �������

	std::vector<CPoint> points;  // �������������� ������������ ������ ����� �������

	converter.GenerateGraphPoints(rc, points);  // �������� ����� �������

	dc.MoveTo(points[0]);  // ����������� "����" � ������ �������


	if (!IsDPF) { // ���� �� ������ ���, �� ������ ������ ���� ���������. �� ������ ���� � ���� ������������ �����. ������ ������� ������ ���� �������

		// ��������� ������� �������
		for (int i = 1; i < points.size(); i++) {
			dc.LineTo(points[i]);
		}
	}
	else {

		// ��������� ������� ���
		dc.LineTo(CPoint(points[0].x, rc.Height()));
		for (int i = 1; i < points.size(); i++) {
			dc.MoveTo(points[i]);
			dc.LineTo(CPoint(points[i].x, rc.Height()));
		}
	}

#pragma endregion

#pragma region ��������� ������
	// ����� ��� � ����������
	CFont Xfont;
	Xfont.CreateFont(12, 0, 700, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	//����� ��� Y ����������
	CFont Yfont;
	Yfont.CreateFont(12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Arial"));

	dc.SetTextColor(CColor);  // ����� ����� ��� ������ (��������� � ������ ����� ���������)


	CFont* XfontSelector = dc.SelectObject(&Xfont);  // ����� ������ ��� � ��������� (����� � ��������� ������� �������)
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, rc.Height() - 10, xLines[i].value);  // �������� ������
	}

	CFont* YfontSelector = dc.SelectObject(&Yfont);  // ����� ������ ��� Y ���������
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);  // �������� ������
	}
#pragma endregion

}
