// InitParser.cpp: Implementierung der Klasse CInitParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InitParser.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
namespace eag {

CInitParser::CInitParser()
{

}

CInitParser::~CInitParser()
{

}

void CInitParser::GetNextToken(DString &r_dstrSource, CString &Key, CString &value, CString &trash)
{
	int sizeofsource = r_dstrSource.laenge();

	wchar_t *tmp = new wchar_t[sizeofsource+1];

	do 
	{
		_wcsnset(tmp,0,sizeofsource);
	
		r_dstrSource.get(tmp,sizeofsource,'<');
		trash = tmp;
		r_dstrSource.get(tmp,2,'>');
		
		_wcsnset(tmp,0,sizeofsource);
		r_dstrSource.get(tmp,sizeofsource,'>');
		Key = tmp;

		r_dstrSource.get(tmp,2,' ');

		_wcsnset(tmp,0,sizeofsource);
		r_dstrSource.get(tmp,sizeofsource,'\n');
		RemoveLastLF(tmp);
		value = tmp;

		r_dstrSource.get(tmp,2,' ');

	} while (Key.GetLength() ? (Key[0] == '*') : FALSE);

	delete  tmp;

	value.TrimLeft();
	value.TrimRight();

	return ;
}

void CInitParser::RemoveLastLF(wchar_t *txt)
{
	for (int i=0; txt[i] != 0; i++)
		if ( ((txt[i] == '\r') &&  (txt[i+1] == 0   )) ||
			 ((txt[i] == '\r') &&  (txt[i+1] == '\n')) ||
			 ((txt[i] == '\r') &&  (txt[i+1] == '\r')) ||
			 ((txt[i] == '\n') &&  (txt[i+1] == 0   )) ||
			 ((txt[i] == '\n') &&  (txt[i+1] == '\n')) || 
			 ((txt[i] == '\n') &&  (txt[i+1] == '\r')) )
			   txt[i] = 0;
}


} // end of namespace