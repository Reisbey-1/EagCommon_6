//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%38F71CE20197.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%38F71CE20197.cm

//## begin module%38F71CE20197.cp preserve=no
//## end module%38F71CE20197.cp

//## Module: StringUtility%38F71CE20197; Package body
//## Subsystem: common%38F7195F0086
//## Source file: Z:\app_hte\common\implement\StringUtility.cpp

//## begin module%38F71CE20197.additionalIncludes preserve=no
//## end module%38F71CE20197.additionalIncludes

//## begin module%38F71CE20197.includes preserve=yes
#include "stdafx.h"
//## end module%38F71CE20197.includes

// StringUtility
#include "StringUtility.h"
//## begin module%38F71CE20197.declarations preserve=no
//## end module%38F71CE20197.declarations

//## begin module%38F71CE20197.additionalDeclarations preserve=yes
//## end module%38F71CE20197.additionalDeclarations


//## Modelname: common%38F717B70177
namespace eag {
	//## begin eag%38F717B70177.initialDeclarations preserve=yes
	//## end eag%38F717B70177.initialDeclarations
	
	// Class Utility eag::CStringUtility 
	
	
	//## Other Operations (implementation)
	//##ModelId=3978398E034E
	BSTR CStringUtility::stdToBSTR (std::string str)
	{
		CString result(str.c_str());
		return result.AllocSysString();
	}

	/// md returnde buffer should be deallocated by caller !!
	wchar_t* CStringUtility::CHARToWCHAR(char* szStr)
	{
/*		wchar_t* szResult;		
		wcstombs(szStr, szResult, sizeof(szStr));
		return szResult;

		const size_t cSize = mbstowcs(NULL, szStr, 0) + 1;*/
		const size_t cSize = strlen(szStr) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, szStr, cSize);

