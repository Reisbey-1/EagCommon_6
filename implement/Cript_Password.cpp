// PDN_Password Implementation File
//

#include "stdafx.h"

#include "Cript_Password.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPDN_Password - Konstruktoren
namespace eag {

CCript_Password::CCript_Password()
{
	m_CryptKey = L"Willi Wunder im Wunderland";
}

CCript_Password::CCript_Password(CString csCryptKey)
{
	m_CryptKey = csCryptKey;
}

/////////////////////////////////////////////////////////////////////////////
// CPDN_Password - Zugriffsmethoden

// SetCryptKey
//
// Ändern den Schlüssel

void CCript_Password::SetCryptKey(CString csCryptKey)
{
	m_CryptKey = csCryptKey;
}

// Encrypt
//
// Verschlüsselt den übergebenen String

DString CCript_Password::Encrypt(CString csString)
{
	long B, i, a;
	char  buffer[3];

	DString sStrg = csString;
	DString sPass = m_CryptKey;
	DString sCryptStrg ;

	// Verschlüsseln
	a = 0;
	for (i=0; i < sStrg.laenge(); i++)
	{
		B=(int)sPass[a];
		a++;
		if (a == m_CryptKey.laenge())
			a=0;

		sCryptStrg << (wchar_t)((int)sStrg[i] ^ B);
	}

	sStrg.leere();
	// Umwandeln in Hex-Code
	for (i=0; i < sCryptStrg.laenge() ; i++)
	{
		unsigned int usi = (unsigned char) sCryptStrg[i];
		sprintf( buffer, "%02X", usi );
		sStrg << buffer;
	}

	return sStrg;
}

// Decrypt
//
// Entschlüsselt den übergebenen String

DString CCript_Password::Decrypt(CString csCryptString)
{
	DString sStrg = csCryptString;
	DString sPass = m_CryptKey;
	DString sDeCryptStrg;

	long wert, i, a, B;
	wchar_t sLeft[3];

	// Umwandlung von Hex-Code in String
	do { 
		sStrg.get(sLeft,3,L'\0');
		if ( sStrg.gcount() == 0 ) 
			break;
		wert=(int) wcstol(sLeft,'\0',16); 
		sDeCryptStrg << (wchar_t)wert;

	} while ( sStrg.gcount() > 0 );

	sStrg.leere();

	// Entschlüsselung
	a = 0;
	for (i=0; i < sDeCryptStrg.laenge(); i++)
	{
		B=(int)sPass[a];
		a++;
		if (a == m_CryptKey.laenge())
			a=0;

		sStrg << (wchar_t)((int)sDeCryptStrg[i] ^ B);
	}

	return sStrg;
}

} //end of namespace eag

/////////////////////////////////////////////////////////////////////////////
