// stdafx.h : Include-Datei für Standard-System-Include-Dateien,
//  oder projektspezifische Include-Dateien, die häufig benutzt, aber
//      in unregelmäßigen Abständen geändert werden.
//

#if !defined(AFX_STDAFX_H__E361E826_110B_11D4_BF48_006008579BB9__INCLUDED_)
#define AFX_STDAFX_H__E361E826_110B_11D4_BF48_006008579BB9__INCLUDED_


#define WINVER 0x0700
#define _WIN32_WINNT _WIN32_WINNT_MAXVER

#define VC_EXTRALEAN		// Selten verwendete Teile der Windows-Header nicht einbinden
#define _ALLOW_RTCc_IN_STL

#include <afxwin.h>         // MFC-Kern- und -Standardkomponenten
#include <afxext.h>         // MFC-Erweiterungen
/*
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE-Klassen
#include <afxodlgs.h>       // MFC OLE-Dialogfeldklassen
#include <afxdisp.h>        // MFC Automatisierungsklassen 
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC-Datenbankklassen
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO-Datenbankklassen
#endif // _AFX_NO_DAO_SUPPORT
*/
#include <afxdtctl.h>		// MFC-Unterstützung für allgemeine Steuerelemente von Internet Explorer 4
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC-Unterstützung für gängige Windows-Steuerelemente
#endif // _AFX_NO_AFXCMN_SUPPORT
/*
#include <atlbase.h>
#include <stdlib.h>

template class __declspec(dllimport) CStringT<TCHAR, StrTraitMFC<TCHAR, ChTraitsCRT<TCHAR> > >;
template class __declspec(dllimport) CSimpleStringT<TCHAR>;
*/
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_STDAFX_H__E361E826_110B_11D4_BF48_006008579BB9__INCLUDED_)
