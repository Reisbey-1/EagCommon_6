/*
//=============================================================================
//
// = PROJECT
//
//     XML -- XML TreeBuilder
//
// = FILENAME
//
//     XmlTreeBuilder.h
//
//
// = SUMMARY
//
//     SAX Header-File for the XmlTreeBuilder class, the base class for the
//     SAX (Simple API for XML) event system 
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

#ifndef _XMLTREEBUILDER_H__
#define _XMLTREEBUILDER_H__

// header for filestream
#include <fstream>   /// DLH

// header for stack
#include <stack>

// scanner/parser
#include "xmlscanner.h"
#include "xmlparser.h"

#include "xmlhandler.h"

namespace eag {

//=============================================================================

extern XMLTREEBUILDER_API CXmlNullHandler gNullHandler;
// no nested tags 
extern XMLTREEBUILDER_API CXmlHandler* const gLeafTag;
// unrecognized tag
extern XMLTREEBUILDER_API CXmlHandler* const gSwallowTagSet;

//=============================================================================

class XMLTREEBUILDER_API CXmlTreeBuilder : private XmlScanner, public XmlParser

//=============================================================================
//
// = TITLE
//
//     CXmlTreeBuilder
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     base class for the SAX (Simple API for XML) event system
//
//=============================================================================

{
// attributes
protected:
	std::string m_sError;

	std::string m_sVersion;

	// String mit Fehlermeldungen
	std::stack<CXmlHandler*> m_Handlers;

	CXmlTopLevelHandler* m_pTopLevelHandler;

// methods
protected:
	CXmlTreeBuilder();

	//##ModelId=396A3C0703A2
	virtual void yyerror(char *m);
	//##ModelId=396A3C070398
	int scanXml(void);

	void startDocument(const StartDocumentEvent &);
	void startElement(const StartElementEvent &);
	void endElement(const EndElementEvent &);
	void data(const DataEvent &);

	std::string getString(CharString ChStr);

public:
	CXmlTreeBuilder(CXmlHandler* pTopLevelHandler, std::string sVersion = "1.0");
	~CXmlTreeBuilder(void);

	std::string GetErrorString(void);
	std::string GetVersion(void);

	bool ReadDataFile(std::string fileName, bool bDecode = false);
	bool ReadDataString(std::string& rString, bool bDecode = false);

	bool WriteDataFile(std::string fileName, std::string rootName, bool bEncode = false, bool bOptimize = false);
	bool WriteDataString(std::string& rString, std::string rootName, bool bEncode = false, bool bOptimize = false);
};

} // namespace eag

#endif // #ifndef _XMLTREEBUILDER_H__
