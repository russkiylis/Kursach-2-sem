
// KursachDlg.cpp: файл реализации
//

#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Radiosignal.h"
#include "RadiosignalDlg.h"

#include <initguid.h>
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatEMF, 0xb96b3cac, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatWMF, 0xb96b3cad, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatJPEG, 0xb96b3cae, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatPNG, 0xb96b3caf, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatGIF, 0xb96b3cb0, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);
DEFINE_GUID(ImageFormatTIFF, 0xb96b3cb1, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

bool IsRestart = false;

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


// Диалоговое окно CRadiosignalDlg
CRadiosignalDlg::CRadiosignalDlg(CWnd* pParent /*=nullptr*/)
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
	, SWidth(0)
	, SXDensity(0)
	, DWidth(0)
	, DXDensity(0)
	, SYDensity(0)
	, DYDensity(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// Связь переменных с интерфейсом
void CRadiosignalDlg::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, SGColorControl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON2, SCColorControl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON3, SBColorControl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON4, DGColorControl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON5, DCColorControl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON6, DBColorControl);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON1, SGColor);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON2, SCColor);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON3, SBColor);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON4, DGColor);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON5, DCColor);
	DDX_Text(pDX, IDC_MFCCOLORBUTTON6, DBColor);
	DDX_Control(pDX, IDC_SLIDER1, SWidthControl);
	DDX_Control(pDX, IDC_SLIDER2, SXDensityControl);
	DDX_Control(pDX, IDC_SLIDER3, DWidthControl);
	DDX_Control(pDX, IDC_SLIDER4, DXDensityControl);
	DDX_Slider(pDX, IDC_SLIDER1, SWidth);
	DDX_Slider(pDX, IDC_SLIDER2, SXDensity);
	DDX_Slider(pDX, IDC_SLIDER3, DWidth);
	DDX_Slider(pDX, IDC_SLIDER4, DXDensity);
	DDX_Control(pDX, IDC_SLIDER5, SYDensityControl);
	DDX_Slider(pDX, IDC_SLIDER5, SYDensity);
	DDX_Control(pDX, IDC_SLIDER6, DYDensityControl);
	DDX_Slider(pDX, IDC_SLIDER6, DYDensity);
}

// Подключение обработчиков событий
BEGIN_MESSAGE_MAP(CRadiosignalDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CRadiosignalDlg::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, ID_N_SPIN, &CRadiosignalDlg::OnDeltaposNSpin)
	ON_WM_SYSCOMMAND()
	ON_EN_KILLFOCUS(ID_N_EDIT, &CRadiosignalDlg::OnEnKillfocusNEdit)
	ON_EN_KILLFOCUS(ID_F_EDIT, &CRadiosignalDlg::OnEnKillfocusFEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_F_SPIN, &CRadiosignalDlg::OnDeltaposFSpin)
	ON_EN_KILLFOCUS(ID_Fm_EDIT, &CRadiosignalDlg::OnEnKillfocusFmEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_Fm_SPIN, &CRadiosignalDlg::OnDeltaposFmSpin)
	ON_EN_KILLFOCUS(ID_M_EDIT, &CRadiosignalDlg::OnEnKillfocusMEdit)
	ON_NOTIFY(UDN_DELTAPOS, ID_M_SPIN, &CRadiosignalDlg::OnDeltaposMSpin)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_SIGNALGRAPH_YCONTROL, &CRadiosignalDlg::OnNMCustomdrawSignalgraphYcontrol)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_SIGNALGRAPH_XCONTROL, &CRadiosignalDlg::OnNMCustomdrawSignalgraphXcontrol)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_DPFGRAPH_YCONTROL2, &CRadiosignalDlg::OnNMCustomdrawDpfgraphYcontrol2)
	ON_NOTIFY(NM_CUSTOMDRAW, ID_DPFGRAPH_XCONTROL2, &CRadiosignalDlg::OnNMCustomdrawDpfgraphXcontrol2)
	ON_BN_CLICKED(ID_DPFGRAPH_LOGBUTTON, &CRadiosignalDlg::OnBnClickedDpfgraphLogbutton)
	ON_BN_CLICKED(ID_SIGNALGRAPH_BMPBUTTON, &CRadiosignalDlg::OnBnClickedSignalgraphBmpbutton)
	ON_BN_CLICKED(ID_DPFGRAPH_BMPBUTTON, &CRadiosignalDlg::OnBnClickedDpfgraphBmpbutton)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CRadiosignalDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON2, &CRadiosignalDlg::OnBnClickedMfccolorbutton2)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON3, &CRadiosignalDlg::OnBnClickedMfccolorbutton3)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON4, &CRadiosignalDlg::OnBnClickedMfccolorbutton4)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON5, &CRadiosignalDlg::OnBnClickedMfccolorbutton5)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON6, &CRadiosignalDlg::OnBnClickedMfccolorbutton6)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CRadiosignalDlg::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CRadiosignalDlg::OnNMCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CRadiosignalDlg::OnNMCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &CRadiosignalDlg::OnNMCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &CRadiosignalDlg::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, &CRadiosignalDlg::OnNMCustomdrawSlider6)
	ON_BN_CLICKED(IDC_BUTTON2, &CRadiosignalDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CRadiosignalDlg::OnBnClickedButton3)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// Обработчики сообщений CRadiosignalDlg

