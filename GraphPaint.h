#pragma once
#include <afxwin.h>

// Класс рисования сигнала
class CSignalPaint :
    public CStatic
{
public:
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
public:
    DECLARE_MESSAGE_MAP()

    // Что происходит когда надо отрисовать
    afx_msg void OnPaint();

    // Данные о прямоугольнике, в котором нужно рисовать
    CRect rc;
};

