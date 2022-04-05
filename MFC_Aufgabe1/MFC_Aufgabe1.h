
// MFC_Aufgabe1.h: Hauptheaderdatei für die MFC_Aufgabe1-Anwendung
//
#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"       // Hauptsymbole


// CMFCAufgabe1App:
// Siehe MFC_Aufgabe1.cpp für die Implementierung dieser Klasse
//

class CMFCAufgabe1App : public CWinApp
{
public:
	CMFCAufgabe1App() noexcept;


// Überschreibungen
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementierung

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCAufgabe1App theApp;