BOOL CRadiosignalDlg::OnInitDialog()
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

	Lib_ValueConverter converter;

	// Инициализация переменных
	N = AfxGetApp()->GetProfileInt(L"Settings", L"N", 500);
	N_Edit.SetWindowTextW(converter.intToCString(N));
	F = AfxGetApp()->GetProfileInt(L"Settings", L"F", 2000000);
	F_Edit.SetWindowTextW(converter.doubleToCString_3(F));
	Fm = AfxGetApp()->GetProfileInt(L"Settings", L"Fm", 400000);;
	Fm_Edit.SetWindowTextW(converter.doubleToCString_3(Fm));
	M = AfxGetApp()->GetProfileInt(L"Settings", L"M", 5);
	M_Edit.SetWindowTextW(converter.doubleToCString_3(M));

	DPFGraph_IsLog = AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_IsLog", 0);
	DPFGraph_LogControl.SetCheck(AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_IsLog", 0));

	// Ползунок графика сигнала по Y
	SignalGraph_YScale = AfxGetApp()->GetProfileInt(L"Settings", L"SignalGraph_YScale", 1500);
	SignalGraph_YControl.SetRange(600, 3000);
	SignalGraph_YControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"SignalGraph_YScale", 1500));

	// Ползунок графика сигнала по X
	SignalGraph_XScale = AfxGetApp()->GetProfileInt(L"Settings", L"SignalGraph_XScale", 300);
	SignalGraph_XControl.SetRange(200, 1000);
	SignalGraph_XControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"SignalGraph_XScale", 300));

	// Ползунок графика ДПФ по Y
	DPFGraph_YScale = AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_YScale", 50);
	DPFGraph_YControl.SetRange(50, 100);
	DPFGraph_YControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_YScale", 50));

	// Ползунок графика ДПФ по X
	DPFGraph_XScale = AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_XScale", 300);
	DPFGraph_XControl.SetRange(200, 1000);
	DPFGraph_XControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"DPFGraph_XScale", 300));

	// Ползунок ширины сигнала
	SWidth = AfxGetApp()->GetProfileInt(L"Settings", L"SWidth", 2);
	SWidthControl.SetRange(1, 5);
	SWidthControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"SWidth", 2));

	// Ползунок ширины ДПФ
	DWidth = AfxGetApp()->GetProfileInt(L"Settings", L"DWidth", 2);
	DWidthControl.SetRange(1, 5);
	DWidthControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"DWidth", 2));

	// Ползунок плотности координат сигнала x
	SXDensity = AfxGetApp()->GetProfileInt(L"Settings", L"SXDensity", 25);
	SXDensityControl.SetRange(10, 50);
	SXDensityControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"SXDensity", 25));

	// Ползунок плотности координат сигнала y
	SYDensity = AfxGetApp()->GetProfileInt(L"Settings", L"SYDensity", 50);
	SYDensityControl.SetRange(50, 100);
	SYDensityControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"SYDensity", 50));

	// Ползунок плотности координат ДПФ x
	DXDensity = AfxGetApp()->GetProfileInt(L"Settings", L"DXDensity", 25);
	DXDensityControl.SetRange(10, 50);
	DXDensityControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"DXDensity", 25));

	// Ползунок плотности координат ДПФ y
	DYDensity = AfxGetApp()->GetProfileInt(L"Settings", L"DYDensity", 25);
	DYDensityControl.SetRange(25, 50);
	DYDensityControl.SetPos(AfxGetApp()->GetProfileInt(L"Settings", L"DYDensity", 25));

	// Начальное задание цвета
	SGColor = AfxGetApp()->GetProfileInt(L"Settings", L"SGColor", 0);
	DGColor = AfxGetApp()->GetProfileInt(L"Settings", L"DGColor", 0);
	SCColor = AfxGetApp()->GetProfileInt(L"Settings", L"SCColor", 13158600);
	DCColor = AfxGetApp()->GetProfileInt(L"Settings", L"DCColor", 13158600);
	SBColor = AfxGetApp()->GetProfileInt(L"Settings", L"SBColor", 16777215);
	DBColor = AfxGetApp()->GetProfileInt(L"Settings", L"DBColor", 16777215);
	SGColorControl.SetColor(SGColor);
	DGColorControl.SetColor(DGColor);
	SCColorControl.SetColor(SCColor);
	DCColorControl.SetColor(DCColor);
	SBColorControl.SetColor(SBColor);
	DBColorControl.SetColor(DBColor);

	// Передача в класс построения графика сигнала
	Signal.N = N;
	Signal.F = F;
	Signal.Fm = Fm;
	Signal.M = M;
	Signal.XScale = SignalGraph_XScale;
	Signal.YScale = SignalGraph_YScale;
	Signal.GColor = SGColor;
	Signal.CColor = SCColor;
	Signal.BColor = SBColor;
	Signal.GWidth = SWidth;
	Signal.CXDensity = SXDensity;
	Signal.CYDensity = SYDensity;
	Signal.IsDPF = false;

	// Передача в класс построения графика ДПФ
	DPF.N = N;
	DPF.F = F;
	DPF.Fm = Fm;
	DPF.M = M;
	DPF.XScale = DPFGraph_XScale;
	DPF.YScale = DPFGraph_YScale;
	DPF.GColor = DGColor;
	DPF.CColor = DCColor;
	DPF.BColor = DBColor;
	DPF.GWidth = DWidth;
	DPF.CXDensity = DXDensity;
	DPF.CYDensity = DYDensity;
	DPF.IsLog = DPFGraph_IsLog;
	DPF.IsDPF = true;

	// Назначение окошка для рисования
	Signal.SubclassDlgItem(ID_SIGNALGRAPH_WINDOW, this);
	DPF.SubclassDlgItem(ID_DPFGRAPH_WINDOW, this);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CRadiosignalDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CRadiosignalDlg::OnPaint()
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
HCURSOR CRadiosignalDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Что происходит по нажатию кнопки Enter
void CRadiosignalDlg::OnBnClickedOk()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(N, 100, 1000, N_Edit);  // Возвращение N в нормальные значения, если нужно
	data.CheckIntNumber(F, 1000000, 4000000, F_Edit);  // Возвращение F в нормальные значения, если нужно
	data.CheckIntNumber(Fm, 100000, 900000, Fm_Edit);  // Возвращение Fm в нормальные значения, если нужно
	data.CheckIntNumber(M, 0, 10, M_Edit);  // Возвращение M в нормальные значения, если нужно

	// Получение цвета
	SGColor = SGColorControl.GetColor();
	SCColor = SCColorControl.GetColor();
	SBColor = SBColorControl.GetColor();
	DGColor = DGColorControl.GetColor();
	DCColor = DCColorControl.GetColor();
	DBColor = DBColorControl.GetColor();

	// Передача в класс построения графика сигнала
	Signal.N = N;
	Signal.F = F;
	Signal.Fm = Fm;
	Signal.M = M;
	Signal.XScale = SignalGraph_XScale;
	Signal.YScale = SignalGraph_YScale;
	Signal.GColor = SGColor;
	Signal.CColor = SCColor;
	Signal.BColor = SBColor;
	Signal.CXDensity = SXDensity;
	Signal.CYDensity = SYDensity;

	// Передача в класс построения графика ДПФ
	DPF.N = N;
	DPF.F = F;
	DPF.Fm = Fm;
	DPF.M = M;
	DPF.XScale = DPFGraph_XScale;
	DPF.YScale = DPFGraph_YScale;
	DPF.GColor = DGColor;
	DPF.CColor = DCColor;
	DPF.BColor = DBColor;
	DPF.CXDensity = DXDensity;
	DPF.CYDensity = DYDensity;

	// Инвалидация окошек с графиком (перерисовывание)
	Signal.Invalidate();
	DPF.Invalidate();
}

