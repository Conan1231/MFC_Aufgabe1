
// ChildView.cpp: Implementierung der CChildView-Klasse
//
#include <math.h>

#include "pch.h"
#include "framework.h"
#include "MFC_Aufgabe1.h"
#include "ChildView.h"
#include "Vektor2.h"
#include "Vektor3.h"
#include <gl/GL.h>
#include <gl/GLU.h>

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
	ON_COMMAND(ID_AUFGABE5_CUBEGL, &CChildView::OnAufgabe5Cubegl)
	ON_COMMAND(ID_AUFGABE6_QUADRIC, &CChildView::OnAufgabe6Quadric)
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
	
	double size = 99;
	int diff = 0;

	Vektor3 cube[8];
	Matrix3 RotCube, TransCube, TransCubeReverse;

	cube[0] = Vektor3(windowx - size, windowy - size, 0);
	cube[1] = Vektor3(windowx + size, windowy - size, 0);
	cube[2] = Vektor3(windowx + size, windowy + size, 0);
	cube[3] = Vektor3(windowx - size, windowy + size, 0);
	cube[4] = Vektor3(windowx - size + diff, windowy - size + diff, size * 2);
	cube[5] = Vektor3(windowx + size + diff, windowy - size + diff, size * 2);
	cube[6] = Vektor3(windowx + size + diff, windowy + size + diff, size * 2);
	cube[7] = Vektor3(windowx - size + diff, windowy + size + diff, size * 2);


	CDC* m_DC = GetDC();
	//CDC* p_DC = GetDC();
	
	for (int anim = 0; anim < 90000; anim++) {
		m_DC->FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(131, 89, 216));
		Sleep(10);
		
		/*RY.SetRot(winkel);
		winkel += 0.01;
		for (int i = 0; i < 8; i++) {
			wurfel[i] = P * RX * RZ * orig[i];
			double c = wurfel[i].v[3];
			wurfel[i] = T * wurfel[i] / c;
		}*/

		// Rotieren
		TransCube.setTrans(-windowx, -windowy);
		RotCube.setRotationX(0.01);


		TransCubeReverse.setTrans(windowx, windowy);

		for (int i = 0; i < 8; i++) {
			cube[i] = TransCube * cube[i]; // Verschieben Ursprung
			cube[i] = RotCube * cube[i]; // Rotieren im Ursprung
			cube[i] = TransCubeReverse * cube[i]; // Verschieben undo
		}		
		RotCube.setRotationY(0.01);
		for (int i = 0; i < 8; i++) {
			cube[i] = TransCube * cube[i]; // Verschieben Ursprung
			cube[i] = RotCube * cube[i]; // Rotieren im Ursprung
			cube[i] = TransCubeReverse * cube[i]; // Verschieben undo
		}		
		RotCube.setRotationZ(0.01);
		for (int i = 0; i < 8; i++) {
			cube[i] = TransCube * cube[i]; // Verschieben Ursprung
			cube[i] = RotCube * cube[i]; // Rotieren im Ursprung
			cube[i] = TransCubeReverse * cube[i]; // Verschieben undo
		}

		// hinten
		m_DC->MoveTo(cube[3].vek[0], cube[3].vek[1]);
		//sm_DC->FillSolidRect(cube[3].vek[0], cube[3].vek[1], cube[4].vek[0], cube[4].vek[1] ,RGB(255, 255, 255));
		for (int i = 0; i < 4; i++) {
			m_DC->LineTo(cube[i].vek[0], cube[i].vek[1]);
		}
		// vorne
		m_DC->MoveTo(cube[7].vek[0],cube[7].vek[1]); // vek[0] -> x-Koordinate | vek[1] -> y-Koordinate
		for (int i = 4; i < 8; i++) {
			m_DC->LineTo(cube[i].vek[0], cube[i].vek[1]);
		}

		for (int i = 0; i < 4; i++) {
			m_DC->MoveTo(cube[i].vek[0], cube[i].vek[1]);
			m_DC->LineTo(cube[i+4].vek[0], cube[i+4].vek[1]);
		}
		//pDC->BitBlt(0, 0, windowx, windowy, &m_DC, 0, 0, SRCCOPY);

		// Animation abbrechen, wenn Esc gedrückt
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}
	
}

// Aufgabe 5 OpenGL

