/*
//=============================================================================
//
// = PROJECT
//
//
// = SUMMARY
//
//     Header-File für einen einfachen Passwort-Algorithmus 
//
// = AUTHOR(S)
//
//     Roland Kopetzky  (created 10.10.1996)
//
// = COPYRIGHT
//
//     2001  ennovatis Stuttgart -- All Rights Reserved
//
// = DATE RELEASED
//
//     $Date: 2002/01/25 16:31:40 $
//
//=============================================================================
*/
    
#ifndef Cript_Password_H
#define Cript_Password_H

#include <stdio.h>
#include <stdlib.h>
	// Standard-Klassen
#include "DString.h"
	// String-Klasse

//=============================================================================
namespace eag {

#ifdef LICENSE_EXPORTS
#define LICENSE_API __declspec(dllexport)
#else
#define LICENSE_API __declspec(dllimport)
#endif

class LICENSE_API CCript_Password

//=============================================================================
//
// = TITLE
//
//     CPDN_Password
//
// = CLASSTYPE
//
//     Concrete
//
// = AUDIENCE
//     
//     PDN
//
// = DESCRIPTION
//
//     Die Klasse CPassword liefert Methoden zur Ver-
//     und Entschlüsselung eines beliebigen Strings
// 
//
//=============================================================================
    
{

protected:
	DString m_CryptKey;

public:

	CCript_Password();
		// Konstruktor des Passwort-Moduls;
		// Ver- und Entschlüsselung mit Standard-Schlüssel

	CCript_Password(CString csCryptKey);
		// Konstruktor des Passwort-Moduls;
		// <csCryptKey> Schlüssel für die Ver- und Entschlüsselung

//
// = ZUGRIFFSMETHODEN
//
	void SetCryptKey(CString csCryptKey);
		// Setzt Schlüssel zur Ver-und Entschlüsselung
		// <csCryptKey> neuer Schlüssel

	DString Encrypt(CString csString);
		// Verschlüsselt den übergebenen String
		// <csString> zu verschlüsselnder String
		// Rückgabe: verschlüsselter String im Hex-Code

	DString Decrypt(CString csCryptString);
		// Entschlüsselt den übergebenen String
		// <csCryptString> zu entschlüsselnder String
		// Rückgabe: entschlüsselter String

};

}; // end of namespace eag

#endif // of #ifndef Cript_Password_H

// ============================================================================




