// MddlStruct Implementation File
//

#include "stdafx.h"
#include "XmlStruct.h"

/////////////////////////////////////////////////////////////////////////////
// namespace eag

namespace eag
{

// ==========================================================================
// CXmlTreeElement

// Konstruktor

//##ModelId=396A3C0D035A
CXmlTreeElement::CXmlTreeElement(CString csText)   // = ""
{
	m_Text = csText;
	m_Data = 0;
	m_Parent = 0;
}

// Destruktor

//##ModelId=396A3C0D0350
CXmlTreeElement::~CXmlTreeElement()
{
	// clean up
	DeleteItemList();
}

// Löschen der Liste

//##ModelId=396A3C0D0346
void CXmlTreeElement::DeleteItemList(void)
{
	// Rekursion, bis alle Items gelöscht
	while (!m_ItemList.IsEmpty())
	{
		m_ItemList.GetHead()->DeleteItemList();
		delete m_ItemList.GetHead();
		m_ItemList.RemoveHead();
	}
}

// Suche nach Texteintrag

//##ModelId=396A3C0D0332
HXMLITEM CXmlTreeElement::FindItemText(CString csText)
{
	HXMLITEM hFound;

	// Schleife über die Pointer-Liste
	for( POSITION pos=m_ItemList.GetHeadPosition(); pos != NULL; m_ItemList.GetNext(pos))
	{
		if ( m_ItemList.GetAt(pos)->m_Text == csText )
			return (DWORD)m_ItemList.GetAt(pos);

		hFound = m_ItemList.GetAt(pos)->FindItemText(csText);
		if (hFound != NULL)
			return hFound;
	}

	return NULL;
}

// Suche nach Element mit vorgeg. Name und Attributwert
//##ModelId=396A3C0D0314
HXMLITEM CXmlTreeElement::FindItemByAttribute(CString csElementName, CString csAttributName, CString csAttributValue)
{
	HXMLITEM hFound;

	// Iterative Suche
	for( POSITION pos=m_ItemList.GetHeadPosition(); pos != NULL; m_ItemList.GetNext(pos))
	{
		if ( m_ItemList.GetAt(pos)->m_Text == csElementName )
		{
			CXmlElement* ListElement = (CXmlElement*)m_ItemList.GetAt(pos)->m_Data.Value();
			if ( ListElement->IsAttribut(csAttributName) ) {
				if ( ListElement->GetAttributValue(csAttributName) == csAttributValue ) {
					return (DWORD)m_ItemList.GetAt(pos);
				}
			}
		}
		
		hFound = m_ItemList.GetAt(pos)->FindItemByAttribute(csElementName,csAttributName,csAttributValue);
		if (hFound != NULL)
			return hFound;
	}

	return NULL;
}

// Suche nach Dateneintrag

//##ModelId=396A3C0D0300
HXMLITEM CXmlTreeElement::FindItemData(HXMLELEMENT hElement)
{
	HXMLITEM hFound;

	// check handle
	if ( !hElement.isValid() ) 
		return NULL;

	// Schleife über die Pointer-Liste
	for( POSITION pos=m_ItemList.GetHeadPosition(); pos != NULL; m_ItemList.GetNext(pos))
	{
		if ( m_ItemList.GetAt(pos)->m_Data == hElement )
			return (DWORD)m_ItemList.GetAt(pos);
		
		hFound = m_ItemList.GetAt(pos)->FindItemData(hElement);
		if (hFound != NULL)
			return hFound;
	}

	return NULL;
}

// ==========================================================================
// CXmlStruct

// Konstruktor

//##ModelId=396A3C060329
CXmlStruct::CXmlStruct()
{
	m_Text.Format(L"ROOT");
	m_ErrorID		= 0;
	m_ErrorString.Format(L"");
}

// Destruktor

//##ModelId=396A3C060328
CXmlStruct::~CXmlStruct()
{
	// Löschen der Element-Liste
	while (!m_ElementList.IsEmpty())
	{
		delete m_ElementList.GetHead();
		m_ElementList.RemoveHead();
	}
}

// ==========================================================================
// protected Methoden
// ==========================================================================

// liefert Daten-Attribut eines Item

//##ModelId=396A3C0603A1
HXMLELEMENT CXmlStruct::GetItemData(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		return pElement->m_Data;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
}

// Setzt Daten eines Item

//##ModelId=396A3C06038D
BOOL CXmlStruct::SetItemData(HXMLITEM hItem, HXMLELEMENT hData)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() || !hData.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		pElement->m_Data = hData;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return FALSE;
	}
	
	return TRUE;
}