#pragma region Обработка ввода N

// Что происходит когда пропадает фокус с окна ввода F
void CRadiosignalDlg::OnEnKillfocusNEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(N, 100, 1000, N_Edit);  // Возвращение N в нормальные значения, если нужно

	Signal.N = N;  // Передача в класс построения графика сигнала
	DPF.N = N;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки N
void CRadiosignalDlg::OnDeltaposNSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(N, 100, 1000, N_Edit, pNMUpDown->iDelta);  // Изменение N

	Signal.N = N;  // Передача в класс построения графика сигнала
	DPF.N = N;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ
	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода F

// Что происходит когда пропадает фокус с окна ввода F
void CRadiosignalDlg::OnEnKillfocusFEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(F, 1000000, 4000000, F_Edit);  // Возвращение F в нормальные значения, если нужно

	Signal.F = F;  // Передача в класс построения графика сигнала
	DPF.F = F;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки F
void CRadiosignalDlg::OnDeltaposFSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(F, 1000000, 4000000, F_Edit, pNMUpDown->iDelta, 5000);  // Изменение F

	Signal.F = F;  // Передача в класс построения графика сигнала
	DPF.F = F;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода Fm

// Что происходит когда пропадает фокус с окна ввода Fm
void CRadiosignalDlg::OnEnKillfocusFmEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(Fm, 100000, 900000, Fm_Edit);  // Возвращение Fm в нормальные значения, если нужно

	Signal.Fm = Fm;  // Передача в класс построения графика сигнала
	DPF.Fm = Fm;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ
}

