// CryptFile.cpp: Implementierung der Klasse CCryptFile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cryptfile.h"

namespace eag {

BOOL CCryptFile::Open( LPCTSTR lpszFileName, UINT nOpenFlags)
{
	CFile raw;
	
	// test for "not only writing"
	if ((nOpenFlags & (CFile::modeReadWrite|CFile::modeWrite))==0)
	{
		if (!raw.Open(lpszFileName,nOpenFlags))
			return FALSE;
		
		unsigned int n;
		n=(unsigned int )raw.GetLength();
		unsigned char *p=(unsigned char *)malloc(n);
		raw.Read(p,n);  // read entire file
		raw.Close();
		// decrypt
		for (unsigned i=0;i<n;i++)
			p[i]^=0xFF;
		Attach(p,n);
	}
	else
		m_csBasefile=lpszFileName;

	return TRUE;
}

void CCryptFile::Close()
{
	CFileException pError;
	CFile raw;

	// if saving, encrypt data and write to real file
	if (!m_csBasefile.IsEmpty())
	{
		unsigned int  n= (unsigned int)GetLength();
		if (!raw.Open(m_csBasefile,
			CFile::modeWrite|CFile::modeCreate|CFile::shareExclusive,
			&pError))
			throw &pError;
		unsigned char *p=Detach();
		// encrypt
		for (unsigned i=0;i<n;i++)
			p[i]^=0xFF;
		raw.Write(p,n);
		raw.Close();
		free(p);
	}
}

UINT CCryptFile::Read( CString& rBuf )
{
	rBuf.Empty();

	CMemFile::Read(rBuf.GetBuffer((int)GetLength()), (int)GetLength());
	rBuf.ReleaseBuffer();

	return rBuf.GetLength();
}

void CCryptFile::Write( CString& rBuf )
{
	CMemFile::Write(rBuf.GetBuffer(rBuf.GetLength()), rBuf.GetLength());
	rBuf.ReleaseBuffer();
}

} //end of namespace eag