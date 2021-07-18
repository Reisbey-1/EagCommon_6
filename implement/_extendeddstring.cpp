//
// ExtededDString.cpp: 
//

#include "stdafx.h"
#include "ExtendedDString.h"

namespace eag {

//##ModelId=3978398301C1
ExtendedDString::ExtendedDString() :
m_pBSTR(NULL),m_bBSTR_sync(false)
{

}

ExtendedDString::ExtendedDString(const wchar_t *initstr) : m_pBSTR(NULL), m_bBSTR_sync(false) {
	DString::operator= (initstr);
}

ExtendedDString::ExtendedDString(const DString& s) { //Copyconstructor: WICHTIG

	init();

	//===========================================
	// this ist jetzt initialisiert, das heißt
	// kopiere jetzt die einzelnen Speicherblöcke:
	//===========================================

	*this = s;
};
//##ModelId=397839830136
ExtendedDString::~ExtendedDString()
{
	ReleaseBSTR();
}

//##ModelId=39783983017C
long ExtendedDString::InsertReturns()
{
	long length=laenge();
	if (0 == length) return 0;

	long iNewLines = CountChars(L'\n');

	wchar_t * pcNewBuffer = new wchar_t [length+iNewLines+1];

	long j=0;
	long i=0;
	long iInserts=0;
	getstr();

	if (L'\n' == Ausgabe[i] ) {
		pcNewBuffer[j] = L'\r';
		j++;
		iInserts++;
	}

	pcNewBuffer[j] = Ausgabe[i];
	i++;
	j++;

	for (  ; i < length; i++ ) {

		if ((Ausgabe[i]	 == L'\n') &&
			(Ausgabe[i-1] != L'\r')) { // then insert return:

			pcNewBuffer[j] = L'\r';
			j++;
			pcNewBuffer[j] = Ausgabe[i];
			iInserts++;
		}
		else {
			pcNewBuffer[j] = Ausgabe[i];
		}
		j++;
	}	
	leere();
	addstr(pcNewBuffer,j);

	delete [] pcNewBuffer;

	return iInserts;
}

/*
ExtendedDString::ExtendedDString(const CString& s) { //Copyconstructor: WICHTIG

	init();

	//===========================================
	// this ist jetzt initialisiert, das heißt
	// kopiere jetzt die einzelnen Speicherblöcke:
	//===========================================

	//*this = s;
};
*/
//##ModelId=397839830185
long ExtendedDString::CountChars(char c)
{
	long ln=0;
	long length=laenge();
	getstr();
	for (int i=0; i < length; i++)
		if (Ausgabe[i] == c) ln++;
	return ln;
}

//##ModelId=397839830190
void ExtendedDString::Split(CStringArray & cstrArray, wchar_t cSplitChar)
{
	long sizeofarray = CountChars(cSplitChar)+1;
	cstrArray.SetSize(sizeofarray);

	wchar_t * cpTmpBuf = new wchar_t[laenge()+1];
	for (long i = 0 ; i < sizeofarray ; i++ ) {
		get( cpTmpBuf, laenge()+1 ,cSplitChar);
		cstrArray[i] = cpTmpBuf;
		if (cSplitChar == L' ')
			get( cpTmpBuf, 2 , L'\n');
		else
			get( cpTmpBuf, 2 , L' ');
	}

	rewind();
	delete cpTmpBuf;
}


//##ModelId=397839830171
bool 
ExtendedDString::Replace(long lStartPos, long lEndPos, const wchar_t * pcCharReplaceString){
	
	long lSizeOfReplacement;
	long lOrginalLength = laenge();

	if (( lEndPos - lStartPos) < 0 ) return false;
	if (lEndPos > lOrginalLength) return false;
	if (lStartPos > lOrginalLength ) return false;
	if (lStartPos < 0 ) return false;


	if (pcCharReplaceString) {
		lSizeOfReplacement = wcslen(pcCharReplaceString);
	}
	else 
		lSizeOfReplacement = 0L;

	getstr(); 
	leere();
	addstr(Ausgabe, lStartPos);
	addstr(pcCharReplaceString, lSizeOfReplacement);
	addstr(Ausgabe + lEndPos ,lOrginalLength - lEndPos );

	return true;
}


int ExtendedDString::Replace(const wchar_t *cReplace, const wchar_t *cReplacement, bool bCaseInsensitive, int iCount, int iSkip)
{

	long lLastPos			= 0;
	int iReplacements		= 0;
	int iReplacementLength	= wcslen(cReplace);
	
	for ( int iCounts = 0 ; true ; iCounts++) {

		if ( bCaseInsensitive )
			lLastPos = suche_case_insensitive_ab_position(cReplace,lLastPos);
		else
			lLastPos = suche_ab_position(cReplace,lLastPos);

		if ( lLastPos >=0 ) {
		
			if (iCounts < iSkip ) {
				lLastPos++;
				continue;		
			} 

			if ( iCount != 0 ) {
			
				Replace(lLastPos, lLastPos+iReplacementLength, cReplacement );
				lLastPos += iReplacementLength;
				iReplacements++;
			}
			else 
				lLastPos++;

			if (iCount > 0 && iCount == iReplacements ) {
				return iReplacements;
			} 

		}
		else {
			if ( iCount != 0 )
				return 	iReplacements;		
			else
				return iCounts;
		}
	}

	return 0;
}


//##ModelId=39783983015D
BSTR 
ExtendedDString::GetBSTR(){

/*	if (!m_bBSTR_sync || !A_sync) {

		union_US_UL ulLaenge;
		ulLaenge.ul = ( unsigned long ) laenge();

		ReleaseBSTR();
		getstr(); //Set Ausgabe to a valid value

		if (ulLaenge.ul == 0 ) {
			m_bBSTR_sync = true;
			return NULL;
		}
		
		m_pBSTR = (BSTR)new unsigned short [ulLaenge.ul+3];  /// DLG

		memset(m_pBSTR, 0 , sizeof(unsigned short) * (ulLaenge.ul +3)) ;

		ulLaenge.ul *= 2;
		*m_pBSTR		= ulLaenge.us[0];
		*(m_pBSTR+1)	= ulLaenge.us[1];

		if ( MultiByteToWideChar( CP_ACP, 0, Ausgabe, ulLaenge.ul/2, m_pBSTR+2, ulLaenge.ul/2+1) != (long)ulLaenge.ul/2 ){
		
			ReleaseBSTR();
			return NULL;

		}

	
		m_bBSTR_sync = true;
	}
*/
	if (m_pBSTR)
		return (m_pBSTR+2);
	else
		return NULL;
}


//##ModelId=39783983014A
void  
ExtendedDString::ReleaseBSTR(){
	
	if (m_pBSTR) {
		delete (m_pBSTR);	
		m_pBSTR=NULL;
	}
};


unsigned long 
ExtendedDString::SetBSTR(BSTR pBSTR){
	leere();
	return AddBSTR(pBSTR);
};	

//##ModelId=397839830140
unsigned long  
ExtendedDString::AddBSTR(BSTR  pBSTR){

	union_US_UL ulLaenge;
	ulLaenge.ul = 0;
	unsigned long iWrittenChars = 0;

	if (pBSTR) {
		
		ulLaenge.us[0] = *(pBSTR-2);
		ulLaenge.us[1] = *(pBSTR-1);
	/*
		if ( ulLaenge.ul > 0 ) {

			wchar_t *pBuffer = new wchar_t[ulLaenge.ul/2+1];
			memset(pBuffer, 0, ulLaenge.ul/2 + 1);

			iWrittenChars = WideCharToMultiByte(CP_ACP, 0, pBSTR, ulLaenge.ul/2, pBuffer, ulLaenge.ul/2+1, NULL, NULL);
			
			
			addstr(pBuffer, iWrittenChars );	// Füge String mit der Länge iWrittenChars an

			delete pBuffer;
		}
		*/

		std::wstring  wsVar;
		wsVar.assign(pBSTR);
		iWrittenChars = wsVar.length();
		addstr(wsVar.c_str(), iWrittenChars);
		
	}

	return iWrittenChars;
};


BSTR ExtendedDString::DetachBSTR()
{
	return ::SysAllocString(GetBSTR());
}


HRESULT ExtendedDString::AttachBSTR(BSTR src)
{
	SetBSTR(src );
	::SysFreeString(src);
	return S_OK;
}

//##ModelId=3978398301A4
wchar_t * ExtendedDString::FindOneOf(const wchar_t * pcOneOf)
{
	wchar_t * pcSaerch=getstr(); //Set Ausgabe to a valid value
	long lStringLength = laenge(); 
	long lSearchLength = wcslen(pcOneOf);
	long lPosOneOf;

    for (long l=0 ; l < lStringLength ; l++ ) {
        for ( lPosOneOf = 0 ; lPosOneOf < lSearchLength ; lPosOneOf ++ ) {
            if (pcSaerch[l] == pcOneOf[lPosOneOf])
                return pcSaerch+l ;
        }
    }
    return NULL;
}

} // namespace