		return wc;
	}

	PCHAR CStringUtility::WCHARToCHAR(PWCHAR szStr)
	{
		//const WCHAR* wc = L"Hello World";
		_bstr_t b(szStr);
		char* szResult = b;
		return szResult;
	}

	std::wstring CStringUtility::stdToWSTR(std::string str)
	{
		int len;
		int slength = (int)str.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), slength, buf, len);
		std::wstring result(buf);
		delete[] buf;
		return result;

	}
	std::string CStringUtility::WSTRToStr(std::wstring wstr)
	{
		setlocale(LC_CTYPE, "");
		std::string s(wstr.begin(), wstr.end());
		return s;
	}
	//##ModelId=3978398E0343
	std::string CStringUtility::bstrToStd (BSTR bstr)
	{
		//## begin eag::CStringUtility::bstrToStd%38F718B2018C.body preserve=yes
		CString csDumy = _T("");
		try
		{
			std::string s((LPCSTR ) csDumy.GetBuffer());
			return s;

		}
		catch ( ... )
		{
			return (LPCSTR) _T("");
		}
		//## end eag::CStringUtility::bstrToStd%38F718B2018C.body
	}
	
	BSTR CStringUtility::xmlStringToBSTR (CXmlString str)
	{
		CString result(str.string());
		return result.AllocSysString();
	}
	
	CXmlString CStringUtility::bstrToXmlString (BSTR bstr)
	{
		std::string s;
		s.empty();
		CXmlString xmlEmpty(s);
		try
		{
			std::string s = bstrToStd(bstr);
			CXmlString xml(s);
			return xml;
		}
		catch ( ... )
		{
			return xmlEmpty;
		}
	}	
	
	// dont forget to free returned bstr   :  SysFreeString(bstr) !!! 
	BSTR CStringUtility::cStringToBSTR (CString cstr)
	{
		return cstr.AllocSysString();
	}
	
	CString CStringUtility::bstrToCString (BSTR bstr)
	{
		try
		{
			CString s;
			if(bstr == NULL)
				return s; // empty for NULL BSTR

			#ifdef UNICODE
				s =  bstr;
			#else
				LPSTR p = s.GetBuffer(SysStringLen(bstr) + 1); 
				::WideCharToMultiByte(CP_ACP,           // ANSI Code Page
					0,									// no flags
					bstr,								// source widechar string
					-1,									// assume NUL-terminated
					p,									// target buffer
					SysStringLen(bstr)+1,				// target buffer length
					NULL,								// use system default char
					NULL);								// don't care if default used
				s.ReleaseBuffer();
			#endif

			return s;
		}
		catch ( ... )
		{
			return _T("");
		}
	}
	
	bool CStringUtility::CStringArrayFromVariant(CStringArray &dest, VARIANT &src) 
	{

		if (src.vt == VT_ARRAY){
			
			SAFEARRAY *psa=src.parray;

			long indice[1];
			BSTR value;
			dest.SetSize(psa->rgsabound->cElements);

			for (indice[0] = 0 ; indice[0] < psa->rgsabound->cElements ; indice[0]++) {
				
				SafeArrayGetElement( psa, indice, &value);
				dest[indice[0]] = bstrToCString(value);
			}
		}
		else {
			return false;
		}
		return true;
	}

	bool CStringUtility::VariantFromCStringArray( VARIANT &dest, CStringArray &src) 
	{

		SAFEARRAYBOUND sab;
		sab.cElements=src.GetSize();
		sab.lLbound=0;

		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &sab); 

		long indice[1];
		for ( indice[0] = 0 ; indice[0] < src.GetSize() ; indice[0]++) {
			SafeArrayPutElement( psa, indice, src[indice[0]].AllocSysString() );
		}

		dest.vt = VT_ARRAY;
		dest.parray=psa;

		return true;
	}
	
	CString CStringUtility::CLSIDFromModulename( CString& rModule )
	{
		CLSID clsid;
		BSTR bstrClsid;
		HRESULT hr;

		try
		{
			hr = CLSIDFromProgID ( rModule.AllocSysString(), &clsid );
			if ( FAILED ( hr ) )
				return _T("");

			hr = StringFromCLSID(clsid, &bstrClsid);
			if ( FAILED ( hr ) )
				return _T("");

			return bstrToCString(bstrClsid);
		}
		catch(...)
		{
			return _T("");
		}
	}

	CString CStringUtility::ModulenameFromCLSID( CString& rId )
	{
		CLSID clsid;
		LPOLESTR pString = NULL;
		CString csModulename("");
		HRESULT hr;

		try
		{
			hr = CLSIDFromString(rId.AllocSysString(), &clsid); 
			if ( FAILED ( hr ) )
				return _T("");

			hr = ProgIDFromCLSID(clsid, &pString);
			if ( FAILED ( hr ) )
				return _T("");

			csModulename = bstrToCString(pString);

            CoTaskMemFree(pString);
		}
		catch(...)
		{
			return _T("");
		}

		return csModulename;
	}

	void CStringUtility::GetNextToken (DString &r_dstrSource, CString &Key, CString &value, CString& trash)
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

	void CStringUtility::RemoveLastLF (wchar_t* txt)
	{
		for (int i=0; txt[i] != 0; i++)
			if ( ((txt[i] == L'\r') &&  (txt[i+1] ==0L   ))  ||
				 ((txt[i] == L'\r') &&  (txt[i+1] == L'\n')) ||
				 ((txt[i] == L'\r') &&  (txt[i+1] == L'\r')) ||
				 ((txt[i] == L'\n') &&  (txt[i+1] == 0L   )) ||
				 ((txt[i] == L'\n') &&  (txt[i+1] == L'\n')) || 
				 ((txt[i] == L'\n') &&  (txt[i+1] == L'\r')) )
				   txt[i] = 0;
	}


	const wchar_t CStringUtility::base64table[] = L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


	 wchar_t CStringUtility::base64_dec( const  wchar_t Ch )
	{
		if ( Ch ) {
			wchar_t * p = (wchar_t*)wcschr( base64table, Ch );    /// DLG

			if ( p )
				return ( wchar_t)( p - base64table );
		}

		// Any other character returns NULL since the character would be invalid.
		return(0);
	}


	void CStringUtility::base64_decode(eag::DString &dstr_in, eag::DString &dstr_out)
	{
		wchar_t c1, c2;
		wchar_t d;

		if (dstr_in.laenge() == 0)
			return;

		unsigned char *in= (unsigned char *)dstr_in.getstr();

		dstr_out.leere();

		for ( ; *in; ) {
			if ( (*in == '\r') || (*in == '\n') ) {
				in++;
				continue;
			}

			if ( *in == '=') break;

			c1 = base64_dec( *in++ );

			c2 = base64_dec( *in++ ); d = (wchar_t)((c1 << 2) + (c2 >> 4)); dstr_out.addstr( &d,1);

			if ( *in == '=') break;

			c1 = base64_dec( *in++ ); d = (wchar_t)((c2 << 4) + (c1 >> 2)); dstr_out.addstr( &d,1);

			if ( *in == '=') break;

			c2 = base64_dec( *in++ ); d = (wchar_t)((c1 << 6) + c2); dstr_out.addstr( &d,1);

		}
	}


	void CStringUtility::base64_encode(eag::DString & source, eag::DString & out, int inclCrLf )
	{
		DWORD           length;
		wchar_t * in;
		int             bytes_out;
		wchar_t            tmpstr[80];
		unsigned long   bitStream;

		in     = (wchar_t *) source.getstr();
		length = source.laenge();

		// Ensure the data is padded with NULL to work the for() loop.
		in[length] = L'\0';

		tmpstr[ 72 ] = L'\0';

		for ( bytes_out = 0; length > 2; length -= 3, in += 3 ) {
			if ( bytes_out == 72 ) {
				out.addstr( tmpstr );
				bytes_out = 0;
				if ( inclCrLf )
					out.addstr( L"\r\n" );
			}

			bitStream = (in[0] << 16) | (in[1] << 8) | in[2];
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream >> 18 );
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream >> 12 );
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream >>  6 );
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream       );
		}

		/* If length == 0, then we're done.
		 * If length == 1 at this point, then the in[0] is the last byte of the file, and in[1] is a binary zero.
		 * If length == 2 at this point, then in[0] and in[1] are the last bytes, while in[2] is a binary zero.
		 * In all cases, in[2] is not needed.
		 */
		if ( length ) {
			if ( bytes_out == 72 ) {
				out.addstr( tmpstr );
				if ( inclCrLf )
					out.addstr( L"\r\n" );

				bytes_out = 0;
			}

			bitStream = (in[0] << 8) | in[1];
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream >> 10 );
			tmpstr[ bytes_out++ ] = B64_Mask( bitStream >>  4 );

			if ( length == 2 )
				tmpstr[ bytes_out++ ] = B64_Mask( bitStream << 2 );
			else
				tmpstr[ bytes_out++ ] = L'=';

			tmpstr[ bytes_out++ ] = L'=';
		}

		if ( bytes_out ) {
			tmpstr[ bytes_out ] = L'\0';
			out.addstr( tmpstr );
			if ( inclCrLf )
				out.addstr( L"\r\n" );
		}
	}

} // namespace eag

//## begin module%38F71CE20197.epilog preserve=yes
//## end module%38F71CE20197.epilog
