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
//     Header-File für die Klassen zur Definition von typesafe Handles
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

#ifndef _XML_XMLHANDLE_H_
#define _XML_XMLHANDLE_H_

#include "xmldef.h"

namespace eag 
{

//=============================================================================

class CXmlElementHandle;
class CXmlItemHandle;

//=============================================================================

typedef CXmlElementHandle	HXMLELEMENT;
typedef CXmlItemHandle		HXMLITEM;

//=============================================================================
//
// = TITLE
//
//     CXmlElementHandle
//
// = CLASSTYPE
//
//     Abstract
//
// = AUDIENCE
//     
//     XML PDN
//
// = DESCRIPTION
//
//     Die Klasse CXmlElementHandle ermöglicht die typesafe Übergabe
//     von ELEMENT-HANDLE der XML-Elementstruktur
//
//=============================================================================

//##ModelId=396A3C0C00D7
class XMLSTRUCT_API CXmlElementHandle
{
protected:
	//##ModelId=396A3C0C0151
  unsigned long val;

public:
	//##ModelId=396A3C0C01AB
	CXmlElementHandle();
	//##ModelId=396A3C0C01B4
	CXmlElementHandle(const CXmlElementHandle& h);
	//##ModelId=396A3C0C01BF
	CXmlElementHandle(const unsigned long l);
	//##ModelId=396A3C0C01C9
	CXmlElementHandle(const int i);
	//##ModelId=396A3C0C01AA
	~CXmlElementHandle() {};
	//##ModelId=396A3C0C01A0
	unsigned long Value(void);
	//##ModelId=396A3C0C0196
	BOOL isValid(void);
	//##ModelId=396A3C0C0179
	CXmlElementHandle& operator=(const CXmlElementHandle& h);
	//##ModelId=396A3C0C0183
	CXmlElementHandle& operator=(const unsigned long l);
	//##ModelId=396A3C0C018C
	CXmlElementHandle& operator=(const int i);

	//##ModelId=396A3C0C00E1
	friend int operator==(const CXmlElementHandle& h1, const CXmlElementHandle& h2);
	//##ModelId=396A3C0C00F5
	friend int operator!=(const CXmlElementHandle& h1, const CXmlElementHandle& h2);
	//##ModelId=396A3C0C0100
	friend int operator==(const CXmlElementHandle& h,  const unsigned long l);
	//##ModelId=396A3C0C0113
	friend int operator!=(const CXmlElementHandle& h,  const unsigned long l);
	//##ModelId=396A3C0C011E
	friend int operator==(const CXmlElementHandle& h,  const int i);
	//##ModelId=396A3C0C013C
	friend int operator!=(const CXmlElementHandle& h,  const int i);

protected:
	//##ModelId=396A3C0C015A
	void SetValue(const CXmlElementHandle& h);
	//##ModelId=396A3C0C0164
	void SetValue(const unsigned long l);
	//##ModelId=396A3C0C016E
	void SetValue(const int i);
};


inline int operator==(const CXmlElementHandle& h1, const CXmlElementHandle& h2) {
  return h1.val == h2.val;
}

inline int operator!=(const CXmlElementHandle& h1, const CXmlElementHandle& h2) {
  return h1.val != h2.val;
}

inline int operator==(const CXmlElementHandle& h, const unsigned long l) {
  return h.val == l;
}

inline int operator!=(const CXmlElementHandle& h, const unsigned long l) {
  return h.val != l;
}

inline int operator==(const CXmlElementHandle& h, const int i) {
  return h.val == (unsigned int)i;
}

inline int operator!=(const CXmlElementHandle& h, const int i) {
  return h.val != (unsigned int)i;
}

//=============================================================================
//
// = TITLE
//
//     CXmlItemHandle
//
// = CLASSTYPE
//
//     Abstract
//
// = AUDIENCE
//     
//     XML PDN
//
// = DESCRIPTION
//
//     Die Klasse CXmlItemHandle ermöglicht die typesafe Übergabe
//     von ITEM-HANDLE der XML-Elementstruktur
//
//=============================================================================

//##ModelId=396A3C0101FE
class XMLSTRUCT_API CXmlItemHandle
{
protected:
	//##ModelId=396A3C010263
  unsigned long val;

public:
	//##ModelId=396A3C0102C8
	CXmlItemHandle();
	//##ModelId=396A3C0102D0
	CXmlItemHandle(const CXmlItemHandle& h);
	//##ModelId=396A3C0102DB
	CXmlItemHandle(const unsigned long l);
	//##ModelId=396A3C0102E4
	CXmlItemHandle(const int i);
	//##ModelId=396A3C0102C7
	~CXmlItemHandle() {};
	//##ModelId=396A3C0102BC
	unsigned long Value(void);
	//##ModelId=396A3C01029F
	BOOL isValid(void);
	//##ModelId=396A3C010282
	CXmlItemHandle& operator=(const CXmlItemHandle& h);
	//##ModelId=396A3C01028B
	CXmlItemHandle& operator=(const unsigned long l);
	//##ModelId=396A3C010295
	CXmlItemHandle& operator=(const int i);

	//##ModelId=396A3C010208
	friend int operator==(const CXmlItemHandle& h1, const CXmlItemHandle& h2);
	//##ModelId=396A3C01021D
	friend int operator!=(const CXmlItemHandle& h1, const CXmlItemHandle& h2);
	//##ModelId=396A3C010228
	friend int operator==(const CXmlItemHandle& h,  const unsigned long l);
	//##ModelId=396A3C01023A
	friend int operator!=(const CXmlItemHandle& h,  const unsigned long l);
	//##ModelId=396A3C010245
	friend int operator==(const CXmlItemHandle& h,  const int i);
	//##ModelId=396A3C010258
	friend int operator!=(const CXmlItemHandle& h,  const int i);

protected:
	//##ModelId=396A3C01026C
	void SetValue(const CXmlItemHandle& h);
	//##ModelId=396A3C010276
	void SetValue(const unsigned long l);
	//##ModelId=396A3C010280
	void SetValue(const int i);
};

inline int operator==(const CXmlItemHandle& h1, const CXmlItemHandle& h2) {
  return h1.val == h2.val;
}

inline int operator!=(const CXmlItemHandle& h1, const CXmlItemHandle& h2) {
  return h1.val != h2.val;
}

inline int operator==(const CXmlItemHandle& h, const unsigned long l) {
  return h.val == l;
}

inline int operator!=(const CXmlItemHandle& h, const unsigned long l) {
  return h.val != l;
}

inline int operator==(const CXmlItemHandle& h, const int i) {
  return h.val == (unsigned int)i;
}

inline int operator!=(const CXmlItemHandle& h, const int i) {
  return h.val != (unsigned int)i;
}

//=============================================================================

} // namespace eag

#endif // #ifndef _XML_XMLHANDLE_H_

//=============================================================================
