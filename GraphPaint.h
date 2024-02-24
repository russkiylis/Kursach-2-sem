#pragma once
#include <afxwin.h>

// Класс рисования сигнала
class CSignalPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CSignalPaint)  // Объявление класса динамическим (для того чтобы впихивать переменные)
public:
    //Переменные

    int N;
    int G;
    int F;
    int Fm;
    int M;
    int XScale;
    int YScale;

    // Объявление карты событий
    DECLARE_MESSAGE_MAP()

    // Что происходит когда надо отрисовать
    afx_msg void OnPaint();

    // Данные о прямоугольнике, в котором нужно рисовать
    CRect rc;
};



// Класс рисования ДПФ
class CDPFPaint :
    public CStatic
{
    DECLARE_DYNAMIC(CDPFPaint)  // Объявление класса динамическим (для того чобы впихивать переменные)
public:
    //Переменные

    int N;
    int G;
    int F;
    int Fm;
    int M;
    int XScale;
    int YScale;
    bool IsLog;

    // Объявление карты событий
    DECLARE_MESSAGE_MAP()

    // Что происходит когда надо отрисовать
    afx_msg void OnPaint();

    // Данные о прямоугольнике, в котором нужно рисовать
    CRect rc;
};

