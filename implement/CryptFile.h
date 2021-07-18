// CryptFile.h: Schnittstelle für die Klasse CCryptFile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRYPTFILE_H__ED9E39B0_9EC0_11D5_B306_000374890932__INCLUDED_)
#define AFX_CRYPTFILE_H__ED9E39B0_9EC0_11D5_B306_000374890932__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace eag {

#ifdef LICENSE_EXPORTS
#define LICENSE_API __declspec(dllexport)
#else
#define LICENSE_API __declspec(dllimport)
#endif

class LICENSE_API CCryptFile : public CMemFile   
{
public:
	BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	void Close();
	UINT Read(CString& rBuf);
	void Write(CString& rBuf);

protected:
	CString m_csBasefile;
};

}; // end of namespace eag

#endif // !defined(AFX_CRYPTFILE_H__ED9E39B0_9EC0_11D5_B306_000374890932__INCLUDED_)