// liefert Eintrag mit Elementhandle

//##ModelId=396A3C060378
HXMLITEM CXmlStruct::GetItem(HXMLELEMENT hElement)
{
	HXMLITEM hFound;

	// check handle
	if ( !hElement.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	hFound = FindItemData(hElement);
	
	return hFound;
}

// ==========================================================================
// Zugriffsmethoden auf Baumstruktur
// ==========================================================================

// Liefert handle auf Root-Item

//##ModelId=396A3C06031E
HXMLITEM CXmlStruct::GetRootItem()
{
	if (m_ItemList.GetCount() > 0)
	{
		return (DWORD)m_ItemList.GetHead();
	}
	else
	{
		m_ErrorID = XML_ERROR_TREE_EMPTY;
		return NULL;
	}
}

// liefert Text eines Item

//##ModelId=396A3C060314
CString CXmlStruct::GetItemText(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		return pElement->m_Text;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}
}

// Setzt Text eines Item

//##ModelId=396A3C060364
BOOL CXmlStruct::SetItemText(HXMLITEM hItem, CString & csText)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		pElement->m_Text = csText;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return FALSE;
	}

	return TRUE;
}

// liefert Adresse des Eltern-Item

//##ModelId=396A3C06030A
HXMLITEM CXmlStruct::GetParentItem(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		return pElement->m_Parent;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
}

// Liefert ersten Eintrag auf Kind-Item

//##ModelId=396A3C0602E2
HXMLITEM CXmlStruct::GetChildItem(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
		
	try
	{
		if (pElement->m_ItemList.GetCount() > 0)
		{
			return (DWORD)pElement->m_ItemList.GetHead();
		} else {
			m_ErrorID = XML_ERROR_LIST_EMPTY;
			return NULL;
		}
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
	
}

// Liefert ersten Eintrag auf Kind-Item, sofern Elementname passt

//##ModelId=396A3C0602F6
HXMLITEM CXmlStruct::GetChildItem(HXMLITEM hItem, CString & csElementName)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();
	CXmlElement *ListElement;
	HXMLITEM hElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	// SGML nicht Case-Sensitiv !!!
	csElementName.MakeUpper();

	try
	{
		if (pElement->m_ItemList.GetCount() > 0)
		{
			hElement = (DWORD)pElement->m_ItemList.GetHead();
			ListElement = (CXmlElement*)GetItemData(hElement).Value();

			if ( ListElement->GetElementName() == csElementName )
				return hElement;
			else
				return GetNextSiblingItem(hElement, csElementName);
		}
		else
		{
			m_ErrorID = XML_ERROR_LIST_EMPTY;
			return NULL;
		}
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
	
}

// Liefert nächsten Eintrag einer Ebene

//##ModelId=396A3C0602A5
HXMLITEM CXmlStruct::GetNextSiblingItem(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();
	CXmlTreeElement* pParent = NULL;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		// Eltern-Item
		if (pElement->m_Parent == NULL)
			pParent = this;
		else
			pParent = (CXmlTreeElement*)pElement->m_Parent.Value();

		// Position in Liste
		POSITION pos = pParent->m_ItemList.Find(pElement);
		pParent->m_ItemList.GetNext(pos);

		if (pos != NULL)
			return (DWORD)pParent->m_ItemList.GetAt(pos);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	return NULL;
}

// Liefert nächsten Eintrag einer Ebene mit dem Elementnamen csElementName 

//##ModelId=396A3C0602B0
HXMLITEM CXmlStruct::GetNextSiblingItem(HXMLITEM hItem, CString & csElementName)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();
	CXmlTreeElement* pParent = NULL;
	CXmlElement *ListElement;
	HXMLITEM hElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	// SGML nicht Case-Sensitiv !!!
	csElementName.MakeUpper();

	hElement = GetNextSiblingItem(hItem);
	while ( hElement != NULL ) {

		// Vergleiche Element. Wenn Name identisch => Rückgabe
		ListElement = (CXmlElement*)GetItemData(hElement).Value();
		if ( ListElement->GetElementName() == csElementName )
			return hElement;

		// nächstes Element
		hElement = GetNextSiblingItem(hElement);
	}

	return NULL;
}