void CChildView::GLInit(int Breite, int Hoehe, int Modus)
{
	static HDC         hdc;
	static HGLRC       hglrc;
	int         iPixelFormat;
	HWND hwnd = GetSafeHwnd();


	static PIXELFORMATDESCRIPTOR pfd =	//pfd legt das Aussehen der Szene fest
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,						//Versionsnummer
		PFD_DRAW_TO_WINDOW |	//pfd muss Windows unterstützen
		PFD_SUPPORT_OPENGL |	//pfd muss OpenGL unterstützen
		PFD_DOUBLEBUFFER ,		//Doppelpuffer wird unterstützt
		PFD_TYPE_RGBA,			//RGBA-Farbformat auswählen
		32,						//Bit-Farbtiefe
		0, 0, 0, 0, 0, 0,		//Farbbits werden ignoriert
		0,						//kein Alphapuffer
		0,						//Schiebebit ignoriert
		0,						//kein Ansammlungspuffer
		0, 0, 0, 0,				//Ansammlungsbits werden ignoriert
		16,						//16bit Z-Puffer (Tiefenpuffer)
		16,						//Masken-Puffer
		0,						//keinen Hilfs-Puffer
		PFD_MAIN_PLANE,			//Festlegung der Zeichenebene (Hauptebene)
		0,						//reserviert
		0, 0, 0					//Ebenenmasken werden ignoriert 
	};
	CDC* pDC = GetDC();
	CRect gesamt, client;
	GetWindowRect(&gesamt);
	GetClientRect(&client);
	int diff_x = gesamt.Width() - client.Width();
	int diff_y = gesamt.Height() - client.Height();
	m_height = Hoehe;
	m_width = Breite;

	switch (Modus)
	{
	case 1:  // Modus 1 -> Initialisierung

		// ---------- Fenstergröße
		GetParent()->SetWindowPos(&wndTop,
			50, 50, m_height + diff_x, m_width + diff_y, 0);
		//		GetParent()->ShowWindow(SW_NORMAL);
		GetParent()->RedrawWindow();
		// ------ Device Context
		hdc = pDC->GetSafeHdc();

		// ------ Pixelformat einstellen (OpenGL-fähig)
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);

		// ----  Rendering-Context erstellen und zuweisen
		hglrc = wglCreateContext(hdc);
		if (hglrc == NULL) { SetWindowText(CString("Fehler beim RC !")); Sleep(2000); }
		wglMakeCurrent(hdc, hglrc);
		break;

	case 0:  // Modus 0 -> Beenden
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hglrc);

		ReleaseDC(pDC);
		break;
	}
	return;

}

void CChildView::Bunter_Einheitswuerfel()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);          // grün bei z = -0.5
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(1, 0, 0);        // rot bei z = 0.5
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	glColor3f(1, 0.75, 0.25);  // orange bei y = -0.5
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glColor3f(0, 0, 1);          // blau bei y = 0.5
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glColor3f(1, 0, 1);          // lila bei x =  0.5
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	glColor3f(1, 1, 0);          // gelb bei x = -0.5
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void CChildView::Achsenkreuz(float l)
{
	GLfloat Pfeil = (float)0.05;

	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(-l, 0, 0);  // Achsen
	glVertex3f(l, 0, 0);

	glVertex3f(0, -l, 0);
	glVertex3f(0, l, 0);

	glVertex3f(0, 0, -l);
	glVertex3f(0, 0, l);

	glVertex3f(l, 0, 0);  // Pfeile
	glVertex3f(l - Pfeil, Pfeil, 0);

	glVertex3f(l, 0, 0);
	glVertex3f(l - Pfeil, -Pfeil, 0);

	glVertex3f(0, l, 0);  // Pfeile
	glVertex3f(0, l - Pfeil, Pfeil);

	glVertex3f(0, l, 0);
	glVertex3f(0, l - Pfeil, -Pfeil);

	glVertex3f(0, 0, l);  // Pfeile
	glVertex3f(Pfeil, 0, l - Pfeil);

	glVertex3f(0, 0, l);
	glVertex3f(-Pfeil, 0, l - Pfeil);
	glEnd();
}

