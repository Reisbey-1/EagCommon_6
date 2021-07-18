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
//     Header-File für die XML-Datenstruktur
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

#ifndef _XML_XMLSTRUCT_H_
#define _XML_XMLSTRUCT_H_


//=============================================================================
// Header-Dateien
//=============================================================================

#include "XmlDef.h"
	// definitions

#include "XmlHandle.h"
	// typesafe HANDLES

#include "XmlElement.h"
	// Elemente aus Datenfile

#include "XmlProcessor.h"
	// Vereinfachter XML-Parser fuer InformationItems

#include <sstream>

namespace eag
{

//=============================================================================

//##ModelId=396A3C0D0273
class XMLSTRUCT_API CXmlTreeElement : public CObject

//=============================================================================
//
// = TITLE
//
//     CXmlTreeElement
//
// = CLASSTYPE
//
//     Klasse
//
// = DESCRIPTION
//
//     Die Klasse CXmlTreeElement bildet ein Blatt der XML-Datenstruktur
//     "Baum".
//
//=============================================================================
{
friend class CXmlStruct;

protected:
	//##ModelId=396A3C0D02EC
	CString m_Text;
		// Text-Attribut

	//##ModelId=396A3C0D02DA
	HXMLELEMENT m_Data;
		// Pointer auf Datenstruktur

	//##ModelId=396A3C0D02BB
	HXMLITEM m_Parent;
		// Pointer auf ElternItem

	//##ModelId=396A3C0D0293
	CTypedPtrList<CObList, CXmlTreeElement*> m_ItemList;
		// Liste mit Kind-Zweigen

//
//	Methoden
//

	//##ModelId=396A3C0D035A
	CXmlTreeElement(CString csText =_T(""));
		// Konstruktor

	//##ModelId=396A3C0D0350
	~CXmlTreeElement();
		// Destruktor

	//##ModelId=396A3C0D0346
	void DeleteItemList(void);
		// Löschen der ItemList

	//##ModelId=396A3C0D0332
	HXMLITEM FindItemText(CString csText);
		// Suche nach Texteintrag

	//##ModelId=396A3C0D0314
	HXMLITEM FindItemByAttribute(CString csElementName, CString csAttributName, CString csAttributValue);
		// Suche nach Element mit vorgeg. Name und Attributwert

	//##ModelId=396A3C0D0300
	HXMLITEM FindItemData(HXMLELEMENT hElement);
		// Suche nach Dateneintrag

};

//=============================================================================

//##ModelId=396A3C0600E3
class XMLSTRUCT_API CXmlStruct : public CXmlTreeElement

//=============================================================================
//
// = TITLE
//
//     CXmlStruct
//
// = CLASSTYPE
//
//     Klasse
//
//
// = DESCRIPTION
//
//     Die Klasse CXmlStruct kapselt die XML-Datenstrukrur "Baum".
//     Sie liefert Methoden zur Navigation in diesem Baum und zur Manipulierung
//     der XML-Elemente und ihrer Attribute.
//
// = EXAMPLE 
//	   Das folgende Beispiel legt die Struktur an, und liefert einen Testprint
//     eines Attributs, der Elementwerte und einer Fehlermeldung.
//
//		<Root-Element Name1="Wert1" Name2="Wert2">
//			<Kind1>Eintrag1
//			<Kind2>Eintrag2
//			<Kind3>Eintrag3
//		</Root-Element>
// 
//		{
//			HXMLITEM hNewItem;
//			HXMLITEM hNext;
//			HXMLITEM hRoot;
//			CXmlStruct TreeStruct;
//	
//			// Anlegen eines neuen Elements auf Root-Ebene
//			hRoot = TreeStruct.InsertItem("Root-Element", XML_TI_ROOT);
//			// Setzen von zwei Attributen
//			TreeStruct.AddAttribut(hRoot, "Name1", "Wert1");
//			TreeStruct.AddAttribut(hRoot, "Name2", "Wert2");
//
//			// Anlegen Kindeinträge
//			hNewItem = TreeStruct.InsertItem("Kind1", hRoot);
//			TreeStruct.SetElementValue(hNewItem,"Eintrag1");
//
//			hNewItem = TreeStruct.InsertItem("Kind2", hRoot);
//			TreeStruct.SetElementValue(hNewItem,"Eintrag2");
//	
//			hNewItem = TreeStruct.InsertItem("Kind3", hRoot);
//			TreeStruct.SetElementValue(hNewItem,"Eintrag3");
//
//			// Testausgabe des zweiten Attributs und der drei Eintraege 
//			hRoot = TreeStruct.GetRootItem();
//
//			AfxMessageBox("Attribut Name2: "+TreeStruct.GetAttributValue(hRoot, "Name2"));
//
//			hNext = TreeStruct.GetChildItem(hRoot);
//			while (hNext != NULL)
//			{
//				AfxMessageBox("Eintrag: "+TreeStruct.GetElementValue(hNext));
//				hNext = TreeStruct.GetNextSiblingItem(hNext);
//			}
//
//			// Löschen aller Einträge
//			TreeStruct.DeleteAllItems();
//
//			// Test der Fehlerausgabe 
//			if (TreeStruct.GetRootItem() == NULL)
//				AfxMessageBox(TreeStruct.GetErrorString());
//		}
//
//=============================================================================
{

protected:
	
	//##ModelId=396A3C06013D
	int m_ErrorID;
		// Fehlervaraiable

	//##ModelId=396A3C060133
	CString m_ErrorString;
		// CString mit Fehlertext

	//##ModelId=396A3C060121
	CStringArray m_caIncludeDir;
		// zusätzliche Include-Verzeichnisse

	//##ModelId=396A3C06010B
	CTypedPtrList<CObList, CXmlElement*> m_ElementList;
		// Liste mit Elementen aus Datenfile

	//##ModelId=396A3C0603A1
	HXMLELEMENT GetItemData(HXMLITEM hItem);
		// liefert Daten-Attribut eines Item

	//##ModelId=396A3C06038D
	BOOL SetItemData(HXMLITEM hItem, HXMLELEMENT hData);
		// setzt Daten-Attribut eines Item

	//##ModelId=396A3C060378
	HXMLITEM GetItem(HXMLELEMENT hElement);
		// liefert Eintrag mit bestimmten Dateneintrag

	//##ModelId=396A3C060364
	BOOL SetItemText(HXMLITEM hItem, CString & csText);
		// setzt Text eines Item

	//##ModelId=396A3C060332
	int WriteDataLine(FILE *pFile, HXMLITEM hParent, int nLevel);
		// schreibt eine einzelne Datenzeile in theFile

	//##ModelId=396A3C060347
	/// md int WriteDataLine(std::ostream& stream, HXMLITEM hParent, int nLevel);
	int WriteDataLine(std::wostream& stream, HXMLITEM hParent, int nLevel);

	int WriteDataLine(CString& rStr, HXMLITEM hParent, int nLevel);

public:
	int WriteDataString(CString& rString);
	//##ModelId=396A3C060329
	CXmlStruct();
		// Konstruktor

	//##ModelId=396A3C060328
	~CXmlStruct();
		// Destruktor

//
// Zugriffsmethoden zur Navigation durch Baumstruktur
//

	//##ModelId=396A3C06031E
	HXMLITEM GetRootItem();
		// liefert Pointer auf ersten Eintrag

	//##ModelId=396A3C060314
	CString GetItemText(HXMLITEM hItem);
		// liefert Text eines Item (entspricht dem Elementnamen)

	//##ModelId=396A3C06030A
	HXMLITEM GetParentItem(HXMLITEM hItem);
		// liefert Eltern-Item

	//##ModelId=396A3C0602E2
	HXMLITEM GetChildItem(HXMLITEM hItem);
		// liefert erstes Kind-Item

	//##ModelId=396A3C0602F6
	HXMLITEM GetChildItem(HXMLITEM hItem, CString & csElementName);
		// liefert ersten Kind-Eintrag, dessen Elementname csElementName entspricht

	//##ModelId=396A3C0602A5
	HXMLITEM GetNextSiblingItem(HXMLITEM hItem);
		// liefert nächsten Item einer Hierarchie-Stufe

	//##ModelId=396A3C0602B0
	HXMLITEM GetNextSiblingItem(HXMLITEM hItem, CString & csElementName);
		// liefert nächsten Item einer Hierarchie-Stufe mit vorgegebenen Elementnamen
		// oder NULL

	//##ModelId=396A3C0602C3
	HXMLITEM GetNextSiblingItem(HXMLITEM hItem, CString & csElementName, CString & csAttributName, CString & csAttributValue);
		// liefert nächsten Item einer Hierarchie-Stufe mit vorgegebenen Elementnamen und Attributwerten
		// oder NULL

	//##ModelId=396A3C060382
	HXMLITEM GetItem(CString & csText);
		// liefert Eintrag mit bestimmtem Text

	//##ModelId=396A3C060291
	HXMLITEM FindItemByAttribute(CString csElementName, CString csAttributName, CString csAttributValue);
		// liefert Eintrag mit bestimmtem Attribut und Wert

	//##ModelId=396A3C06027D
	HXMLITEM GetNextItem(HXMLITEM hItem, unsigned int nCode);
		// liefert nächsten Item:
		// nCode kann dabei sein:
		//	XML_TGN_CHILD:	Erster Kind-Eintrag
		//	XML_TGN_NEXT:	Nächster Eintrag einer Ebene	
		//	XML_TGN_PARENT:	Eltern-Item
		//	XML_TGN_ROOT:	Erster Eintrag einer Ebene

	//##ModelId=396A3C06026A
	BOOL ItemHasChildren(HXMLITEM hItem);
		// TRUE, wenn Kind-Items vorhanden

	//##ModelId=396A3C060255
	HXMLITEM InsertItem(CString & csText,
					    HXMLITEM hParent = XML_TI_ROOT);
		// Einfügen neuer Eintrag

	//##ModelId=396A3C06024B
	BOOL DeleteItem(HXMLITEM hItem);
		// Löschen eines Eintrags mit allen Kind-items

	//##ModelId=396A3C060238
	BOOL DeleteAllItems(void);
		// Löschen aller Einträge

//
// Zugriffsmethoden auf Elemente und Attribute
//

	int CountAttributs(HXMLITEM hItem);
	CString GetAttributValue(HXMLITEM hItem, int nPos);
	CString GetAttributName(HXMLITEM hItem, int nPos);

	//##ModelId=396A3C060223
	int AddAttribut(HXMLITEM hItem, CString & csName, CString & csValue);
		// Hinzufügen neues Attribut
		// Rückgabe:
		// Fehlervariable (0 = OK)

	//##ModelId=396A3C06020F
	BOOL IsAttribut(HXMLITEM hItem, CString & csName);
		// Kontrolle, ob csName Attribut
		// Rückgabe:
		//   TRUE: Attribut
		//	 FALSE: kein Attribut

	//##ModelId=396A3C0601FB
	BOOL DeleteAttribut(HXMLITEM hItem, CString & csName);
		// Löschen eines Attributs
		// Rückgabe:
		//   TRUE: Löschen erfolgreich
		//	 FALSE: Löschen nicht erfolgreich

	//##ModelId=396A3C0601E7
	CString GetAttributValue(HXMLITEM hItem, CString & csName);
		// Liefert den Wert eines bestimmten Attributs zurück

	//##ModelId=396A3C0601D3
	int SetAttributValue(HXMLITEM hItem, CString & csName, CString & csValue);
		// Setzt den Wert eines bestimmten Attributs
		// Rückgabe: Fehlercode (0 = OK)

	int SetAttributValue(HXMLITEM hItem, CString & csName, int nValue);
		// Setzt den Wert eines bestimmten Attributs
		// Rückgabe: Fehlercode (0 = OK)

	//##ModelId=396A3C0601B6
	int SetElementValue(HXMLITEM hItem, CString & csValue);
		// Belegt Elementwert
		// Rückgabe: Fehlercode (0 = OK)

	//##ModelId=396A3C0601AB
	CString GetElementValue(HXMLITEM hItem);
		// Liefert den Wert eines Elements als CString 

	//##ModelId=396A3C0601A1
	CString GetElementName(HXMLITEM hItem);
		// Liefert den Namen eines Elements als CString 


//
//	Daten Ein- und Auslesen
//
	//##ModelId=396A3C06018D
	int ReadDataFile(CString  & csInputFile, BOOL bAdd = FALSE);
		// Liest Datenfile csInputFile ein und belegt Datenstruktur
		// Ist bAdd = TRUE, werden die neuen Daten ergänzt,
		// ist bAdd = FALSE, werden die alten Daten überschrieben

	//##ModelId=396A3C060179
	int ReadDataString(CString & csInputString, BOOL bAdd = FALSE);
		// Liest String csInputString ein und belegt Datenstruktur
		// Ist bAdd = TRUE, werden die neuen Daten ergänzt,
		// ist bAdd = FALSE, werden die alten Daten überschrieben

	//##ModelId=396A3C06016F
	int WriteDataFile(CString & csOutputFile);
		// Schreibt XML-Datenfile

	//##ModelId=396A3C060165
	int	WriteDataStream(std::wostream& outStream);

//
//	Fehlerrückgabe
//
	//##ModelId=396A3C06015B
	int GetError(void);
	//##ModelId=396A3C060147
	CString GetErrorString(void);

};

//=============================================================================

} // namespace eag

#endif // #ifndef _XML_XMLSTRUCT_H_

//=============================================================================
