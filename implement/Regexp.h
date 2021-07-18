#ifndef __REGEXP_H__
#define __REGEXP_H__

namespace eag {

#ifdef REGEXPUTILITY_EXPORTS
#define REGEXPUTILITY_API __declspec(dllexport)
#else
#define REGEXPUTILITY_API __declspec(dllimport)
#endif

class regexp;

class REGEXPUTILITY_API CRegexp
{
public:
	enum { NSUBEXP = 10 };

	CRegexp();
	CRegexp( LPCTSTR exp, BOOL iCase = 0 );
	CRegexp( const CRegexp &r );
	~CRegexp();
	const CRegexp & operator=( const CRegexp & r );

	bool Match( const TCHAR * s );
	int SubStrings() const;
	
	const CString operator[]( unsigned int i ) const;
	int SubStart( unsigned int i ) const;
	int SubLength( unsigned int i ) const;

	CString GetReplaceString( LPCTSTR source ) const;

	CString GetErrorString() const;
	bool CompiledOK() const;

#if defined( _RE_DEBUG )
	void Dump();
#endif
private:
	const TCHAR * string;	/* used to return substring offsets only */
	mutable CString m_szError;
	regexp * rc;

	void ClearErrorString() const;
	int safeIndex( unsigned int i ) const;

};

} // eag

#endif

