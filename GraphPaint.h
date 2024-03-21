#pragma once
#include <afxwin.h>

// Класс рисования сигнала
class CGraphPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CGraphPaint)  // Объявление класса динамическим (для того чтобы впихивать переменные)
public:
    //Переменные

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

    // Объявление карты событий
    DECLARE_MESSAGE_MAP()

    // Что происходит когда надо отрисовать
    afx_msg void OnPaint();

    // Данные о прямоугольнике, в котором нужно рисовать
    CRect rc;
};


