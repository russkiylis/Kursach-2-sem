
// KursachDlg.cpp: файл реализации
//

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно CAboutDlg используется для описания сведений о приложении
#pragma region CAboutDlg
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
#pragma endregion


// Диалоговое окно CKursachDlg
CKursachDlg::CKursachDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KURSACH_DIALOG, pParent)
	, N(500)
	, F(2000000)
	, Fm(400000)
	, M(5)
	, SignalGraph_YScale(50000)
	, SignalGraph_XScale(5)
	, DPFGraph_YScale(0)
	, DPFGraph_XScale(0)
	, DPFGraph_IsLog(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// Связь переменных с интерфейсом
void CKursachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_N_SPIN, N_Spin);
	DDX_Text(pDX, ID_N_EDIT, N);
	DDV_MinMaxInt(pDX, N, 100, 1000);
	DDX_Control(pDX, ID_N_EDIT, N_Edit);
	DDX_Control(pDX, ID_F_SPIN, F_Spin);
	DDX_Control(pDX, ID_F_EDIT, F_Edit);
	DDX_Text(pDX, ID_F_EDIT, F);
	DDV_MinMaxInt(pDX, F, 1000000, 4000000);
	DDX_Control(pDX, ID_Fm_EDIT, Fm_Edit);
	DDX_Text(pDX, ID_Fm_EDIT, Fm);
	DDV_MinMaxInt(pDX, Fm, 100000, 900000);
	DDX_Control(pDX, ID_Fm_SPIN, Fm_Spin);
	DDX_Control(pDX, ID_M_EDIT, M_Edit);
	DDX_Text(pDX, ID_M_EDIT, M);
	DDV_MinMaxInt(pDX, M, 0, 10);
	DDX_Control(pDX, ID_M_SPIN, M_Spin);
	DDX_Slider(pDX, ID_SIGNALGRAPH_YCONTROL, SignalGraph_YScale);
	DDX_Control(pDX, ID_SIGNALGRAPH_YCONTROL, SignalGraph_YControl);
	DDX_Control(pDX, ID_SIGNALGRAPH_XCONTROL, SignalGraph_XControl);
	DDX_Slider(pDX, ID_SIGNALGRAPH_XCONTROL, SignalGraph_XScale);
	DDX_Control(pDX, ID_DPFGRAPH_YCONTROL2, DPFGraph_YControl);
	DDX_Slider(pDX, ID_DPFGRAPH_YCONTROL2, DPFGraph_YScale);
	DDX_Control(pDX, ID_DPFGRAPH_XCONTROL2, DPFGraph_XControl);
	DDX_Slider(pDX, ID_DPFGRAPH_XCONTROL2, DPFGraph_XScale);
	DDX_Control(pDX, ID_DPFGRAPH_LOGBUTTON, DPFGraph_LogControl);
	DDX_Check(pDX, ID_DPFGRAPH_LOGBUTTON, DPFGraph_IsLog);
}

// Подключение обработчиков событий
BEGIN_MESSAGE_MAP(CKursachDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CKursachDlg::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, ID_N_SPIN, &CKursachDlg::OnDeltaposNSpin)
	ON_WM_SYSCOMMAND()
	ON_EN_KILLFOCUS(ID_N_EDIT, &CKursachDlg::OnEnKillfocusNEdit)
	ON_EN_KILLFOCUS(ID_F_EDIT, &CKursachDlg::OnEnKillfocusFEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_F_SPIN, &CKursachDlg::OnDeltaposFSpin)
	ON_EN_KILLFOCUS(ID_Fm_EDIT, &CKursachDlg::OnEnKillfocusFmEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_Fm_SPIN, &CKursachDlg::OnDeltaposFmSpin)
	ON_EN_KILLFOCUS(ID_M_EDIT, &CKursachDlg::OnEnKillfocusMEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_M_SPIN, &CKursachDlg::OnDeltaposMSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_SIGNALGRAPH_YCONTROL, &CKursachDlg::OnNMCustomdrawSignalgraphYcontrol)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_SIGNALGRAPH_XCONTROL, &CKursachDlg::OnNMCustomdrawSignalgraphXcontrol)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_DPFGRAPH_YCONTROL2, &CKursachDlg::OnNMCustomdrawDpfgraphYcontrol2)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_DPFGRAPH_XCONTROL2, &CKursachDlg::OnNMCustomdrawDpfgraphXcontrol2)
	ON_BN_CLICKED(ID_DPFGRAPH_LOGBUTTON, &CKursachDlg::OnBnClickedDpfgraphLogbutton)
END_MESSAGE_MAP()


// Обработчики сообщений CKursachDlg

