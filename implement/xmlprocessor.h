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
//     Header-File für die Klasse XmlProcessor
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

#ifndef _XMLPROCESSOR_H__
#define _XMLPROCESSOR_H__

// header for ostrstream
#include <strstream>	 /// DLG

// Header for TreeStruct
#include "XmlStruct.h"

#include "xmldef.h"
#include "xmlscanner.h"
#include "xmlparser.h"

namespace eag {

//##ModelId=396A3C07029D
class XmlProcessor : private XmlScanner, public XmlParser

//=============================================================================
//
// = TITLE
//
//     XmlProcessor
//
// = CLASSTYPE
//
//     Klasse
//
//
// = DESCRIPTION
//
//     Die Klasse XmlProcessor erzeugt aus einer XML-Instanz eine
//     Baum-Datenstruktur.
//
//=============================================================================

{
protected:
	//##ModelId=396A3C07031F
	CString m_csError;
		// String mit Fehlermeldungen
	//##ModelId=396A3C070315
	CString m_csInputFile;
		// Name der zu parsenden Datei
	//##ModelId=396A3C070301
	CString m_csScanstring;
		// zu parsender String
	//##ModelId=396A3C0702F7
	int	m_Depth;
		// Schachteltiefe (0 = Root-Ebene)
	//##ModelId=396A3C0702ED
	HXMLITEM m_hParent;
		// aktueller Knoten
	//##ModelId=396A3C0702CF
	CString m_CurrentValue;
		// aktueller Elementwert
	//##ModelId=396A3C0702BD
	CXmlStruct *m_pTreeStruct;
		// Pointer auf Baumstruktur

	//##ModelId=396A3C0703A2
	virtual void yyerror(char *m);
	//##ModelId=396A3C070398
	int scanXml(void);

	void startDocument(const StartDocumentEvent &);
	//##ModelId=396A3C07038D
	void startElement(const StartElementEvent &);
	//##ModelId=396A3C070383
	void endElement(const EndElementEvent &);
	//##ModelId=396A3C070379
	void data(const DataEvent &);

	//##ModelId=396A3C070366
	CString getString(CharString ChStr);

public:
	//##ModelId=396A3C07035B
	XmlProcessor(CXmlStruct *pTreeStruct);
	//##ModelId=396A3C070351
	~XmlProcessor(void);

	//##ModelId=396A3C070347
	CString GetParserMsg(void);

	//##ModelId=396A3C070334
	BOOL SetInputFile(CString sFile);
	//##ModelId=396A3C070329
	BOOL SetInputString(CString sString);

};

} // namespace eag

#endif // #ifndef _XMLPROCESSOR_H__