void CChildView::OnAufgabe5Cubegl()
{
	GLInit(700, 700, 1);
	glClearColor(0.5,0.5,0.5,0); // Setzen der Farbe, die beim Clearen verwendet wird [R,G,B,alpha-Kanal = 1 solid; 0 transparent] 

	glMatrixMode(GL_PROJECTION); // Hier werden Projektionen organisiert
	glLoadIdentity();
								 
	//glOrtho(-1, 1, -1, 1, 1.5, 6);
	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0,	// Augpunkt
			  0.0, 0.0, 0.0,	// Zielpunkt
			  0.0, 1.0, 0.0);	// Up-Vektor | Winkel wie auf Objekt geschaut wird (z.B. Kopf schräg halten)


	for (int anim = 0; anim < 1000; anim++) {
		
		glEnable(GL_DEPTH_TEST);	// Tiefe hinzufügen
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW); // Transformationen organisieren

		glLoadIdentity(); // Zurücksetzen auf Standardeinstellungen, Laden der Identitätsmatrix
		Achsenkreuz(1.2);
		//glRotated(anim, 0.0, 1.0, 0.0);
		//glRotated(-anim, 1.0, 0.0, 0.0);
		Bunter_Einheitswuerfel();

		
		// Gitter um das Gebilde
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glScaled(1.2, 1.2, 1.2);
		Bunter_Einheitswuerfel();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// Würfel Pickel 1 rechts
		glLoadIdentity();
		glTranslated(0.6, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 1.0, 0.0, 0.0);
		Bunter_Einheitswuerfel();

		// Würfel Pickel 2 links
		glLoadIdentity();
		glTranslated(-0.6, 0, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 1.0, 0.0, 0.0);
		Bunter_Einheitswuerfel();

		// Würfel Pickel 3 Oben
		glLoadIdentity();
		glTranslated(0, 0.6, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 1.0, 0.0);
		Bunter_Einheitswuerfel();

		// Würfel Pickel 4 Unten
		glLoadIdentity();
		glTranslated(0, -0.6, 0);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 1.0, 0.0);
		Bunter_Einheitswuerfel();
		
		//Würfel Pickel 5 vorne
		glLoadIdentity();
		glTranslated(0, 0.0, 0.6);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 0.0, 1.0);
		Bunter_Einheitswuerfel();

		// Würfel Pickel 6 hinten
		glLoadIdentity();
		glTranslated(0, 0, -0.6);
		glScaled(0.5, 0.5, 0.5);
		glRotated(anim, 0.0, 0.0, 1.0);
		Bunter_Einheitswuerfel();

		Sleep(10);
		SwapBuffers(wglGetCurrentDC());

		// Animation abbrechen, wenn Esc gedrückt
		if (GetAsyncKeyState(VK_ESCAPE)) {
			break;
		}
	}
	GLInit(0, 0, 0);
}