// Liefert nächsten Eintrag einer Ebene mit dem Elementnamen csElementName und dem entsprechenden Attributwert

//##ModelId=396A3C0602C3
HXMLITEM CXmlStruct::GetNextSiblingItem(HXMLITEM hItem, CString & csElementName, CString & csAttributName, CString & csAttributValue)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();
	CXmlTreeElement* pParent = NULL;
	CXmlElement *ListElement;
	HXMLITEM hElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	// SGML nicht Case-Sensitiv !!!
	csElementName.MakeUpper();
	csAttributName.MakeUpper();

	hElement = GetNextSiblingItem(hItem);
	while ( hElement != NULL ) {

		// Vergleiche Element. Wenn Name und Attributwert identisch => Rückgabe
		ListElement = (CXmlElement*)GetItemData(hElement).Value();
		if ( ListElement->GetElementName() == csElementName ) {
			if ( ListElement->IsAttribut(csAttributName) ) {
				if ( ListElement->GetAttributValue(csAttributName) == csAttributValue ) {
					return hElement;
				}
			}
		}

		// nächstes Element
		hElement = GetNextSiblingItem(hElement);
	}

	return NULL;
}

// liefert ersten Eintrag mit Text "csText"

//##ModelId=396A3C060382
HXMLITEM CXmlStruct::GetItem(CString & csText)
{
	HXMLITEM hFound;

	hFound = FindItemText(csText);
	
	return hFound;
}

// liefert Eintrag mit bestimmtem Attribut und Wert

//##ModelId=396A3C060291
HXMLITEM CXmlStruct::FindItemByAttribute(CString csElementName, CString csAttributName, CString csAttributValue)
{
	HXMLITEM hFound;

	hFound = CXmlTreeElement::FindItemByAttribute(csElementName, csAttributName, csAttributValue); 
	
	return hFound;
}

// Liefert nächsten zu Code passenden Eintrag

//##ModelId=396A3C06027D
HXMLITEM CXmlStruct::GetNextItem(HXMLITEM hItem, unsigned int nCode)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		switch ( nCode )
		{
		case XML_TGN_CHILD:
			return GetChildItem(hItem);
	
		case XML_TGN_NEXT:
			return GetNextSiblingItem(hItem);
		
		case XML_TGN_PARENT:
			return GetParentItem(hItem);

		case XML_TGN_ROOT:
			if (pElement->m_Parent == NULL)
				pElement = this;
			else
				pElement = (CXmlTreeElement*)pElement->m_Parent.Value();
		
			if ( pElement->m_ItemList.GetCount() > 0 )
				return (DWORD)pElement->m_ItemList.GetHead();
			else
				return NULL;
			break;

		default:
			m_ErrorID = XML_ERROR_UNKNOWN_KEYWORD;
			return NULL;
		}
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
}

// Liefert TRUE, wenn Item Kind-Items hat

//##ModelId=396A3C06026A
BOOL CXmlStruct::ItemHasChildren(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		if (pElement->m_ItemList.GetCount() > 0)
			return TRUE;
		else
			return FALSE;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return FALSE;
	}
}

// Einfügen eines neuen Zweiges

