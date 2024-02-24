#include "pch.h"
#include "GraphPaint.h"
#include "Lib.h"

// ����������� CSignalPaint � ������������ ����� (��� ���� ����� ������� ����������)
IMPLEMENT_DYNAMIC(CSignalPaint, CStatic)

// ���������� ������� CSignalPaint
BEGIN_MESSAGE_MAP(CSignalPaint, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CSignalPaint::OnPaint()
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

	// �������� ������������� ������
	GetClientRect(&rc);

	CRgn rgn;  // ������, � ������� ����� ��������
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // �������� ������ �������
	dc.SelectClipRgn(&rgn);  // ����������, ��� �������� ����� ������ � ���� �������


	dc.FillSolidRect(rc, RGB(255, 255, 255));  // ���������� �����

	std::vector<CPoint> points;  // �������������� ������������ ������ �����

	converter.GenerateSignalGraphPoints(rc, points);  // �������� ����� �������

	dc.MoveTo(points[0]);  // ����������� "����" � ������ �������
	// ���������� ��������� �������
	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}

}

// ����������� CSignalPaint � ������������ ����� (��� ���� ����� ������� ����������)
IMPLEMENT_DYNAMIC(CDPFPaint, CStatic)

// ���������� ������� CDPFPaint
BEGIN_MESSAGE_MAP(CDPFPaint, CStatic)
ON_WM_PAINT()
END_MESSAGE_MAP()


void CDPFPaint::OnPaint()
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

	// �������� ������������� ������
	GetClientRect(&rc);

	CRgn rgn;  // ������, � ������� ����� ��������
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // �������� ������ �������
	dc.SelectClipRgn(&rgn);  // ����������, ��� �������� ����� ������ � ���� �������


	dc.FillSolidRect(rc, RGB(255, 255, 255));  // ���������� �����

	std::vector<CPoint> points;  // �������������� ������������ ������ �����

	converter.GenerateDPFGraphPoints(rc, points);  // �������� ����� �������

	dc.MoveTo(points[0]);  // ����������� "����" � ������ �������

	// ���������� ��������� �������
	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}

}