void CChildView::OnAufgabe6Quadric()
{
	float colors[24][10] = { {0.0215,0.1745,0.0215,0.07568,0.61424,0.07568,0.633,0.727811,0.633,0.6  },   {0.135,0.2225,0.1575,0.54,0.89,0.63,0.316228,0.316228,0.316228,0.1  },   {0.05375,0.05,0.06625,0.18275,0.17,0.22525,0.332741,0.328634,0.346435,0.3  },   {0.25,0.20725,0.20725,1,0.829,0.829,0.296648,0.296648,0.296648,0.088  },   {0.1745,0.01175,0.01175,0.61424,0.04136,0.04136,0.727811,0.626959,0.626959,0.6  },   {0.1,0.18725,0.1745,0.396,0.74151,0.69102,0.297254,0.30829,0.306678,0.1  },   {0.329412,0.223529,0.027451,0.780392,0.568627,0.113725,0.992157,0.941176,0.807843,0.21794872  },   {0.2125,0.1275,0.054,0.714,0.4284,0.18144,0.393548,0.271906,0.166721,0.2  },   {0.25,0.25,0.25,0.4,0.4,0.4,0.774597,0.774597,0.774597,0.6  },   {0.19125,0.0735,0.0225,0.7038,0.27048,0.0828,0.256777,0.137622,0.086014,0.1  },   {0.24725,0.1995,0.0745,0.75164,0.60648,0.22648,0.628281,0.555802,0.366065,0.4  },   {0.19225,0.19225,0.19225,0.50754,0.50754,0.50754,0.508273,0.508273,0.508273,0.4  },   {0,0,0,0.01,0.01,0.01,0.5,0.5,0.5,0.25  },
{0,0.1,0.06,0,0.50980392,0.50980392,0.50196078,0.50196078,0.50196078,0.25  },   {0,0,0,0.1,0.35,0.1,0.45,0.55,0.45,0.25  },   {0,0,0,0.5,0,0,0.7,0.6,0.6,0.25  },   {0,0,0,0.55,0.55,0.55,0.7,0.7,0.7,0.25  },   {0,0,0,0.5,0.5,0,0.6,0.6,0.5,0.25  },   {0.02,0.02,0.02,0.01,0.01,0.01,0.4,0.4,0.4,0.078125  },   {0,0.05,0.05,0.4,0.5,0.5,0.04,0.7,0.7,0.078125  },   {0,0.05,0,0.4,0.5,0.4,0.04,0.7,0.04,0.078125  },   {0.05,0,0,0.5,0.4,0.4,0.7,0.04,0.04,0.078125  },   {0.05,0.05,0.05,0.5,0.5,0.5,0.7,0.7,0.7,0.078125  },   {0.05,0.05,0,0.5,0.5,0.4,0.7,0.7,0.04,0.078125  } };
	GLInit(1000, 1000, 1);
	glClearColor(0.1f, 0.0f, 0.1f, 0); // Setzen der Farbe, die beim Clearen verwendet wird ; Dark purple (0.1f, 0.0f, 0.1f)

	glMatrixMode(GL_PROJECTION); // Hier werden Projektionen organisiert
	glLoadIdentity();

	glFrustum(-1, 1, -1, 1, 1.5, 6);
	gluLookAt(1.0, 1.0, 3.0,	// Augpunkt
		0.0, 0.0, 0.0,	// Zielpunkt
		0.0, 1.0, 0.0);	// Up-Vektor | Winkel wie auf Objekt geschaut wird (z.B. Kopf schräg halten)

	glEnable(GL_DEPTH_TEST);	// Tiefe hinzufügen
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); // Transformationen organisieren
	glLoadIdentity();

	GLUquadricObj* pquadric = gluNewQuadric();
	gluQuadricDrawStyle(pquadric, GLU_FILL);

	// rubber ball right
	glTranslated(1, 0, 0); 
	material_v2(colors[4]); // ruby
	gluSphere(pquadric, 0.5, 20, 20);
	glPopMatrix();

	// rubber ball left
	glPushMatrix();
	glTranslated(-1, 0, 0);
	material(0.05, 0.05, 0.0, 0.5, 0.5, 0.4, 0.7, 0.7, 0.04, .078125); // yellow
	gluSphere(pquadric, 0.5, 20, 20);
	glPopMatrix();

	// ball left left
	glPushMatrix();
	glTranslated(-2, 0, 0);
	material_v2(colors[20]);
	gluSphere(pquadric, 0.5, 20, 20);
	glPopMatrix();

	// black cylinder left
	glPushMatrix();
	//material(0.05	,0.05	,0.0	,0.5	,0.5	,0.4	,0.7	,0.7	,0.04	,.078125); 
	material_v2(colors[4]);
	gluCylinder(pquadric, 0.5, 0.5, 0.6, 20, 10);
	glPopMatrix();

	// black cylinder left
	glPushMatrix();
	glTranslated(-1, 0, 0);
	material_v2(colors[4]);
	gluCylinder(pquadric, 0.5, 0.5, 0.6, 20, 10);
	glPopMatrix();

	// black cylinder green
	glPushMatrix();
	glTranslated(-2, 0, 0);
	material_v2(colors[4]);
	gluCylinder(pquadric, 0.5, 0.5, 0.6, 20, 10);
	glPopMatrix();


	SwapBuffers(wglGetCurrentDC());


	GLInit(0, 0, 0);
}

void CChildView::material(float AmatR, float AmatG, float AmatB, float DmatR, float DmatG, float DmatB, float SmatR, float SmatG, float SmatB, float sh) {
	GLfloat Ambient[4] = { AmatR,AmatG,AmatB,1 };
	GLfloat Diffuse[4] = { DmatR,DmatG,DmatB,1 };
	GLfloat Specular[4] = { SmatR,SmatG,SmatB,1 };
	
	GLfloat shininess = sh*128;
	glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);

	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void CChildView::material_v2(float colors[10]) {
	GLfloat Ambient[4] = { colors[0], colors[1], colors[2], 1 };
	GLfloat Diffuse[4] = { colors[3], colors[4], colors[5], 1 };
	GLfloat Specular[4] = { colors[6], colors[7], colors[8], 1 };

	GLfloat shininess = 128 * colors[9]; //0-128
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

}
/*
* 0: emerald
* 1: jade
* 2: obsidian
* 3: pearl
* 4: ruby
* 5: turquoise
* 6: brass
* 7: bronze
* 8: chrome
* 9: copper
* 10: gold
* 11: silver
* 12: black plastic
* 13: cyan plastic
* 14: green plastic
* 15: red plastic
* 16: white plastic
* 17: yellow plastic
* 18: black rubber
* 19: cyan rubber
* 20: green rubber
* 21: red rubber:
* 22: white rubber:
* 23: yellow rubber
*/