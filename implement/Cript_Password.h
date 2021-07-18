/*
//=============================================================================
//
// = PROJECT
//
//
// = SUMMARY
//
//     Header-File f�r einen einfachen Passwort-Algorithmus 
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
//     und Entschl�sselung eines beliebigen Strings
// 
//
//=============================================================================
    
{

protected:
	DString m_CryptKey;

public:

	CCript_Password();
		// Konstruktor des Passwort-Moduls;
		// Ver- und Entschl�sselung mit Standard-Schl�ssel

	CCript_Password(CString csCryptKey);
		// Konstruktor des Passwort-Moduls;
		// <csCryptKey> Schl�ssel f�r die Ver- und Entschl�sselung

//
// = ZUGRIFFSMETHODEN
//
	void SetCryptKey(CString csCryptKey);
		// Setzt Schl�ssel zur Ver-und Entschl�sselung
		// <csCryptKey> neuer Schl�ssel

	DString Encrypt(CString csString);
		// Verschl�sselt den �bergebenen String
		// <csString> zu verschl�sselnder String
		// R�ckgabe: verschl�sselter String im Hex-Code

	DString Decrypt(CString csCryptString);
		// Entschl�sselt den �bergebenen String
		// <csCryptString> zu entschl�sselnder String
		// R�ckgabe: entschl�sselter String

};

}; // end of namespace eag

#endif // of #ifndef Cript_Password_H

// ============================================================================