//##ModelId=396A3C060255
HXMLITEM CXmlStruct::InsertItem(CString & csText, HXMLITEM hParent)	// = XML_TI_ROOT
{
	CXmlTreeElement* pParent = NULL;
	CXmlTreeElement* pNewElement = NULL;
	CXmlElement* pListElement = NULL;

	// check handle
	if ( !hParent.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	// Neues Element
	pNewElement = new CXmlTreeElement(csText);
	pListElement = new CXmlElement(csText);

	switch ( hParent.Value() )
	{
	case XML_TI_ROOT: 
		pParent = this;
		pNewElement->m_Parent = NULL;
		break;
	default:
		pParent = (CXmlTreeElement*)hParent.Value();
		pNewElement->m_Parent = hParent;
	}

	try
	{
		// Einfügen in Item-List
		pParent->m_ItemList.AddTail(pNewElement);

		// Anhängen an lineare Elementliste
		m_ElementList.AddTail(pListElement);
	}
	catch(...)
	{
		delete pNewElement;
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	// Eintragen des Pointers in Baumstruktur
	SetItemData((DWORD)pNewElement, (DWORD)pListElement);

	return (DWORD)pNewElement;
}

// Löscht einen Item mit allen Kind-Items

//##ModelId=396A3C06024B
BOOL CXmlStruct::DeleteItem(HXMLITEM hItem)
{
	CXmlTreeElement* pElement = (CXmlTreeElement*)hItem.Value();
	CXmlTreeElement* pParent = NULL;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
	
	if (pElement->m_Parent == XML_TI_ROOT)
		pParent = this;
	else
		pParent = (CXmlTreeElement*)pElement->m_Parent.Value();

	try
	{
		// Lösche Klassen-Liste des Elements
		pElement->DeleteItemList();

		// Lösche aus Liste
		pParent->m_ItemList.RemoveAt(pParent->m_ItemList.Find(pElement));

		// Lösche Element
		delete pElement;
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
	}

	return FALSE;
}

// Löscht den vollständigen Baum

//##ModelId=396A3C060238
BOOL CXmlStruct::DeleteAllItems()
{
	DeleteItemList();

	if (!m_ItemList.IsEmpty())
		return FALSE;

	// Löschen der Element-Liste
	while (!m_ElementList.IsEmpty())
	{
		delete m_ElementList.GetHead();
		m_ElementList.RemoveHead();
	}

	return TRUE;
}

// ==========================================================================
// Zugriffsmethoden auf einzelne Elemente
// ==========================================================================

int CXmlStruct::CountAttributs(HXMLITEM hItem)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return -1;
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->m_AttributList.GetCount();
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return -1;
	}
}

CString CXmlStruct::GetAttributValue(HXMLITEM hItem, int nPos)
{
	CXmlElement *ListElement;
	int nCur = 0;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();

		POSITION pos =  ListElement->m_AttributList.GetHeadPosition();
		while ( pos )
		{
			if ( nCur == nPos )
				return ListElement->m_AttributList.GetAt(pos)->m_Value;

			ListElement->m_AttributList.GetNext(pos);
			nCur++;
		}
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
	}

	return _T("");
}

CString CXmlStruct::GetAttributName(HXMLITEM hItem, int nPos)
{
	CXmlElement *ListElement;
	int nCur = 0;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();

		POSITION pos =  ListElement->m_AttributList.GetHeadPosition();
		while ( pos )
		{
			if ( nCur == nPos )
				return ListElement->m_AttributList.GetAt(pos)->m_Name;

			ListElement->m_AttributList.GetNext(pos);
			nCur++;
		}
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
	}

	return _T("");
}

// Hinzufügen neues Attribut

//##ModelId=396A3C060223
int CXmlStruct::AddAttribut(HXMLITEM hItem, CString & csName, CString & csValue)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->AddAttribut(csName, csValue);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return m_ErrorID;
	}
}

// Kontrolle, ob csName Attribut

//##ModelId=396A3C06020F
BOOL CXmlStruct::IsAttribut(HXMLITEM hItem, CString & csName)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->IsAttribut(csName);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return FALSE;
	}
}

// Löschen eines Attributs

//##ModelId=396A3C0601FB
BOOL CXmlStruct::DeleteAttribut(HXMLITEM hItem, CString & csName)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->DeleteAttribut(csName);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return FALSE;
	}
}

// Liefert den Wert eines bestimmten Attributs zurück

//##ModelId=396A3C0601E7
CString CXmlStruct::GetAttributValue(HXMLITEM hItem, CString & csName)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->GetAttributValue(csName);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

}

// Setzt den Wert eines bestimmten Attributs

//##ModelId=396A3C0601D3
int CXmlStruct::SetAttributValue(HXMLITEM hItem, CString & csName, CString & csValue)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}
	
	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->SetAttributValue(csName, csValue);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return m_ErrorID;
	}
}

int CXmlStruct::SetAttributValue(HXMLITEM hItem, CString & csName, int nValue)
{
	CString csValue(_T(""));
	csValue.Format(_T("%d"), nValue);

	return SetAttributValue(hItem, csName, csValue);
}

// Belegt Elementwert, abhängig von DataTyp

