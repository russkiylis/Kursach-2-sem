#pragma once
#include <afxwin.h>

class CSignalPaint :
    public CStatic
{
public:
    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    CRect rc;
};

