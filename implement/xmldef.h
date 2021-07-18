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
//     Header-File für die XML-Datenstruktur Definitionen
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

#ifndef _xmldef_h__
#define _xmldef_h__

//=============================================================================

#ifdef XMLTREEBUILDER_EXPORTS
#define XMLTREEBUILDER_API __declspec(dllexport)
#else
#define XMLTREEBUILDER_API __declspec(dllimport)
#endif

#ifdef XMLSTRUCT_EXPORTS
#define XMLSTRUCT_API __declspec(dllexport)
#else
#define XMLSTRUCT_API __declspec(dllimport)
#endif

//=============================================================================
// Definitionen von StandardHandles
//=============================================================================

#define XML_TI_ROOT		0x0001

#define XML_TGN_CHILD	0x0002
#define XML_TGN_NEXT	0x0003
#define XML_TGN_PARENT	0x0004
#define XML_TGN_ROOT	0x0005

#define XML_TG_FIRST	0x0006

#define XML_TIE_ROOT	0x0007

//=============================================================================
// Fehlercode
//=============================================================================

#define XML_ERROR_ALREADY_DEFINED       1000
#define XML_ERROR_INVALID_ADRESS        1001
#define XML_ERROR_ATTRIBUT_NOT_FOUND    1002
#define XML_ERROR_TREE_EMPTY            1003
#define XML_ERROR_LIST_EMPTY            1004
#define XML_ERROR_UNKNOWN_KEYWORD       1005
#define XML_ERROR_NO_ACCESS             1006
#define XML_ERROR_NO_FILE               1007
#define XML_ERROR_UNEXPECTED_STREAMEND  1008
#define XML_ERROR_ELEMENT_NOT_DEFINED   1009
#define XML_ERROR_DATASET_ERROR         1010
#define XML_ERROR_WRONG_ENDTAG          1011
#define XML_ERROR_UNEXPECTED_CHAR       1012
#define XML_ERROR_NO_PARENT_ENTRY       1013
#define XML_ERROR_PARSER_ERROR          1014
#define XML_ERROR_OPEN_FILE             1015
#define XML_ERROR_BAD_STREAM            1016

//=============================================================================
// Definitionen von Structs
//=============================================================================

typedef char Char; /// md

//##ModelId=396A3C0C02C2
struct CharString {
	//##ModelId=396A3C0C02EC
    Char *ptr;
	//##ModelId=396A3C0C02D6
    size_t len;
};

//##ModelId=396A3C0803AD
struct Attribute {
	//##ModelId=396A3C09000D
    CharString name;
	//##ModelId=396A3C0803D5
	CharString data;
};

//##ModelId=396A3C080009
struct StartElementEvent {
	//##ModelId=396A3C080051
    CharString gi;
	//##ModelId=396A3C08003B
    size_t nAttributes;
	//##ModelId=396A3C080029
    Attribute *attributes;
};

//##ModelId=396A3C0603D2
struct EndElementEvent {
	//##ModelId=396A3C070012
    CharString gi;
};

//##ModelId=396A3C01030C
struct DataEvent {
	//##ModelId=396A3C01032C
    CharString data;
};

struct StartDocumentEvent {
    CharString doctype;
    CharString systemtype;
    CharString version;
	CharString pathname;
};

//##ModelId=396A3BFF01E8
struct ErrorEvent {
	//##ModelId=396A3BFF02A5
    CharString message;
};

//=============================================================================
// Definitionen of Macros
//=============================================================================

// SAX Interface declaration

#define EAG_BEGIN_SAX_MAP() \
public: \
CXmlHandler* startElement(const StartElementEvent & event); \
bool streamElement(ostream & stream, std::string strName, int nLevel) const; \

#define EAG_SAX_ENTRY_DOUBLE(attribute) \
protected: \
	CXmlDouble m_xml##attribute; \
public: \
	double get_##attribute(void); \
	void set_##attribute(double dVal); \

#define EAG_SAX_ENTRY_STRING(attribute) \
protected: \
	CXmlString m_xml##attribute; \
public: \
	CString get_##attribute(void); \
	void set_##attribute(CString& rVal); \

#define EAG_SAX_ENTRY_INTEGER(attribute) \
protected: \
	CXmlInteger m_xml##attribute; \
public: \
	int get_##attribute(void); \
	void set_##attribute(int iVal); \

