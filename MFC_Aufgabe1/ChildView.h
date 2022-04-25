
// ChildView.h: Schnittstelle der CChildView-Klasse
//


#pragma once


// CChildView-Fenster

class CChildView : public CWnd
{
// Konstruktion
public:
	CChildView();

// Attribute
public:

// Vorgänge
public:
	double xd_min;
	double xd_delta;
	double yd_min;
	double yd_delta;

// Überschreibungen
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void JuliaMalen();
	void MandelbrotMalen();
// Implementierung
public:
	virtual ~CChildView();

	// Generierte Funktionen für die Meldungstabellen
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAufgabe1Diagonale();
	afx_msg void OnAufgabe1Juliamenge();
	afx_msg void OnAufgabe1JuliamengeZoom();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAufgabe1Mandelbrot();
	afx_msg void OnVektorQuadrat1();
};

