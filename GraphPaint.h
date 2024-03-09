#pragma once
#include <afxwin.h>

// ����� ��������� �������
class CSignalPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CSignalPaint)  // ���������� ������ ������������ (��� ���� ����� ��������� ����������)
public:
    //����������

    int N;
    int G;
    int F;
    int Fm;
    int M;
    int XScale;
    int YScale;

    COLORREF GColor, CColor, BColor;
    int GWidth;
    int CDensity;

    // ���������� ����� �������
    DECLARE_MESSAGE_MAP()

    // ��� ���������� ����� ���� ����������
    afx_msg void OnPaint();

    // ������ � ��������������, � ������� ����� ��������
    CRect rc;
};



// ����� ��������� ���
class CDPFPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CDPFPaint)  // ���������� ������ ������������ (��� ���� ���� ��������� ����������)
public:
    //����������

    int N;
    int G;
    int F;
    int Fm;
    int M;
    int XScale;
    int YScale;
    bool IsLog;

    COLORREF GColor, CColor, BColor;
    int GWidth;
    int CDensity;

    // ���������� ����� �������
    DECLARE_MESSAGE_MAP()

    // ��� ���������� ����� ���� ����������
    afx_msg void OnPaint();

    // ������ � ��������������, � ������� ����� ��������
    CRect rc;
};