//##ModelId=396A3C0601B6
int CXmlStruct::SetElementValue(HXMLITEM hItem, CString & csValue)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return NULL;
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->SetElementValue(csValue);
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return m_ErrorID;
	}
}

//##ModelId=396A3C0601AB
CString CXmlStruct::GetElementValue(HXMLITEM hItem)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->GetElementValue();
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}
}

//##ModelId=396A3C0601A1
CString CXmlStruct::GetElementName(HXMLITEM hItem)
{
	CXmlElement *ListElement;

	// check handle
	if ( !hItem.isValid() ) {
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}

	try
	{
		ListElement = (CXmlElement*)GetItemData(hItem).Value();
		return ListElement->GetElementName();
	}
	catch(...)
	{
		m_ErrorID = XML_ERROR_INVALID_ADRESS;
		return _T("");
	}
}
// ==========================================================================
// Ein- und Auslesen von Datendatei
// ==========================================================================

//##ModelId=396A3C06018D
int CXmlStruct::ReadDataFile(CString   & csInputFile, BOOL bAdd /* = FALSE */ )
{
	m_ErrorID = 0;

	// Baum zurücksetzen ?
	if (!bAdd)
		DeleteAllItems();

	// InformationItem Processor initialisieren
	XmlProcessor xmlProcessor(this);

	xmlProcessor.SetInputFile(csInputFile);
	if ( xmlProcessor.parseXml() > 0 )
	{
		m_ErrorID = XML_ERROR_PARSER_ERROR;
		m_ErrorString = xmlProcessor.GetParserMsg();
		DeleteAllItems();
	}

	return m_ErrorID;
}

//##ModelId=396A3C060179
int CXmlStruct::ReadDataString(CString & csInputString, BOOL bAdd /* = FALSE */ )
{
	m_ErrorID = 0;

	// Baum zurücksetzen ?
	if (!bAdd)
		DeleteAllItems();

	// InformationItem Processor initialisieren
	XmlProcessor xmlProcessor(this);

	xmlProcessor.SetInputString(csInputString);
	if ( xmlProcessor.parseXml() > 0 )
	{
		m_ErrorID = XML_ERROR_PARSER_ERROR;
		m_ErrorString = xmlProcessor.GetParserMsg();
		DeleteAllItems();
	}

	return m_ErrorID;
}

//##ModelId=396A3C06016F
int CXmlStruct::WriteDataFile(CString & csOutputFile)
{
	int iErr = 0;
	FILE *pFile = NULL;
	CString csLine("");
	HXMLITEM hRoot;
	pFile = _wfopen(csOutputFile.GetString(), L"w");

	if (pFile == NULL)
	{
		printf("errno = %d\n", errno);
			perror("Error");
		return XML_ERROR_OPEN_FILE;
	}

	// ROOT-Eintrag
	hRoot = GetRootItem();
	if (hRoot == NULL)
		return XML_ERROR_TREE_EMPTY;

	// Zusammenbau der ersten Dokument-Zeile
	// z.B. <!doctype meta-dat SYSTEM "meta-dat.dtd">
	csLine = "<!DOCTYPE ";
	csLine += GetItemText(hRoot)
		   +  " SYSTEM "
		   +  "\""
		   +  GetItemText(hRoot)
		   +  ".DTD\">\n";

	// Schreiben der ersten Zeile
	fprintf( pFile, "%ls", csLine.GetBuffer(csLine.GetLength()) );

	// Schreiben der Datenstruktur
	iErr = WriteDataLine(pFile, hRoot, 0);

    // Schliessen DatenFile
	fclose(pFile);

	return iErr;
}

//##ModelId=396A3C060165
int CXmlStruct::WriteDataStream(std::wostream& outStream)
{
	int iErr = 0;
	HXMLITEM hRoot;

	if(!outStream)
		return XML_ERROR_BAD_STREAM;

	// ROOT-Eintrag
	hRoot = GetRootItem();
	if (hRoot == NULL)
		return XML_ERROR_TREE_EMPTY;

	// Zusammenbau der ersten Dokument-Zeile
	// z.B. <!doctype meta-dat SYSTEM "meta-dat.dtd">
	outStream 
		<< "<!DOCTYPE " << GetItemText(hRoot).GetBuffer(GetItemText(hRoot).GetLength()) << " SYSTEM " << "\"" 
		<< GetItemText(hRoot).GetBuffer(GetItemText(hRoot).GetLength()) << ".DTD\">\n";

	// Schreiben der Datenstruktur
	iErr = WriteDataLine(outStream, hRoot, 0);

	return iErr;
}

