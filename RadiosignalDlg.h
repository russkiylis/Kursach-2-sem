// KursachDlg.h: файл заголовка
//

#pragma once
#include "GraphPaint.h"

// Диалоговое окно CRadiosignalDlg
class CRadiosignalDlg : public CDialogEx
{
// Создание
public:
	CRadiosignalDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KURSACH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	// Переменная стрелочек задания N
	CSpinButtonCtrl N_Spin;
	// Переменная N (Количество отсчётов сигнала)
	int N = 100;
	// Переменная окошка выбора N
	CEdit N_Edit;

	afx_msg void OnBnClickedOk();
	afx_msg void OnDeltaposNSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	// Переменная стрелочек задания F
	CSpinButtonCtrl F_Spin;
	// Переменная окошка выбора F
	CEdit F_Edit;
	// Переменная F (Несущая частота сигнала)
	int F;

	afx_msg void OnEnKillfocusNEdit();
	afx_msg void OnEnKillfocusFEdit();
	afx_msg void OnDeltaposFSpin(NMHDR* pNMHDR, LRESULT* pResult);

	// Переменная окошка выбора Fm
	CEdit Fm_Edit;
	// Переменная Fm (Частота модуляции)
	int Fm;
	// Переменная стрелочек задания Fm
	CSpinButtonCtrl Fm_Spin;

	afx_msg void OnEnKillfocusFmEdit();
	afx_msg void OnDeltaposFmSpin(NMHDR* pNMHDR, LRESULT* pResult);

	// Переменная окошка выбора M
	CEdit M_Edit;
	// Переменная M (Глубина модуляции)
	int M;
	// Переменная стрелочек задания M
	CSpinButtonCtrl M_Spin;

	afx_msg void OnEnKillfocusMEdit();
	afx_msg void OnDeltaposMSpin(NMHDR* pNMHDR, LRESULT* pResult);

	// Масштаб по Y графика сигнала
	int SignalGraph_YScale;
	afx_msg void OnNMCustomdrawSignalgraphYcontrol(NMHDR* pNMHDR, LRESULT* pResult);

	// Переменная управления ползунком масшаба OY графика сигнала
	CSliderCtrl SignalGraph_YControl;
	// Переменная ползунка масштаба OX графика сигнала
	CSliderCtrl SignalGraph_XControl;

	// Переменная масштаба графика сигнала по X
	int SignalGraph_XScale;
	afx_msg void OnNMCustomdrawSignalgraphXcontrol(NMHDR* pNMHDR, LRESULT* pResult);

	// Переменная рисования графика сигнала
	CGraphPaint Signal;
	// Переменная управления ползунка Y графика ДПФ
	CSliderCtrl DPFGraph_YControl;
	// Переменная масштаба графика ДПФ по Y
	int DPFGraph_YScale;
	// Переменная управления ползунка Х графика ДПФ
	CSliderCtrl DPFGraph_XControl;
	// Переменная масштаба Х графика ДПФ
	int DPFGraph_XScale;
	// Управление галочкой логарифмирования Y графика ДПФ
	CButton DPFGraph_LogControl;
	// Переменная логарифмирования Y графика ДПФ
	BOOL DPFGraph_IsLog;
	afx_msg void OnNMCustomdrawDpfgraphYcontrol2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawDpfgraphXcontrol2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedDpfgraphLogbutton();
	// Переменная рисования ДПФ
	CGraphPaint DPF;
	afx_msg void OnBnClickedSignalgraphBmpbutton();
	afx_msg void OnBnClickedDpfgraphBmpbutton();
	CMFCColorButton SGColorControl;
	CMFCColorButton SCColorControl;
	CMFCColorButton SBColorControl;
	CMFCColorButton DGColorControl;
	CMFCColorButton DCColorControl;
	CMFCColorButton DBColorControl;
	COLORREF SGColor;
	COLORREF SCColor;
	COLORREF SBColor;
	COLORREF DGColor;
	COLORREF DCColor;
	COLORREF DBColor;
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedMfccolorbutton2();
	afx_msg void OnBnClickedMfccolorbutton3();
	afx_msg void OnBnClickedMfccolorbutton4();
	afx_msg void OnBnClickedMfccolorbutton5();
	afx_msg void OnBnClickedMfccolorbutton6();
	CSliderCtrl SWidthControl;
	CSliderCtrl SXDensityControl;
	CSliderCtrl DWidthControl;
	CSliderCtrl DXDensityControl;
	int SWidth;
	int SXDensity;
	int DWidth;
	int DXDensity;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl SYDensityControl;
	int SYDensity;
	CSliderCtrl DYDensityControl;
	int DYDensity;
	afx_msg void OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	// Сохранение в реестр Windows
	void RegistrySave();
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnClose();
};