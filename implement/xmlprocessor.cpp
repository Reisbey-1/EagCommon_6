//=============================================================================
// xmlprocessor.cpp
//=============================================================================

#include "stdafx.h"

#include <fstream>  /// DLG
#include <strstream>	/// DLG
#include "xmlprocessor.h"

//=============================================================================

namespace eag {


XmlProcessor::XmlProcessor(CXmlStruct *pTreeStruct)
{
	yyin            = NULL;
	m_Depth			= 0;
	m_pTreeStruct	= pTreeStruct;
	m_CurrentValue	= "";
	m_hParent		= XML_TI_ROOT;

	m_csInputFile  = "default.sgm";
	m_csScanstring = "";
	m_csError      = "";
}

//=============================================================================

XmlProcessor::~XmlProcessor()
{
	if (yyin)
		delete yyin;
}

//=============================================================================

int XmlProcessor::scanXml()
{
	return XmlScanner::scanValue(theTokenValue);
}

//=============================================================================

BOOL XmlProcessor::SetInputFile(CString sFile)
{
	m_csInputFile = sFile;
	yyin = new std::ifstream(sFile);
	return TRUE;
}

//=============================================================================

BOOL XmlProcessor::SetInputString(CString sString)
{
	m_csScanstring = sString;
	if (m_csScanstring == "")
		return FALSE;

	 yyin = new std::istrstream((char*)m_csScanstring.GetBuffer(m_csScanstring.GetLength()));
	/// yyin = new std::wistream(m_csScanstring.GetBuffer(m_csScanstring.GetLength()));
	return TRUE;
}

//=============================================================================

void XmlProcessor::yyerror(char *msg)
{
	char text[1024];
	sprintf(text," near \"%s\"",yytext);

	m_csError += msg;
	m_csError += text;
}

//=============================================================================

CString XmlProcessor::GetParserMsg()
{
	return m_csError;
}

//=============================================================================

void XmlProcessor::startDocument(const StartDocumentEvent &)
{
	// nothing to do
}

//=============================================================================

void XmlProcessor::startElement(const StartElementEvent &event)
{
	// Einfügen eines neuen Elements
	m_hParent = m_pTreeStruct->InsertItem(getString(event.gi), m_hParent);

	// Einfügen der Attribute
	for (size_t num = 0; num < event.nAttributes; num++)
	{
		// CDATA - Attribut
		m_pTreeStruct->AddAttribut(m_hParent,
					  			   getString(event.attributes[num].name),
							       getString(event.attributes[num].data));
	}

	// eine Ebene erhöhen
	m_Depth++;
}

//=============================================================================

void XmlProcessor::endElement(const EndElementEvent &event)
{
	// Elementwert zuschneiden: Linke und rechte Leerstellen, Return-Zeichen und Tabs
	if ( m_CurrentValue != "" )
	{
		m_CurrentValue.TrimLeft();
		m_CurrentValue.TrimRight();
		m_pTreeStruct->SetElementValue(m_hParent, m_CurrentValue);
	}

	// eine Ebene tiefer
	if (m_Depth > 0)
		m_hParent = m_pTreeStruct->GetParentItem(m_hParent);
	m_Depth--;

	// Wert zuruecksetzen
	m_CurrentValue = "";
}

//=============================================================================

void XmlProcessor::data(const DataEvent &event)
{
	m_CurrentValue += getString(event.data);
	m_pTreeStruct->SetElementValue(m_hParent, m_CurrentValue);
}

//=============================================================================

CString XmlProcessor::getString(CharString ChStr)
{
	CString csString("");

	for (size_t i=0; i<ChStr.len; i++)
		csString += char(ChStr.ptr[i]);

	return csString;	
}

} // namespace eag

//=============================================================================