int CXmlStruct::WriteDataString(CString &rString)
{
	int iErr = 0;
	HXMLITEM hRoot;

	rString = _T("");

	// ROOT-Eintrag
	hRoot = GetRootItem();
	if (hRoot == NULL)
		return XML_ERROR_TREE_EMPTY;

	// Zusammenbau der ersten Dokument-Zeile
	// z.B. <!doctype meta-dat SYSTEM "meta-dat.dtd">
	rString += "<!DOCTYPE ";
	rString += GetItemText(hRoot).GetBuffer(GetItemText(hRoot).GetLength());
	rString += " SYSTEM ";
	rString += "\"";
	rString += GetItemText(hRoot).GetBuffer(GetItemText(hRoot).GetLength());
	rString += ".DTD\">\n";

	// Schreiben der Datenstruktur
	iErr = WriteDataLine(rString, hRoot, 0);

	return iErr;
}

//##ModelId=396A3C060332
int CXmlStruct::WriteDataLine(FILE *pFile, HXMLITEM hParent, int nLevel)
{
	int i;
	int iErr = 0;
	CString csLine("");

	CXmlElement* pElement = NULL;

	// check handle
	if ( !hParent.isValid() ) {
		return XML_ERROR_INVALID_ADRESS;
	}

	try
	{
		while (hParent != NULL)
		{
			// Einrücken, um bessere Übersicht zu gewährleisten
			for (i=0; i<nLevel; i++)
				csLine += '\t';
		
			// Elementname
			csLine += "<" + GetItemText(hParent);

			// zugehöriges Element
			pElement = (CXmlElement*)GetItemData(hParent).Value();

			// Einfügen eventueller Attribute
			for( POSITION pos=pElement->m_AttributList.GetHeadPosition(); pos != NULL; pElement->m_AttributList.GetNext(pos))
			{
				csLine += " "
					   +  pElement->m_AttributList.GetAt(pos)->m_Name
					   + "=\""
					   +  pElement->m_AttributList.GetAt(pos)->m_Value
					   + "\"";
			}

			// Tag-Ende
			csLine += ">";
	
			// Wenn Element Kindeinträge => rekursives Einfügen der Kinder
			if (ItemHasChildren(hParent))
			{
				// Neue Zeile
				csLine += "\n";
				
				// Schreiben der Datenzeile
				fprintf( pFile, "%ls", csLine.GetBuffer(csLine.GetLength()) );
				csLine = "";
				
				// Rekursives Einfügen der Kind-Elemente
				iErr = WriteDataLine(pFile, GetChildItem(hParent), nLevel+1);
				if (iErr > 0)
					return iErr;
				
				// EndTag einrücken
				for (i=0; i<nLevel; i++)
					csLine += '\t';
				
			}
			else
			{
				// Wert des Elements als CString anhängen
				csLine += pElement->GetElementValue();
			}		

			// EndTag einfügen
			csLine += "</"
				+  GetItemText(hParent)
				+ ">\n";
			
			// Schreiben der Datenzeile
			/// md fprintf( pFile, "%ls", csLine.GetBuffer(csLine.GetLength()) );  
			fwprintf(pFile, L"%ls", csLine.GetBuffer(csLine.GetLength()));

			csLine = "";
			
			// Nächster Eintrag der gleichen Ebene
			hParent = GetNextSiblingItem(hParent);
		}
	}
	catch(...)
	{
		return XML_ERROR_INVALID_ADRESS;
	}

	return 0;
}