// Что происходит когда нажимаются кнопочки Fm
void CRadiosignalDlg::OnDeltaposFmSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(Fm, 100000, 900000, Fm_Edit, pNMUpDown->iDelta, 1000);  // Изменение Fm

	Signal.Fm = Fm;  // Передача в класс построения графика сигнала
	DPF.Fm = Fm;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка ввода M

// Что происходит когда пропадает фокус с окна ввода M
void CRadiosignalDlg::OnEnKillfocusMEdit()
{
	Lib_InteractiveBoxesData data;

	UpdateData();  // Обновление информации
	data.CheckIntNumber(M, 0, 10, M_Edit);  // Возвращение M в нормальные значения, если нужно

	Signal.M = M;  // Передача в класс построения графика сигнала
	DPF.M = M;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ

}

// Что происходит когда нажимаются кнопочки M
void CRadiosignalDlg::OnDeltaposMSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	Lib_InteractiveBoxesData data;
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	data.IntSpinChange(M, 0, 10, M_Edit, pNMUpDown->iDelta);  // Изменение M

	Signal.M = M;  // Передача в класс построения графика сигнала
	DPF.M = M;  // Передача в класс построения графика ДПФ

	Signal.Invalidate();  // Перерисовывание графика сигнала
	DPF.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка масштаба графика сигнала

