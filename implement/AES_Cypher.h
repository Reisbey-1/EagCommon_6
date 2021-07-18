// AES_Cypher.h: Schnittstelle für die Klasse CAES_Cypher.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AES_CYPHER_H__BC6C92B9_53BC_4743_A279_12A1C50B23FC__INCLUDED_)
#define AFX_AES_CYPHER_H__BC6C92B9_53BC_4743_A279_12A1C50B23FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
Encrypting a data block is four-step process:
  - #use the AES library
  - obtain a 16 byte data block
  - obtain a correctly-sized key block
  - call the appropriate AES encryption function

The example from Appendix C.1 uses a 128-key to encrypt the plaintext:
   #use "AES.LIB"

   unsigned char pt[16] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff };

   unsigned char k[16]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

   unsigned char ct[16];

   AES_128_Cipher(pt, ct, k);

The encrypted version of the plaintext is now available in the ct[] array.

Decrypting is similar:
   AES_128_Decipher(ct, pt, k);

*/

#include "DString.h"


namespace eag {

#ifdef LICENSE_EXPORTS
#define LICENSE_API __declspec(dllexport)
#else
#define LICENSE_API __declspec(dllimport)
#endif


class LICENSE_API CAES_Cypher  
{
public:
	CAES_Cypher();
	virtual ~CAES_Cypher();
	
	
private:
	static const unsigned char AES_SBoxTable[];
	static const unsigned char AES_InvSBoxTable[];
	static const unsigned long AES_RconTable[];
	
	
	unsigned long AES_SubWord( unsigned long w );
	unsigned long AES_RotWord( unsigned long w );
	bool AES_KeyExpand(CString &cskey, unsigned long **w, int &Nk);
	void AES_AddRoundKey(unsigned char state[4][4], unsigned long *w, int StartW, int Nb);
	void AES_SubBytes( unsigned char state[4][4], int Nb );
	void AES_ShiftRows( unsigned char state[4][4] );
	inline unsigned char AES_Func2x( unsigned char x );
	inline unsigned char AES_Func3x( unsigned char x );
	inline unsigned char AES_Func9x( unsigned char x );
	inline unsigned char AES_FuncBx( unsigned char x );
	inline unsigned char AES_FuncDx( unsigned char x );
	inline unsigned char AES_FuncEx( unsigned char x );
	void AES_MixColumns( unsigned char state[4][4] );
	void AES_Cipher(unsigned char *in, unsigned char *out, unsigned long *w, int Nk);
	void AES_InvShiftRows( unsigned char state[4][4] );
	void AES_InvSubBytes( unsigned char state[4][4], int Nb );
	void AES_InvMixColumns( unsigned char state[4][4] );
	void AES_InvCipher(unsigned char *in, unsigned char *out, unsigned long *w, int Nk);
	
public:
	// if dstrTarget and dstrSource are the same, in place encription will be happend
	// cskey.length  must be 16 (128bit),24(192bit) or 32(256bit). Any other value will fail!!
	bool AES_Encript( DString& dstrTarget, DString& dstrSource, CString &cskey);

	bool AES_Decript( DString& dstrTarget, DString& dstrSource, CString &cskey);

};

} // end of namespace

#endif // !defined(AFX_AES_CYPHER_H__BC6C92B9_53BC_4743_A279_12A1C50B23FC__INCLUDED_)