//##ModelId=396A3C060347
/// md int CXmlStruct::WriteDataLine(std::ostream& stream, HXMLITEM hParent, int nLevel)
int CXmlStruct::WriteDataLine(std::wostream& stream, HXMLITEM hParent, int nLevel)
{
	int i;
	int iErr = 0;

	CXmlElement* pElement = NULL;

	// check handle
	if ( !hParent.isValid() ) {
		return XML_ERROR_INVALID_ADRESS;
	}

	try
	{
		while (hParent != NULL)
		{
			// Einrücken, um bessere Übersicht zu gewährleisten
			for (i=0; i<nLevel; i++)
				stream << '\t';
		
			// Elementname
			stream << "<" << GetItemText(hParent);

			// zugehöriges Element
			pElement = (CXmlElement*)GetItemData(hParent).Value();

			// Einfügen eventueller Attribute
			for( POSITION pos=pElement->m_AttributList.GetHeadPosition(); pos != NULL; pElement->m_AttributList.GetNext(pos))
			{
				stream << " "
					   <<  pElement->m_AttributList.GetAt(pos)->m_Name
					   << "=\""
					   <<  pElement->m_AttributList.GetAt(pos)->m_Value
					   << "\"";
			}

			// Tag-Ende
			stream << ">";
	
			// Wenn Element Kindeinträge => rekursives Einfügen der Kinder
			if (ItemHasChildren(hParent))
			{
				// Neue Zeile
				stream << "\n";

				// Rekursives Einfügen der Kind-Elemente
				iErr = WriteDataLine(stream, GetChildItem(hParent), nLevel+1);
				if (iErr > 0)
					return iErr;

				// EndTag einrücken
				for (i=0; i<nLevel; i++)
					stream << '\t';

			}
			else
			{
				// Wert des Elements als CString anhängen
				stream << pElement->GetElementValue();
			}		

			// EndTag einfügen
			stream << "</"
				   <<  GetItemText(hParent)
				   << ">\n";
			
			// Nächster Eintrag der gleichen Ebene
			hParent = GetNextSiblingItem(hParent);
		}
	}
	catch(...)
	{
		return XML_ERROR_INVALID_ADRESS;
	}

	return 0;
}

int CXmlStruct::WriteDataLine(CString& rStr, HXMLITEM hParent, int nLevel)
{
	int i;
	int iErr = 0;

	CXmlElement* pElement = NULL;

	// check handle
	if ( !hParent.isValid() ) {
		return XML_ERROR_INVALID_ADRESS;
	}

	try
	{
		while (hParent != NULL)
		{
			// Einrücken, um bessere Übersicht zu gewährleisten
			for (i=0; i<nLevel; i++)
				rStr += '\t';
		
			// Elementname
			rStr += "<" + GetItemText(hParent);

			// zugehöriges Element
			pElement = (CXmlElement*)GetItemData(hParent).Value();

			// Einfügen eventueller Attribute
			for( POSITION pos=pElement->m_AttributList.GetHeadPosition(); pos != NULL; pElement->m_AttributList.GetNext(pos))
			{
				rStr  +=  " "
					   +  pElement->m_AttributList.GetAt(pos)->m_Name
					   + "=\""
					   +  pElement->m_AttributList.GetAt(pos)->m_Value
					   + "\"";
			}

			// Tag-Ende
			rStr += ">";
	
			// Wenn Element Kindeinträge => rekursives Einfügen der Kinder
			if (ItemHasChildren(hParent))
			{
				// Neue Zeile
				rStr += "\n";

				// Rekursives Einfügen der Kind-Elemente
				iErr = WriteDataLine(rStr, GetChildItem(hParent), nLevel+1);
				if (iErr > 0)
					return iErr;

				// EndTag einrücken
				for (i=0; i<nLevel; i++)
					rStr += '\t';

			}
			else
			{
				// Wert des Elements als CString anhängen
				rStr += pElement->GetElementValue();
			}		

			// EndTag einfügen
			rStr += "</"
				 +  GetItemText(hParent)
				 + ">\n";
			
			// Nächster Eintrag der gleichen Ebene
			hParent = GetNextSiblingItem(hParent);
		}
	}
	catch(...)
	{
		return XML_ERROR_INVALID_ADRESS;
	}

	return 0;
}

// ==========================================================================
// Fehlerrückgabe
// ==========================================================================

//##ModelId=396A3C06015B
int CXmlStruct::GetError(void)
{
	int nError = m_ErrorID;
	m_ErrorID = 0;

	return nError;
}

//##ModelId=396A3C060147
CString CXmlStruct::GetErrorString(void)
{
	int nError = m_ErrorID;
	m_ErrorID = 0;

	if (nError != XML_ERROR_PARSER_ERROR)
		m_ErrorString.Format(_T("Fehler: %d"), nError);

	return m_ErrorString;
}

} // namespace eag

/////////////////////////////////////////////////////////////////////////////