BOOL CKursachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	// Связь стрелочек выбора и окошек выбора
	N_Spin.SetBuddy(&N_Edit);
	F_Spin.SetBuddy(&F_Edit);
	Fm_Spin.SetBuddy(&Fm_Edit);
	M_Spin.SetBuddy(&M_Edit);

	// Инициализация переменных
	N = 500;
	N_Edit.SetWindowTextW(L"500");

	F = 2000000;
	F_Edit.SetWindowTextW(L"2000000");

	Fm = 400000;
	Fm_Edit.SetWindowTextW(L"400000");

	M = 5;
	M_Edit.SetWindowTextW(L"5");

	// Ползунок графика сигнала по Y
	SignalGraph_YScale = 50;
	SignalGraph_YControl.SetRange(20, 100);
	SignalGraph_YControl.SetPos(50);

	// Ползунок графика сигнала по X
	SignalGraph_XScale = 30000000;
	SignalGraph_XControl.SetRange(20000000, 100000000);
	SignalGraph_XControl.SetPos(30000000);

	// Передача значений в глобальны переменные
	G_N = N;
	G_F = F;
	G_Fm = Fm;
	G_M = M;
	G_SignalGraph_XScale = double(SignalGraph_XScale);
	G_SignalGraph_YScale=SignalGraph_YScale;

	// Назначение окошка для рисования
	Graph_Signal.SubclassDlgItem(ID_SIGNALGRAPH_WINDOW, this);
	DPF_Signal.SubclassDlgItem(ID_DPFGRAPH_WINDOW, this);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CKursachDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.
void CKursachDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKursachDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Что происходит по нажатию кнопки Enter
void CKursachDlg::OnBnClickedOk()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(N, 100, 1000, N_Edit);  // Возвращение N в нормальные значения, если нужно
	data.CheckIntNumber(F, 1000000, 4000000, F_Edit);  // Возвращение F в нормальные значения, если нужно
	data.CheckIntNumber(Fm, 100000, 900000, Fm_Edit);  // Возвращение Fm в нормальные значения, если нужно
	data.CheckIntNumber(M, 0, 10, M_Edit);  // Возвращение M в нормальные значения, если нужно

	// Передача данных в глобальные значения
	G_N = N;
	G_F = F;
	G_Fm = Fm;
	G_M = M;
	G_SignalGraph_XScale = double(SignalGraph_XScale);
	G_SignalGraph_YScale = SignalGraph_YScale;

	// Инвалидация окошек с графиком (перерисовывание)
	Graph_Signal.Invalidate();
}

#pragma region Обработка ввода N

// Что происходит когда пропадает фокус с окна ввода F
void CKursachDlg::OnEnKillfocusNEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(N, 100, 1000, N_Edit);  // Возвращение N в нормальные значения, если нужно
	G_N = N;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки N
void CKursachDlg::OnDeltaposNSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(N, 100, 1000, N_Edit, pNMUpDown->iDelta);  // Изменение N
	G_N = N;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода F

// Что происходит когда пропадает фокус с окна ввода F
void CKursachDlg::OnEnKillfocusFEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(F, 1000000, 4000000, F_Edit);  // Возвращение F в нормальные значения, если нужно
	G_F = F;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки F
void CKursachDlg::OnDeltaposFSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(F, 1000000, 4000000, F_Edit, pNMUpDown->iDelta, 5000);  // Изменение F
	G_F = F;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода Fm

// Что происходит когда пропадает фокус с окна ввода Fm
void CKursachDlg::OnEnKillfocusFmEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(Fm, 100000, 900000, Fm_Edit);  // Возвращение Fm в нормальные значения, если нужно
	G_Fm = Fm;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки Fm
void CKursachDlg::OnDeltaposFmSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(Fm, 100000, 900000, Fm_Edit, pNMUpDown->iDelta, 1000);  // Изменение Fm
	G_Fm = Fm;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода M

// Что происходит когда пропадает фокус с окна ввода M
void CKursachDlg::OnEnKillfocusMEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(M, 0, 10, M_Edit);  // Возвращение M в нормальные значения, если нужно
	G_M = M;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки M
void CKursachDlg::OnDeltaposMSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(M, 0, 10, M_Edit, pNMUpDown->iDelta);  // Изменение M
	G_M = M;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка масштаба графика сигнала

// Что происходит когда двигают ползунок Y
void CKursachDlg::OnNMCustomdrawSignalgraphYcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	G_SignalGraph_YScale = SignalGraph_YScale;  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала

	*pResult = 0;
}

// Что происходит когда двигают ползунок X
void CKursachDlg::OnNMCustomdrawSignalgraphXcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	G_SignalGraph_XScale = double(SignalGraph_XScale);  // Передача в глобальное значение
	Graph_Signal.Invalidate();  // Перерисовывание графика сигнала

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка масштаба графика ДПФ

// Что происходит когда двигают ползунок Y
void CKursachDlg::OnNMCustomdrawDpfgraphYcontrol2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	G_DPFGraph_YScale = double(DPFGraph_YScale);  // Передача в глобальное значение
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

// Что происходит когда двигают ползунок X
void CKursachDlg::OnNMCustomdrawDpfgraphXcontrol2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	G_DPFGraph_XScale = double(DPFGraph_XScale);  // Передача в глобальное значение
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

// Что происходит когда нажимают на галочку логарифмирования
void CKursachDlg::OnBnClickedDpfgraphLogbutton()
{
	UpdateData();  // Обновление информации
	G_DPFGraph_IsLog=DPFGraph_IsLog;  // Передача в глобальное значение
	DPF_Signal.Invalidate();  // Перерисовывание графика ДПФ
}

#pragma endregion