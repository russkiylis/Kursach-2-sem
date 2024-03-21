#pragma once
#include <afxwin.h>

// ����� ��������� �������
class CGraphPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CGraphPaint)  // ���������� ������ ������������ (��� ���� ����� ��������� ����������)
public:
    //����������

    int N;
    int G;
    double F;
    double Fm;
    double M;
    int XScale;
    int YScale;
    bool IsLog;
    bool IsDPF;

    COLORREF GColor, CColor, BColor;
    int GWidth;
    int CXDensity, CYDensity;

    // ���������� ����� �������
    DECLARE_MESSAGE_MAP()

    // ��� ���������� ����� ���� ����������
    afx_msg void OnPaint();

    // ������ � ��������������, � ������� ����� ��������
    CRect rc;
};