#define EAG_SAX_ENTRY_BOOLEAN(attribute) \
protected: \
	CXmlBool m_xml##attribute; \
public: \
	bool get_##attribute(void); \
	void set_##attribute(bool bVal); \

#define EAG_SAX_ENTRY_DATETIME(attribute) \
protected: \
	CXmlDateTime m_xml##attribute; \
public: \
	CDateTime get_##attribute(void); \
	void set_##attribute(CDateTime& dtVal); \

#define EAG_SAX_ENTRY_DATE(attribute) \
protected: \
	CXmlDate m_xml##attribute; \
public: \
	CDateTime get_##attribute(void); \
	void set_##attribute(CDateTime& dtVal); \

#define EAG_SAX_ENTRY_TIME(attribute) \
protected: \
	CXmlTime m_xml##attribute; \
public: \
	CDateTime get_##attribute(void); \
	void set_##attribute(CDateTime& dtVal); \

#define EAG_SAX_ENTRY_OBJECT(attribute) \
protected: \
	C##attribute m_xml##attribute; \
public: \
	C##attribute& get_##attribute(void); \


#define EAG_END_SAX_MAP() 

// SAX Interface startElement implementation

#define EAG_BEGIN_SAX_IN(classname) \
CXmlHandler* C##classname##::startElement(const StartElementEvent & event) \
{

#define EAG_SAX_IN_IMPL(attribute,attributestring) \
if (getString(event.gi) == attributestring) \
	return &m_xml##attribute;

#define EAG_END_SAX_IN() \
	return gSwallowTagSet; \
}

// SAX Interface streamElement implementation

#define EAG_BEGIN_SAX_OUT(classname) \
bool C##classname##::streamElement(ostream & stream, std::string strName, int nLevel) const \
{ \
	tabs(stream,nLevel); \

#define EAG_BEGIN_SAX_OUT_MAP() \
  stream << "<" << strName.c_str(); \

#define EAG_SAX_OUT_ATTRIBUTE(attribute,attributestring) \
	stream << " " << attributestring << "=\"" << m_##attribute << "\"";

#define EAG_END_SAX_OUT_MAP() \
	std::stream << ">" << std::endl; \

#define EAG_SAX_OUT_IMPL(attribute,attributestring) \
	if(!m_xml##attribute.streamElement(stream, attributestring, (nLevel +1))) \
		return false;

#define EAG_END_SAX_OUT() \
	tabs(stream,nLevel); \
	stream << "</" << strName.c_str() << ">"; stream << std::endl; \
	return true; \
}

// interface implementation
#define EAG_SAX_ENTRY_DOUBLE_IMPL(classname, attribute) \
double C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(double dVal) \
{ \
	m_xml##attribute = dVal; \
}

#define EAG_SAX_ENTRY_INTEGER_IMPL(classname, attribute) \
int C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(int iVal) \
{ \
	m_xml##attribute = iVal; \
}

#define EAG_SAX_ENTRY_BOOLEAN_IMPL(classname, attribute) \
bool C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(bool bVal) \
{ \
	m_xml##attribute = bVal; \
}

#define EAG_SAX_ENTRY_STRING_IMPL(classname, attribute) \
CString C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute.string(); \
} \
void C##classname##::set_##attribute(CString& rVal) \
{ \
	m_xml##attribute = rVal.GetBuffer(rVal.GetLength()); \
}

#define EAG_SAX_ENTRY_DATETIME_IMPL(classname, attribute) \
CDateTime C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(CDateTime& dtVal) \
{ \
	m_xml##attribute = dtVal.GetDATE(); \
}

#define EAG_SAX_ENTRY_DATE_IMPL(classname, attribute) \
CDateTime C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(CDateTime& dtVal) \
{ \
	m_xml##attribute = dtVal.GetDATE(); \
}

#define EAG_SAX_ENTRY_TIME_IMPL(classname, attribute) \
CDateTime C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
} \
void C##classname##::set_##attribute(CDateTime& dtVal) \
{ \
	m_xml##attribute = dtVal.GetDATE(); \
}

#define EAG_SAX_ENTRY_OBJECT_IMPL(classname, attribute) \
C##attribute& C##classname##::get_##attribute(void) \
{ \
	return m_xml##attribute; \
}

#endif

//=============================================================================
//                                  E O F
//=============================================================================
