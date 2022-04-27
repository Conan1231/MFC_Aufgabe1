
// ChildView.cpp: Implementierung der CChildView-Klasse
//
#include <math.h>

#include "pch.h"
#include "framework.h"
#include "MFC_Aufgabe1.h"
#include "ChildView.h"
#include "Vektor2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static int auswahl;

// CChildView

CChildView::CChildView()
{
	double xd_min = 0;
	double xd_delta = 0;
	double yd_min = 0;
	double yd_delta = 0;
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
	ON_COMMAND(ID_VEKTOR_QUADRAT1, &CChildView::OnVektorQuadrat1)
	ON_COMMAND(ID_VEKTOR_QUADRATROTIEREN, &CChildView::OnVektorQuadratrotieren)
	ON_COMMAND(ID_VEKTOR_QUADRATROTIERENV2, &CChildView::OnVektorQuadratrotierenv2)
	ON_COMMAND(ID_AUFGABE4_W32780, &CChildView::OnAufgabe4W32780)
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

	auswahl = 1;

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

	if (auswahl == 1) {
		JuliaMalen();
	}
	else if (auswahl == 2) {
		MandelbrotMalen();
	}
	else {
		return;
	}
	
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

	if (auswahl == 1) {
		JuliaMalen();
	}
	else if (auswahl == 2) {
		MandelbrotMalen();
	}
	else {
		return;
	}

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

	auswahl = 2;

	xd_min = -2., xd_delta = 2.5;
	yd_min = -1.25, yd_delta = 2.5;

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
				a_neu = pow(a_alt, 2) - pow(b_alt, 2) + xd;
				b_neu = 2 * a_alt * b_alt + yd;
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

void CChildView::OnVektorQuadrat1()
{
	Vektor2 Quadrat[4];
	Quadrat[0] = Vektor2(50, 50);
	Quadrat[1] = Vektor2(150, 50);
	Quadrat[2] = Vektor2(150, 150);
	Quadrat[3] = Vektor2(50, 150);

	CDC* pDC = GetDC();

	Matrix2 TransMat;
	//TransMat.setTrans(200, 70);
	TransMat.setTrans(10, 0);

	CRect rect;
	GetClientRect(&rect);

	for (int anim = 0; anim < 100; anim++) {
		pDC->FillSolidRect(rect, RGB(138, 43, 226));
		// Quadrat verschieben
		for (int i = 0; i < 4; i++) {
			Quadrat[i] = TransMat * Quadrat[i];
		}
		// Quadrat malen
		pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]); 

		for (int i = 0; i < 4; i++) {
			pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
		}
		Sleep(5);
	}

}


void CChildView::OnVektorQuadratrotieren()
{
	Vektor2 Quadrat[4];
	Quadrat[0] = Vektor2(50, 50);
	Quadrat[1] = Vektor2(150, 50);
	Quadrat[2] = Vektor2(150, 150);
	Quadrat[3] = Vektor2(50, 150);

	CDC* pDC = GetDC();

	Matrix2 TransMat;
	// Quadrat verschieben in Ursprung cords 0,0
	TransMat.setTrans(-100, -100);

	// Quadrat verschieben zum Ursprung
	for (int i = 0; i < 4; i++) {
		Quadrat[i] = TransMat * Quadrat[i];
	}
	/* Quadrat malen
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int i = 0; i < 4; i++) {
		pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
	}*/

	// Rotationsmatrix anwenden im Ursprung
	Matrix2 RotMat;
	RotMat.setRotation(10);
	// Quadrat rotieren
	for (int i = 0; i < 4; i++) {
		Quadrat[i] = RotMat * Quadrat[i];
	}
	
	/* Quadrat malen
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]); 
	for (int i = 0; i < 4; i++) {
		pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
	}*/

	// Rotierte Matrix auf 100,100 verschieben
	Matrix2 TransMatReverse;
	TransMatReverse.setTrans(100, 100);
	// Quadrat verschieben
	for (int i = 0; i < 4; i++) {
		Quadrat[i] = TransMatReverse * Quadrat[i];
	}
	// Quadrat malen
	pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
	for (int i = 0; i < 4; i++) {
		pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
	}
}


void CChildView::OnVektorQuadratrotierenv2()
{
	// Höhe und Breite der Programmoberfläche auslesen
	CRect rect;
	GetClientRect(&rect);

	double windowx = rect.Width() / 2;
	double windowy = rect.Height() / 2;

	double size = 100;

	Vektor2 Quadrat[4];
	Quadrat[0] = Vektor2(windowx - size, windowy - size);
	Quadrat[1] = Vektor2(windowx + size , windowy - size);
	Quadrat[2] = Vektor2(windowx + size, windowy + size);
	Quadrat[3] = Vektor2(windowx - size, windowy + size);

	CDC* pDC = GetDC();

	Matrix2 TransMat, RotMat, TransMatReverse;
	TransMat.setTrans(-windowx, -windowy);
	RotMat.setRotation(0.1);
	TransMatReverse.setTrans(windowx, windowy);

	for (int anim = 0; anim < 500; anim++) {
		pDC->FillSolidRect(rect, RGB(138, 43, 226));
		for (int i = 0; i < 4; i++) {
			Quadrat[i] = TransMat * Quadrat[i]; // Verschieben Ursprung
			Quadrat[i] = RotMat * Quadrat[i]; // Rotieren im Ursprung
			Quadrat[i] = TransMatReverse * Quadrat[i]; // Verschieben undo
			//Quadrat[i] = TransMat*RotMat*TransMatReverse * Quadrat[i];  // Benötigt Operator Funktionsüberladung für Matrix * Matrix Operation
		}

		// Quadrat malen
		pDC->MoveTo(Quadrat[3].vek[0], Quadrat[3].vek[1]);
		for (int i = 0; i < 4; i++) {
			pDC->LineTo(Quadrat[i].vek[0], Quadrat[i].vek[1]);
		}
		Sleep(10);
		
		// Animation abbrechen, wenn Esc gedrückt
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}
}


void CChildView::OnAufgabe4W32780()
{
	CRect rect;
	GetClientRect(&rect);

	double windowx = rect.Width() / 2;
	double windowy = rect.Height() / 2;
	
	CDC* m_DC = GetDC();
	
	for (int anim = 0; anim < 500; anim++) {
		m_DC.FillSolidRect(0, 0, 500, 500, RGB(255, 255, 255));
		Sleep(10);
		RY.SetRot(winkel);
		winkel += 0.01;
		for (int i = 0; i < 8; i++) {
			wurfel[i] = P * RX * RZ * orig[i];
			double c = wurfel[i].v[3];
			wurfel[i] = T * wurfel[i] / c;
		}

		// hinten
		m_DC.MoveTo(wurfel[3].toPoint());
		for (int i = 0; i < 4; i++) {
			m_DC.LineTo(wurfel[i].toPoint());
		}
		// vorne
		m_DC.MoveTo(wurfel[7].toPoint());
		for (int i = 4; i < 8; i++) {
			m_DC.LineTo(wurfel[i].toPoint());
		}

		for (int i = 0; i < 4; i++) {
			m_DC.MoveTo(wurfel[i].toPoint());
			m_DC.LineTo(wurfel[i + 4].toPoint());
		}
		pDC->BitBlt(0, 0, windowx, windowy, &m_DC, 0, 0, SRCCOPY);

		// Animation abbrechen, wenn Esc gedrückt
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}
	
}