// Что происходит когда двигают ползунок Y
void CRadiosignalDlg::OnNMCustomdrawSignalgraphYcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	Signal.YScale = SignalGraph_YScale;  // Передача в класс
	Signal.Invalidate();  // Перерисовывание графика сигнала

	*pResult = 0;
}

// Что происходит когда двигают ползунок X
void CRadiosignalDlg::OnNMCustomdrawSignalgraphXcontrol(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	Signal.XScale = SignalGraph_XScale;  // Передача в класс
	Signal.Invalidate();  // Перерисовывание графика сигнала

	*pResult = 0;
}

#pragma endregion

#pragma region Обработка масштаба графика ДПФ

// Что происходит когда двигают ползунок Y
void CRadiosignalDlg::OnNMCustomdrawDpfgraphYcontrol2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	DPF.YScale = DPFGraph_YScale;  // Передача в класс
	DPF.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

// Что происходит когда двигают ползунок X
void CRadiosignalDlg::OnNMCustomdrawDpfgraphXcontrol2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);

	UpdateData();  // Обновление информации
	DPF.XScale = DPFGraph_XScale;  // Передача в класс
	DPF.Invalidate();  // Перерисовывание графика ДПФ

	*pResult = 0;
}

// Что происходит когда нажимают на галочку логарифмирования
void CRadiosignalDlg::OnBnClickedDpfgraphLogbutton()
{
	UpdateData();  // Обновление информации
	DPF.IsLog=DPFGraph_IsLog;  // Передача в глобальное значение
	DPF.Invalidate();  // Перерисовывание графика ДПФ
}

#pragma endregion

#pragma region Вывод в картинку

void CRadiosignalDlg::OnBnClickedSignalgraphBmpbutton()
{
	CWnd* pWnd = GetDlgItem(ID_SIGNALGRAPH_WINDOW);

	if (!pWnd)
		return;

	CWindowDC winDC(pWnd);

	CRect rc;
	pWnd->GetClientRect(&rc);

	CDC memDC;
	memDC.CreateCompatibleDC(&winDC);

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(&winDC, rc.Width(), rc.Height());

	HGDIOBJ pOld = memDC.SelectObject(&bitMap);
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);

	static TCHAR szFilter[] = _T("Рисунки BMP (*.bmp)|*.bmp|")
		_T("Рисунки PNG (*.png)|*.png|Рисунки GIF (*.gif)|*.gif|")
		_T("Рисунки JPG (*.jpg)|*.jpg|Все файлы (*.*)|*.*||");
	CFileDialog dlg(FALSE, _T(".bmp"), _T("График сигнала"), 6UL, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CImage image;
		image.Attach(HBITMAP(bitMap));
		CString strFull = dlg.GetOFN().lpstrFile;
		HRESULT hr;

		if (-1 != strFull.Find(_T(".png")))
			hr = image.Save(strFull, ImageFormatPNG);
		else if (-1 != strFull.Find(_T(".jpg")))
			hr = image.Save(strFull, ImageFormatJPEG);
		else if (-1 != strFull.Find(_T(".gif")))
			hr = image.Save(strFull, ImageFormatGIF);
		else if (-1 != strFull.Find(_T(".bmp")))
			hr = image.Save(strFull, ImageFormatBMP);
		else
		{
			strFull += _T(".bmp");
			hr = image.Save(strFull, ImageFormatBMP);
		}
		if (FAILED(hr))
		{
			CString strErr;
				strErr.Format(L" Невозможно сохранить файл: %s, %x ", (LPCTSTR)strFull,
					hr);
			AfxMessageBox(strErr, MB_OK | MB_ICONERROR);
		}
	}
}



