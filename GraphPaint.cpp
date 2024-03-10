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
	converter.XDensity = CXDensity;
	converter.YDensity = CYDensity;

	// �������� ������������� ������
	GetClientRect(&rc);

	CRgn rgn;  // ������, � ������� ����� ��������
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // �������� ������ �������
	dc.SelectClipRgn(&rgn);  // ����������, ��� �������� ����� ������ � ���� �������



	dc.FillSolidRect(rc, BColor);  // ���������� ����

#pragma region ��������� ���������
	CPen CoordPen(PS_DOT, 1, CColor);  // �������� ���� ���������
	HGDIOBJ old1 = dc.SelectObject(CoordPen);  // ����� ���� ���������


	std::vector<CoordLine> xLines, yLines;  // �������������� ������������ ������ ����� ���������
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

#pragma region ��������� �������
	CPen GraphPen(PS_SOLID, GWidth, GColor);  // �������� ���� �������
	HGDIOBJ old = dc.SelectObject(GraphPen);  // ����� ���� �������

	std::vector<CPoint> points;  // �������������� ������������ ������ ����� �������

	converter.GenerateSignalGraphPoints(rc, points);  // �������� ����� �������

	dc.MoveTo(points[0]);  // ����������� "����" � ������ �������
	// ���������� ��������� �������
	for (int i = 1; i < points.size(); i++) {
		dc.LineTo(points[i]);
	}
#pragma endregion

#pragma region ��������� ������
	// ����� ��� � ����������
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

	//����� ��� Y ����������
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
	CFont* def_font1 = dc.SelectObject(&Xfont);  // ����� ������
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, rc.Height() - 10, xLines[i].value);
	}

	CFont* def_font = dc.SelectObject(&Yfont);  // ����� ������
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);
	}
#pragma endregion
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
	converter.isLog = IsLog;
	converter.XDensity = CXDensity;
	converter.YDensity = CYDensity;

	// �������� ������������� ������
	GetClientRect(&rc);

	CRgn rgn;  // ������, � ������� ����� ��������
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);  // �������� ������ �������
	dc.SelectClipRgn(&rgn);  // ����������, ��� �������� ����� ������ � ���� �������



	dc.FillSolidRect(rc, BColor);  // ���������� ����



#pragma region ��������� ���������
	CPen CoordPen(PS_DOT, 1, CColor);  // �������� ���� ���������
	HGDIOBJ old1 = dc.SelectObject(CoordPen);  // ����� ���� ���������


	std::vector<CoordLine> xLines, yLines;  // �������������� ������������ ������ ����� ���������
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

#pragma region ��������� �������
	CPen GraphPen(PS_SOLID, GWidth, GColor);  // �������� ���� �������
	HGDIOBJ old = dc.SelectObject(GraphPen);  // ����� ���� �������

	std::vector<CPoint> points;  // �������������� ������������ ������ �����

	converter.GenerateDPFGraphPoints(rc, points);  // �������� ����� �������

	dc.MoveTo(points[0]);  // ����������� "����" � ������ �������

	// ���������� ��������� �������
	dc.LineTo(CPoint(points[0].x, rc.Height()));

	// ���������� ��������� �������
	for (int i = 1; i < points.size(); i++) {
			dc.MoveTo(points[i]);
			dc.LineTo(CPoint(points[i].x, rc.Height()));
	}
#pragma endregion

#pragma region ��������� ������
	// ����� ��� � ����������
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

	//����� ��� Y ����������
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
	CFont* def_font1 = dc.SelectObject(&Xfont);  // ����� ������
	for (int i = 1; i < xLines.size(); i++) {
		dc.TextOut(xLines[i].coord - 10, 40, xLines[i].value);
	}

	CFont* def_font = dc.SelectObject(&Yfont);  // ����� ������
	for (int i = 1; i < yLines.size()-1; i++) {
		dc.TextOut(5, yLines[i].coord - 5, yLines[i].value);
	}
#pragma endregion
}
