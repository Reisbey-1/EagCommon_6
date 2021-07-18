/*
//=============================================================================
//
// = PROJECT
//
//     XML -- XML DataStruct
//
// = FILENAME
//
//     MddlElement.h
//
//
// = SUMMARY
//
//     Header-File für die Elementklasse, die das Element einer XML-Daten-
//     struktur bereitstellt.
//
// = AUTHOR(S)
//
//     Roland Kopetzky
//
// = COPYRIGHT
//
//     2000  Ennovatis -- All Rights Reserved
//
//
//=============================================================================
*/

#ifndef _XML_XMLELEMENT_H_
#define _XML_XMLELEMENT_H_

#include "xmldef.h"
#include <afxtempl.h> // CTypedPtrList

namespace eag 
{

//=============================================================================

//##ModelId=396A3C0900A1
class XMLSTRUCT_API CXmlAttribut : public CObject

//=============================================================================
//
// = TITLE
//
//     CXmlAttribut
//
// = CLASSTYPE
//
//     Klasse
//
//
// = DESCRIPTION
//
//     Die Klasse CXmlAttribut kapselt ein Attribut einer XML-Datenstruktur. 
//     Dabei werden der Name und der Wert gespeichert.
//
//=============================================================================
{
	// Freund-Klasse
	friend class CXmlTreeElement;
	friend class CXmlElement;
	friend class CXmlStruct;
	
public:
	//##ModelId=396A3C0900B5
	CString m_Name;
		// Attribut-Name

	//##ModelId=396A3C0900AC
	CString m_Value;
		// Attribut-Wert

	//##ModelId=396A3C0900BF
	CXmlAttribut(CString csName = _T(""),
		          CString csValue = _T(""));
};

//=============================================================================

//##ModelId=396A3C090354
class XMLSTRUCT_API CXmlElement : public CObject

//=============================================================================
//
// = TITLE
//
//     CXmlElement
//
// = CLASSTYPE
//
//     Klasse
//
//
// = DESCRIPTION
//
//     Die Klasse CXmlElement kapselt ein Element einer XML-Datei
//	   Derzeit mögliche Werte sind vom Typ CSTRING, unsigned int, BOOL oder TIME.
//
//=============================================================================
{
	// Freundklasse
	friend class CXmlTreeElement;
	friend class CXmlStruct;

protected:
	//##ModelId=396A3C09039A
	CString m_Name;
		// Name des Elements

	//##ModelId=396A3C090390
	CString m_csData;
		// Wert des Elements

	//##ModelId=396A3C090374
	CTypedPtrList<CObList, CXmlAttribut*> m_AttributList;
		// Liste mit Attributen

//
//	Methoden
//

	//##ModelId=396A3C0A002A
	CXmlElement(CString csName = _T(""));
		// Konstruktor

	//##ModelId=396A3C0A0021
	~CXmlElement();
		// Destruktor

	//##ModelId=396A3C0A0016
	int AddAttribut(CString csName, CString csValue);
		// Hinzufügen neues Attribut
		// Rückgabe:
		// Fehlervariable (0 = OK)

	//##ModelId=396A3C0A000C
	BOOL IsAttribut(CString csName);
		// Kontrolle, ob csName Attribut
		// Rückgabe:
		//   TRUE: Attribut
		//	 FALSE: kein Attribut

	//##ModelId=396A3C0903E1
	BOOL DeleteAttribut(CString csName);
		// Löschen eines Attributs
		// Rückgabe:
		//   TRUE: Löschen erfolgreich
		//	 FALSE: Löschen nicht erfolgreich
	
	//##ModelId=396A3C0903D7
	CString GetAttributValue(CString csName);
		// Liefert den Wert eines bestimmten Attributs zurück

	//##ModelId=396A3C0903CC
	int SetAttributValue(CString csName, CString csValue);
		// Setzt den Wert eines bestimmten Attributs
		// Rückgabe: Fehlercode (0 = OK)

	//##ModelId=396A3C0903C2
	int SetElementValue(CString csValue);
		// Belegt Attribut, abhängig von DataTyp
		// Rückgabe: Fehlercode (0 = OK)

	//##ModelId=396A3C0903B8
	CString GetElementValue(void);
		// Liefert den Wert eines Elements als CString 

	//##ModelId=396A3C0903AE
	CString GetElementName(void);
		// Liefert den Namen eines Elements als CString 

	//##ModelId=396A3C0903A4
	CString CutChar(CString csValue);
		// Entfernen evtl. CR-LF und Tabulatoren am Anfang und Ende eines Wertes

};

//=============================================================================

} // namespace eag

#endif // #ifndef _XML_XMLELEMENT_H_

//=============================================================================