void CRadiosignalDlg::OnBnClickedDpfgraphBmpbutton()
{
	CWnd* pWnd = GetDlgItem(ID_DPFGRAPH_WINDOW);

	if (!pWnd)
		return;

	CWindowDC winDC(pWnd);

	CRect rc;
	pWnd->GetClientRect(&rc);

	CDC memDC;
	memDC.CreateCompatibleDC(&winDC);

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(&winDC, rc.Width(), rc.Height());

	HGDIOBJ pOld = memDC.SelectObject(&bitMap);
	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), &winDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOld);

	static TCHAR szFilter[] = _T("Рисунки BMP (*.bmp)|*.bmp|")
		_T("Рисунки PNG (*.png)|*.png|Рисунки GIF (*.gif)|*.gif|")
		_T("Рисунки JPG (*.jpg)|*.jpg|Все файлы (*.*)|*.*||");

	CFileDialog dlg(FALSE, _T(".bmp"), _T("График модуля ДПФ"), 6UL, szFilter);
	if (IDOK == dlg.DoModal())
	{
		CImage image;
		image.Attach(HBITMAP(bitMap));
		CString strFull = dlg.GetOFN().lpstrFile;
		HRESULT hr;

		if (-1 != strFull.Find(_T(".png")))
			hr = image.Save(strFull, ImageFormatPNG);
		else if (-1 != strFull.Find(_T(".jpg")))
			hr = image.Save(strFull, ImageFormatJPEG);
		else if (-1 != strFull.Find(_T(".gif")))
			hr = image.Save(strFull, ImageFormatGIF);
		else if (-1 != strFull.Find(_T(".bmp")))
			hr = image.Save(strFull, ImageFormatBMP);
		else
		{
			strFull += _T(".bmp");
			hr = image.Save(strFull, ImageFormatBMP);
		}
		if (FAILED(hr))
		{
			CString strErr;
			strErr.Format(L" Невозможно сохранить файл: %s, %x ", (LPCTSTR)strFull,
				hr);
			AfxMessageBox(strErr, MB_OK | MB_ICONERROR);
		}
	}
}

#pragma endregion

#pragma region Обработка цвета

void CRadiosignalDlg::OnBnClickedMfccolorbutton1()
{
	// Получение цвета
	SGColor = SGColorControl.GetColor();

	Signal.GColor = SGColor;
	Signal.Invalidate();
}

void CRadiosignalDlg::OnBnClickedMfccolorbutton2()
{
	// Получение цвета
	SCColor = SCColorControl.GetColor();

	Signal.CColor = SCColor;
	Signal.Invalidate();
}

void CRadiosignalDlg::OnBnClickedMfccolorbutton3()
{	
	// Получение цвета
	SBColor = SBColorControl.GetColor();

	Signal.BColor = SBColor;
	Signal.Invalidate();
}

void CRadiosignalDlg::OnBnClickedMfccolorbutton4()
{
	// Получение цвета
	DGColor = DGColorControl.GetColor();

	DPF.GColor = DGColor;
	DPF.Invalidate();
}

void CRadiosignalDlg::OnBnClickedMfccolorbutton5()
{
	// Получение цвета
	DCColor = DCColorControl.GetColor();

	DPF.CColor = DCColor;
	DPF.Invalidate();
}

void CRadiosignalDlg::OnBnClickedMfccolorbutton6()
{
	// Получение цвета
	DBColor = DBColorControl.GetColor();

	DPF.BColor = DBColor;
	DPF.Invalidate();
}

#pragma endregion

#pragma region Ширина графиков

void CRadiosignalDlg::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData(); // Обновление информации
	Signal.GWidth = SWidth;
	Signal.Invalidate();

	*pResult = 0;
}

void CRadiosignalDlg::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData(); // Обновление информации
	DPF.GWidth = DWidth;
	DPF.Invalidate();

	*pResult = 0;
}

