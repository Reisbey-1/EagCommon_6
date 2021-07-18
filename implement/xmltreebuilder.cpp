//=============================================================================
// xmltreebuilder.cpp
//=============================================================================

#include "stdafx.h"
#include "xmltreebuilder.h"
#include "FileUtility.h"

namespace eag
{

// one NULL handler is enough ...
CXmlNullHandler gNullHandler;
// no nested tags 
CXmlHandler* const gLeafTag = NULL;
// unrecognized tag
CXmlHandler* const gSwallowTagSet = NULL;

//=============================================================================

bool CXmlHandler::m_bEncode = false;
bool CXmlHandler::m_bOptimize = false;

//=============================================================================

CXmlTreeBuilder::CXmlTreeBuilder(CXmlHandler* pTopLevelHandler, std::string sVersion)
	: m_sError(""),
	  m_sVersion(sVersion)
{
	m_pTopLevelHandler = new CXmlTopLevelHandler(pTopLevelHandler, sVersion);
	yyin = NULL;
}

//=============================================================================

CXmlTreeBuilder::~CXmlTreeBuilder()
{
	if (yyin)
		delete yyin;

	if (m_pTopLevelHandler)
		delete m_pTopLevelHandler;
}

//=============================================================================

int CXmlTreeBuilder::scanXml()
{
	return XmlScanner::scanValue(theTokenValue);
}

//=============================================================================

bool CXmlTreeBuilder::ReadDataFile(std::string fileName, bool bDecode)
{
	bool bResult = false;

	// reset error
	m_sError = "";

	// decode?
	wantDecode = bDecode;

	// set stream
	yyin = new std::ifstream(fileName.c_str());

	// parse stream
	if ( parseXml() == 0 )
		bResult = true;

	// clean up
	delete yyin;
	yyin = NULL;

	return bResult;
}

//=============================================================================

bool CXmlTreeBuilder::WriteDataString(std::string& rString, std::string rootName, bool bEncode, bool bOptimize)
{
	bool bResult = false;

	// reset error
	m_sError = "";

	// reset string
	rString = "";

	// outstream
	std::ostrstream streamOut;

	// set prec to 14
	streamOut.precision(14);

	// encoding
	CXmlHandler::m_bEncode = bEncode;

	// optimize
	CXmlHandler::m_bOptimize = bOptimize;

	// write elements
	bResult = m_pTopLevelHandler->streamElement(streamOut,rootName);

	// set return value
	if ( bResult )
		rString.append(streamOut.str(),streamOut.pcount());

	return bResult;
}

//=============================================================================

bool CXmlTreeBuilder::WriteDataFile(std::string fileName, std::string rootName, bool bEncode, bool bOptimize)
{
	bool bResult = false;

	// reset error
	m_sError = "";

	// set stream
	std::ofstream streamOut;

	// set prec to 14
	streamOut.precision(14);

	// check on existing and set to writable
	if (CFileUtility::existFile(fileName) )
	{
		if ( ! CFileUtility::setWritable(fileName) )
			return false;
	}
	
	// open file
	streamOut.open(fileName.c_str());

	// encoding
	CXmlHandler::m_bEncode = bEncode;

	// optimize
	CXmlHandler::m_bOptimize = bOptimize;

	// write elements
	bResult = m_pTopLevelHandler->streamElement(streamOut,rootName);

	// close file
	streamOut.close();

	return bResult;
}

//=============================================================================

bool CXmlTreeBuilder::ReadDataString(std::string& rString, bool bDecode)
{
	bool bResult = false;

	// reset error
	m_sError = "";

	// decode?
	wantDecode = bDecode;

	// set stream
	if (rString == "")
		return false;
	yyin = new std::istrstream((char*)rString.c_str());

	// parse stream
	if ( parseXml() == 0 )
		bResult = true;

	// clean up
	delete yyin;
	yyin = NULL;

	return bResult;
}

//=============================================================================

void CXmlTreeBuilder::yyerror(char *msg)
{
	char text[1024];
	sprintf(text," near \"%s\"",yytext);

	m_sError += msg;
	m_sError += text;
}

//=============================================================================

std::string CXmlTreeBuilder::GetErrorString()
{
	return m_sError;
}

//=============================================================================

std::string CXmlTreeBuilder::GetVersion()
{
	return m_sVersion;
}

//=============================================================================

void CXmlTreeBuilder::startDocument(const StartDocumentEvent &)
{
	m_Handlers.push(m_pTopLevelHandler);
}

//=============================================================================

void CXmlTreeBuilder::startElement(const StartElementEvent &event)
{
	CXmlHandler* curHandler = m_Handlers.top();
	CXmlHandler* nextHandler = m_Handlers.top()->startElement(event);
	m_Handlers.push(nextHandler ? nextHandler : &gNullHandler );
}

//=============================================================================

void CXmlTreeBuilder::endElement(const EndElementEvent &event)
{
	CXmlHandler* curHandler = m_Handlers.top();
	if (m_Handlers.top()->endElement())
		m_Handlers.pop();
}

//=============================================================================

void CXmlTreeBuilder::data(const DataEvent &event)
{
	m_Handlers.top()->data(event);
}

//=============================================================================

} // namespace eag