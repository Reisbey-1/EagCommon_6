// InitParser.h: Schnittstelle für die Klasse CInitParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INITPARSER_H__EC850921_C77F_4F2A_BE23_1A21010FB696__INCLUDED_)
#define AFX_INITPARSER_H__EC850921_C77F_4F2A_BE23_1A21010FB696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "DString.h"

namespace eag {

#ifdef INITPARSER_EXPORTS
#define INITPARSER_API __declspec(dllexport)
#else
#define INITPARSER_API __declspec(dllimport)
#endif


class INITPARSER_API CInitParser  
{
public:
	void GetNextToken (DString &r_dstrSource, CString &Key, CString &value, CString& trash);
	CInitParser();
	virtual ~CInitParser();

protected:
	void RemoveLastLF (wchar_t* txt);
};

}; // end of namespace

#endif // !defined(AFX_INITPARSER_H__EC850921_C77F_4F2A_BE23_1A21010FB696__INCLUDED_)