#pragma endregion

#pragma region Плотность координат

void CRadiosignalDlg::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData();
	Signal.CXDensity = SXDensity;
	Signal.Invalidate();

	*pResult = 0;
}

void CRadiosignalDlg::OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData();
	Signal.CYDensity = SYDensity;
	Signal.Invalidate();

	*pResult = 0;
}

void CRadiosignalDlg::OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData();
	DPF.CXDensity = DXDensity;
	DPF.Invalidate();

	*pResult = 0;
}

void CRadiosignalDlg::OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	UpdateData();
	DPF.CYDensity = DYDensity;
	DPF.Invalidate();

	*pResult = 0;
}

#pragma endregion

// Сохранение в реестр Windows
void CRadiosignalDlg::RegistrySave()
{
	HRESULT hr;
	// Обновление информации
	UpdateData();

	// Обновление цвета
	DBColor = DBColorControl.GetColor();
	SBColor = SBColorControl.GetColor();
	DGColor = DGColorControl.GetColor();
	SGColor = SGColorControl.GetColor();
	DCColor = DCColorControl.GetColor();
	SCColor = SCColorControl.GetColor();

	// Внесение цвета в реестр
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DBColor"), DBColor);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SBColor"), SBColor);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DGColor"), DGColor);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SGColor"), SGColor);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DCColor"), DCColor);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SCColor"), SCColor);

	// Внесение переменных в реестр
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("N"), N);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("F"), F);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("Fm"), Fm);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("M"), M);

	// Внесение масштаба и состояния логарифма в реестр
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SignalGraph_XScale"), SignalGraph_XScale);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SignalGraph_YScale"), SignalGraph_YScale);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DPFGraph_XScale"), DPFGraph_XScale);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DPFGraph_YScale"), DPFGraph_YScale);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DPFGraph_IsLog"), DPFGraph_IsLog);

	// Внесение координат и ширины в реестр
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SWidth"), SWidth);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DWidth"), DWidth);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SXDensity"), SXDensity);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("SYDensity"), SYDensity);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DXDensity"), DXDensity);
	hr = AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DYDensity"), DYDensity);

	if (FAILED(hr))
	{
		CString strErr;
		strErr.Format(L"Ошибка сохранения конфигурации!");
		AfxMessageBox(strErr, MB_OK | MB_ICONERROR);
	}
	else {
		CString strOk;
		strOk.Format(L"Конфигурация сохранена в реестр.");
		AfxMessageBox(strOk, MB_OK | MB_ICONINFORMATION);
	}
}

// Кнопка сохранения конфигурации
void CRadiosignalDlg::OnBnClickedButton2()
{
	RegistrySave();
}

// Кнопка сброса конфигурации
void CRadiosignalDlg::OnBnClickedButton3()
{
	if (AfxMessageBox(L"Вы действительно хотите сбросить конфигурацию?", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL) return;

	AfxGetApp()->DelRegTree(HKEY_CURRENT_USER, _T("SOFTWARE\\russkiylis\\Radiosignal\\Settings"));  // Удаление реестра
	IsRestart = true; // Нам нужен рестарт
	this->SendMessage(WM_CLOSE);  // Вызов функции закрытия
}

// Перезапуск программы
void CRadiosignalDlg::OnClose()
{
	if (IsRestart)  // Если рестарт то стартуем нашу программу заново
	{
		// Путь к программе
		wchar_t ProgramPath[100];
		GetModuleFileName(NULL, ProgramPath, 100);

		STARTUPINFO StartInfo;
		PROCESS_INFORMATION procStruct;
		memset(&StartInfo, 0, sizeof(STARTUPINFO));
		StartInfo.cb = sizeof(STARTUPINFO);

		if (CreateProcess((LPCTSTR)ProgramPath, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct))
		{
			CloseHandle(procStruct.hProcess);
			CloseHandle(procStruct.hThread);
		}
	}

	CDialogEx::OnClose();
}
