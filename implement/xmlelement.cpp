// MddlElement Implementation File
//

#include "stdafx.h"

#include "XmlElement.h"

/////////////////////////////////////////////////////////////////////////////
// namespace eag

namespace eag
{

/////////////////////////////////////////////////////////////////////////////
// CXmlAttribut

// Konstruktor

CXmlAttribut::CXmlAttribut(CString csName,   // = ""
						     CString csValue)  // = ""
{
	m_Name = csName;
	m_Name.MakeUpper();

	m_Value = csValue;
}

/////////////////////////////////////////////////////////////////////////////
// CXmlElement

// Konstruktor

CXmlElement::CXmlElement(CString csName)       // = ""
{
	m_Name = csName;

	// UPPER-CASE
	m_Name.MakeUpper();

	m_csData = "";
}

// Destruktor

CXmlElement::~CXmlElement()
{
	while (!m_AttributList.IsEmpty())
	{
		delete m_AttributList.GetHead();
		m_AttributList.RemoveHead();
	}
}

/////////////////////////////////////
// Operationen mit und auf Attribute

// Hinzufügen neues Attribut

int CXmlElement::AddAttribut(CString csName, CString csValue)
{
	CXmlAttribut* newAttribut = NULL;
	
	// UPPER-CASE
	csName.MakeUpper();

	// Kontrolle, ob bereits vorhanden
	if (IsAttribut(csName))
		return XML_ERROR_ALREADY_DEFINED;

	// Einfügen des neuen Attributs
	newAttribut = new CXmlAttribut(csName, csValue);
	m_AttributList.AddTail(newAttribut);

	return 0;
}

// Kontrolle, ob Attribut vorhanden

BOOL CXmlElement::IsAttribut(CString csName)
{
	// UPPER-CASE
	csName.MakeUpper();	

	// Schleife über die Pointer-Liste
	for( POSITION pos=m_AttributList.GetHeadPosition(); pos != NULL; m_AttributList.GetNext(pos))
	{
		if ( m_AttributList.GetAt(pos)->m_Name == csName )
			return TRUE;
	}

	return FALSE;
}

// Löschen des Attributs csName aus Element hItem

BOOL CXmlElement::DeleteAttribut(CString csName)
{
	BOOL bFound = FALSE;
	CTypedPtrList<CObList, CXmlAttribut*> tempList; 	// temporaere Liste

	// UPPER-CASE
	csName.MakeUpper();	

	// Schleife über die Pointer-Liste
	while (!m_AttributList.IsEmpty())
	{
		if ( m_AttributList.GetHead()->m_Name != csName ) {
			tempList.AddTail( m_AttributList.GetHead() );
		}
		else {
			bFound = TRUE;
			delete m_AttributList.GetHead();
		}
		m_AttributList.RemoveHead();
	}
	
	// sort back
	while (!tempList.IsEmpty())
	{
		m_AttributList.AddTail( tempList.GetHead() );
		tempList.RemoveHead();
	}

	return bFound;
}

// Suche nach Attributwert

CString CXmlElement::GetAttributValue(CString csName)
{
	// UPPER-CASE
	csName.MakeUpper();	

	// Schleife über die Pointer-Liste
	for( POSITION pos=m_AttributList.GetHeadPosition(); pos != NULL; m_AttributList.GetNext(pos))
	{
		if ( m_AttributList.GetAt(pos)->m_Name == csName )
			return m_AttributList.GetAt(pos)->m_Value;
	}

	return _T("");
}

// Setzen eines neuen Attribut-Wertes

int CXmlElement::SetAttributValue(CString csName, CString csValue)
{
	// UPPER-CASE
	csName.MakeUpper();	

	// Schleife über die Pointer-Liste
	for( POSITION pos=m_AttributList.GetHeadPosition(); pos != NULL; m_AttributList.GetNext(pos))
	{
		if ( m_AttributList.GetAt(pos)->m_Name == csName )
		{
			m_AttributList.GetAt(pos)->m_Value = csValue;
			return 0;
		}
	}

	// Attribut nicht gefunden
	return XML_ERROR_ATTRIBUT_NOT_FOUND;
}

///////////////////////////////////////
// Oberationen mit und auf das Element

int CXmlElement::SetElementValue(CString csValue)
{
	m_csData = CutChar(csValue);
	return 0;
}

// Rückgabe des Elementwert als CString

CString CXmlElement::GetElementValue()
{
	return m_csData;
}

// Rückgabe des Elementnamen als CString

CString CXmlElement::GetElementName()
{
	return m_Name;
}

// Hilfsfunktionen

// CutChar
//
// Entfernen evtl. CR-LF und Tabulatoren am Anfang und Ende eines Wertes

CString CXmlElement::CutChar(CString csValue)
{
	BOOL bEnd = FALSE;
	char cChar;
	unsigned nPos = 0;
	unsigned nLength;
	unsigned i=0;

	// Länge des String
	nLength = csValue.GetLength();

	// CR-LF und Tabulatoren zu Anfang und Ende entfernen
	while ((!bEnd)&&(i<nLength))
	{
		cChar = csValue.GetAt(i);
	
		switch ( cChar )
		{
		case ' ':
			i++;
			break;
		case '\t':
			i++;
			break;
		case '\n':
			i++;
			break;
		case '\r':
			i++;
			break;
		default: bEnd = TRUE;
		}
	}

	if (i != 0) // Wenn Tab oder CR-LF
	{
		csValue = csValue.Right(nLength-i);
		nLength = csValue.GetLength();
	}

	// Entferne Tab und CR-LF am Ende eines Wertes
	for (i=0; i<nLength; i++)
	{
		cChar = csValue.GetAt(i);
		
		switch ( cChar )
		{
		case '\t': break;
		case '\n': break;
		case '\r': break;
		default: nPos = i;
		}
	}
	
	if (nPos < nLength)
		csValue = csValue.Left(nPos+1);

	return csValue;
}

} // namespace eag

/////////////////////////////////////////////////////////////////////////////
