// ExtededDString.h
// Extended Dynamic String
//////////////////////////////////////////////////////////////////////

#if !defined(_ExtededDString_h_)
#define _ExtededDString_h_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "dstring.h"

namespace eag {

#ifdef EXTENDEDDSTRING_EXPORTS
#define EXTENDEDDSTRING_API __declspec(dllexport)
#else
#define EXTENDEDDSTRING_API __declspec(dllimport)
#endif

//##ModelId=397839830031
class EXTENDEDDSTRING_API ExtendedDString : public DString  
{
public:
	int Replace(const wchar_t *cReplace, const wchar_t *cReplacement, bool bCaseInsensitive = false, int iCount=-1, int iSkip = 0); // iCount == -1 : replace every 'cReplace'
																			   // iCount == 0 : just report count of 'cReplace'
																			   // iCount > 0 : replace iCount
																			   // iSkip > 0 : skip first n*iSkip of 'cReplace' 
	BSTR DetachBSTR();
	HRESULT AttachBSTR(BSTR src);
	ExtendedDString();
	
	
	//##ModelId=3978398301B7
	ExtendedDString(const wchar_t *initstr); // : m_pBSTR(NULL), m_bBSTR_sync(false){
	//	DString::operator= (initstr);
	//}

	
	
	ExtendedDString(const DString& s) ;
	//ExtendedDString(const CString& s);  /// MD

	//##ModelId=3978398301A4
	wchar_t * FindOneOf(const wchar_t *pcOneOf);
	//##ModelId=397839830190
	void Split(CStringArray &cstrArray, wchar_t cSplitChar);
	//##ModelId=397839830185
	long CountChars(char c);
	//##ModelId=39783983017C
	long InsertReturns();
	//##ModelId=397839830171
	bool Replace(long lStartPos, long lEndPos, const wchar_t * pcCharReplaceString);

	/** BSTR Funktioen dienen dem Umgang mit MS BSTR. Insbesondere wird hier die Konvertierung
	von BSTR in einfache Zeichenfolgen und Umgekehrt implementiert. Eine Länderspezifische
	Konvertierung wird nicht berücksichtigt. Unter Umständen gehen Werte bei der Konvertierung
	von BSTR -> char verloren.
	*/
	//##ModelId=39783983015D
	BSTR GetBSTR(void);
	//##ModelId=39783983014A
	void ReleaseBSTR(void);
	//##ModelId=397839830140
	unsigned long SetBSTR(BSTR pBSTR);

//	ExtendedDString& operator<< (BSTR pBSTR);

	unsigned long AddBSTR(BSTR pBSTR);		
	



	//##ModelId=3978398301C1
	//##ModelId=397839830136
	virtual ~ExtendedDString();

	//##ModelId=397839830121
	long operator=(const wchar_t *zeichen){return DString::operator=(zeichen);};

	//##ModelId=39783983012C
	ExtendedDString& operator= (const ExtendedDString& ob) { 
		DString::operator=(ob);
		return *this;
	};

	//DString& operator= (const char *zeichen){return DString::operator=(ob);};

protected:

	typedef union union_US_UL {
		unsigned short us[2];
		unsigned long  ul;
	}varunion_US_UL;
/**/

	//##ModelId=397839830103
	BSTR m_pBSTR;
	/**
	Flag, das die Synchronität zwischen BSTR und <BR>
	internenDaten anzeigt.<BR>
	*/
	//##ModelId=39783983009E
	BOOL m_bBSTR_sync;
};

} // namespace

#endif // _ExtededDString_h_
