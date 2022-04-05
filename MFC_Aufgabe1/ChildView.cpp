
// ChildView.cpp: Implementierung der CChildView-Klasse
//
#include <math.h>

#include "pch.h"
#include "framework.h"
#include "MFC_Aufgabe1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_AUFGABE1_DIAGONALE, &CChildView::OnAufgabe1Diagonale)
	ON_COMMAND(ID_AUFGABE1_JULIAMENGE, &CChildView::OnAufgabe1Juliamenge)
	ON_COMMAND(ID_AUFGABE1_JULIAMENGE_ZOOM, &CChildView::OnAufgabe1JuliamengeZoom)
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_AUFGABE1_MANDELBROT, &CChildView::OnAufgabe1Mandelbrot)
END_MESSAGE_MAP()



// CChildView-Meldungshandler

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	
	// TODO: Fügen Sie hier Ihren Meldungshandlercode ein.
	
	// Rufen Sie nicht CWnd::OnPaint() zum Zeichnen von Nachrichten auf
}



void CChildView::OnAufgabe1Diagonale()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);

	// rp := Rahmen vom Parentframe
	// rc := Rahmen vom Childframe
	// diff := Differenz der GUI
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();

	// Addition der Differenz, damit Zeichenbereich auch wirklich 700*700
	GetParent()->SetWindowPos(NULL, 50, 50, 700+diffx, 700+diffy, SWP_SHOWWINDOW);

	UpdateWindow();

	CDC* pDC = GetDC();
	for (int i = 0; i < 700; i++) {
		pDC->SetPixel(i, i, RGB(255, 0, 0));
	}

}

// Aufgabe 1.2 & 1.3
void CChildView::OnAufgabe1Juliamenge()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();
	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);
	UpdateWindow();
	CDC* pDC = GetDC();
	
	
	int xp, xp_min = 0, xp_delta = 700;
	int yp, yp_min = 0, yp_delta = 700;
	double xd, xd_min = -1.6, xd_delta = 3.2;
	double yd, yd_min = -1.6, yd_delta = 3.2;

	for (xp = 0; xp < 700; xp++) {
		for (yp = 0; yp < 700; yp++) {
			xd = xd_min + xp * xd_delta / xp_delta;
			yd = yd_min + yp * yd_delta / yp_delta;

			double a_alt = xd;
			double b_alt = yd;
			double a_neu, b_neu;
			int n;
			double ab2;
			for (n = 1; n < 255; n++) {  // voher n < 50
				a_neu = pow(a_alt,2) - pow(b_alt,2) - 0.75;
				b_neu = 2 * a_alt * b_alt + 0.06;
				a_alt = a_neu;
				b_alt = b_neu;
				ab2 = (pow(a_alt, 2) + pow(b_alt, 2));
				if ( ab2 > 4) {
					break;
				}
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n, 0, (int)ab2));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(138, 43, 226));
				// pDC->SetPixel(xp, yp, RGB(0, 0, 0));
			}
		}
	}
}

// Aufgabe 1.4
void CChildView::OnAufgabe1JuliamengeZoom()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();
	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);
	UpdateWindow();


	xd_min = -1.6, xd_delta = 3.2;
	yd_min = -1.6, yd_delta = 3.2;

	JuliaMalen();
}
	
void CChildView::JuliaMalen(){
	CDC* pDC = GetDC();
	int xp, xp_min = 0, xp_delta = 700;
	int yp, yp_min = 0, yp_delta = 700;

	double xd, yd;
	for (xp = 0; xp < 700; xp++) {
		for (yp = 0; yp < 700; yp++) {
			xd = xd_min + xp * xd_delta / xp_delta;
			yd = yd_min + yp * yd_delta / yp_delta;
			double a_alt = xd;
			double b_alt = yd;
			double a_neu, b_neu;
			int n;
			double ab2;
			for (n = 1; n < 255; n++) {
				a_neu = pow(a_alt, 2) - pow(b_alt, 2) - 0.75;
				b_neu = 2 * a_alt * b_alt + 0.06;
				a_alt = a_neu;
				b_alt = b_neu;
				ab2 = (pow(a_alt, 2) + pow(b_alt, 2));
				if (ab2 > 4) {
					break;
				}
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n%255, 0, (int)ab2));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(138, 43, 226));
			}
		}
	}
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	double xd = xd_min + point.x * xd_delta / 700.;
	double yd = yd_min + point.y * yd_delta / 700.;

	xd_delta = xd_delta / 2;
	yd_delta = yd_delta / 2;

	xd_min = xd - xd_delta / 2;
	yd_min = yd - yd_delta / 2;

	JuliaMalen();

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	double xd = xd_min + point.x * xd_delta / 700.;
	double yd = yd_min + point.y * yd_delta / 700.;

	xd_delta = xd_delta * 2;
	yd_delta = yd_delta * 2;

	xd_min = xd - xd_delta / 2;
	yd_min = yd - yd_delta / 2;

	JuliaMalen();


	CWnd::OnRButtonUp(nFlags, point);
}


void CChildView::OnAufgabe1Mandelbrot()
{
	CRect rc, rp;
	GetClientRect(&rc);
	GetParent()->GetWindowRect(rp);
	int diffx = rp.Width() - rc.Width();
	int diffy = rp.Height() - rc.Height();
	GetParent()->SetWindowPos(NULL, 50, 50, 700 + diffx, 700 + diffy, SWP_SHOWWINDOW);
	UpdateWindow();


	xd_min = -2., xd_delta = 0.5;
	yd_min = -1.25, yd_delta = 1.25;

	MandelbrotMalen();
}

void CChildView::MandelbrotMalen() {
	CDC* pDC = GetDC();
	int xp, xp_min = 0, xp_delta = 700;
	int yp, yp_min = 0, yp_delta = 700;

	double xd, yd;
	for (xp = 0; xp < 700; xp++) {
		for (yp = 0; yp < 700; yp++) {
			xd = xd_min + xp * xd_delta / xp_delta;
			yd = yd_min + yp * yd_delta / yp_delta;
			double a_alt = xd;
			double b_alt = yd;
			double a_neu, b_neu;
			int n;
			double ab2;
			for (n = 1; n < 255; n++) {
				a_neu = pow(a_alt, 2) - pow(b_alt, 2) - 0.75;
				b_neu = 2 * a_alt * b_alt + 0.06;
				a_alt = a_neu;
				b_alt = b_neu;
				ab2 = (pow(a_alt, 2) + pow(b_alt, 2));
				if (ab2 > 4) {
					break;
				}
			}
			if (ab2 > 4) {
				pDC->SetPixel(xp, yp, RGB(n % 255, 0, (int)ab2));
			}
			else {
				pDC->SetPixel(xp, yp, RGB(138, 43, 226));
			}
		}
	}
}