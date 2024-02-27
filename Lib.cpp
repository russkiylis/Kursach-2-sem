#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "Kursach.h"
#include "KursachDlg.h"

#include <initguid.h>
DEFINE_GUID(ImageFormatBMP, 0xb96b3cab, 0x0728, 0x11d3, 0x9d, 0x7b,
	0x00, 0x00, 0xf8, 0x1e, 0xf3, 0x2e);

CString Lib_Converter::floatToCString_2(float& number)
{
	CString str;
	str.Format(_T("%.2f"), number);  // ���������� �����������

	return str;
}

CString Lib_Converter::intToCString(int& number)
{
	CString str;
	str.Format(_T("%d"), number);  // ���������� �����������

	return str;
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int &delta)
{
	number -= delta;  // ��������� ������ � ����������� � �������� ������ (���� ���������)

	if (number < smallest) {  // ���� ����� ������ ������ ���������� ����������, �� ����� ���������� ����� ��������� ���������
		number = smallest;
	}
	else if (number > largest) {  // ���� ����� ������ ������ �������� ����������, �� ����� ���������� ����� ������� ���������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

void Lib_InteractiveBoxesData::IntSpinChange(int& number, int smallest, int largest, CEdit& editBox, int& delta, int multiplier)
{
	number -= delta*multiplier; // ��������� ������ � ����������� � �������� ������ (���� ���������)

	if (number < smallest) {  // ���� ����� ������ ������ ���������� ����������, �� ����� ���������� ����� ��������� ���������
		number = smallest;
	}
	else if (number > largest) {  // ���� ����� ������ ������ �������� ����������, �� ����� ���������� ����� ������� ���������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

void Lib_InteractiveBoxesData::CheckIntNumber(int& number, int smallest, int largest, CEdit& editBox)
{
	if (number < smallest) {  // ����������� ������ � ����������� ��������
		number = smallest;
	}
	else if (number > largest) {  // ����������� ������ � ����������� ��������
		number = largest;
	}

	editBox.SetWindowTextW(intToCString(number));  // ������� ������ �������� � editBox
}

//void Lib_InteractiveBoxesData::PaintBMPExport(int uId)
//{
//	CWnd* pWnd = GetDlgItem(ID_SIGNALGRAPH_WINDOW);
//
//	if (!pWnd)
//		return;
//
//	CWindowDC winDC(pWnd);
//
//	CRect rc;
//	pWnd->GetClientRect(&rc);
//
//	CDC memDC;
//	memDC.CreateCompatibleDC(&winDC);
//
//	CBitmap bitMap;
//	bitMap.CreateCompatibleBitmap(&winDC, rc.Width(), rc.Height());
//
//	HGDIOBJ pOld = memDC.SelectObject(&bitMap);
//	memDC.BitBlt(0, 0, rc.Width(), rc.Height(), &winDC, 0, 0, SRCCOPY);
//	memDC.SelectObject(pOld);
//
//	static TCHAR szFilter[] = _T("BMP Files (*.bmp)|*.bmp|")
//		_T("PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif|")
//		_T("JPG Files (*.jpg)|*.jpg|All Files (*.*)|*.*||");
//	CFileDialog dlg(FALSE, _T(".bmp"), NULL, 6UL, szFilter);
//	if (IDOK == dlg.DoModal())
//	{
//		CImage image;
//		image.Attach(HBITMAP(bitMap));
//		CString strFull = dlg.GetOFN().lpstrFile;
//		HRESULT hr;
//
//		if (-1 != strFull.Find(_T(".bmp")))
//			hr = image.Save(strFull, ImageFormatBMP);
//		else
//		{
//			strFull += _T(".bmp");
//			hr = image.Save(strFull, ImageFormatBMP);
//		}
//		if (FAILED(hr))
//		{
//			CString strErr;
//			strErr.Format(L" Couldn't Save File: %s, %x ", (LPCTSTR)strFull,
//				hr);
//			AfxMessageBox(strErr, MB_OK | MB_ICONERROR);
//		}
//	}
//}

dXY Lib_PointCalculation::SignalCalculation(double& x)
{
	//���������� ����������� ���������� y
	double y = sin(2 * M_PI * F * x + M * sin(2 * M_PI * Fm * x));

	// ������ ������
	dXY ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

CPoint Lib_GraphConverter::GenerateDrawablePoint(CRect& rc, dXY& calculatedPoint, int x0, int y0, bool isLog)
{

	double x = x0 + calculatedPoint.x * XScale;  // ����������� � ������� � ����� + ���������������
	double y;

	if (isLog) {
		y = y0 - log10(calculatedPoint.y) * YScale;  // ����������� y ������� � ����� + ��������������� (��������)
		if (y>259) y -= (y - 260);
	}
	else {
		y = y0 - calculatedPoint.y * YScale;  // ����������� y ������� � ����� + ���������������
	}


	// ������ ������
	CPoint ans;
	ans.x = x;
	ans.y = y;

	return ans;
}

void Lib_GraphConverter::GenerateSignalGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// ������� �����
	for (int i = 0; i < N; i++) {

		double x = double(i) /10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
		dXY calc = SignalCalculation(x);  // ������� �����

		CPoint point = GenerateDrawablePoint(rc, calc, 0, rc.Height() / 2);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����
		
		vec.push_back(point);  // ���������� ����� � ������ �����
	}

}

void Lib_GraphConverter::GenerateDPFGraphPoints(CRect& rc, std::vector<CPoint>& vec)
{
	// ������� �����
	for (int i = 0; i < N; i++) {

		dXY DPFCalc;
		double sin_sum = 0, cos_sum = 0;

		for (int g = 0; g < N; g++) {
			double x = double(g) / 10000000;  // ������������� �������� i ������� �� 10^7 ��� ��� �� ������� ������� �������� ������� 10 ���
			dXY calc = SignalCalculation(x);  // ������� �����

			sin_sum += calc.y * sin((-2 * M_PI * i * g) /N);  // ������� �������� ������������ ��
			cos_sum += calc.y * cos((-2 * M_PI * i * g) / N);  // ������� ���������� ������������ ��

		}

		DPFCalc.x = double(i)/10000000;  // ����������� ����� �
		DPFCalc.y = sqrt(pow(cos_sum,2)+pow(sin_sum,2));  // ����������� ����� � (������ �� ����� ��������� �������� � ���������� ������������)

		CPoint point = GenerateDrawablePoint(rc, DPFCalc, 0, rc.Height()-1, isLog);  // ���� ����������� ����� � ����������� � � �����, ������� ����� ���������� � ����

		vec.push_back(point);  // ���������� ����� � ������ �����
	}
}
