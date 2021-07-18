#include "stdafx.h"
#include "registrykey.h"

namespace eag {

// Class CRegistryKey 
/**/
CString CRegistryKey::m_scsBaseKey = "";
BOOL CRegistryKey::m_sbBaseKeySet=FALSE;

void CRegistryKey::set_BaseKey (const CString csBaseKey){

	m_scsBaseKey=csBaseKey;
	m_sbBaseKeySet=TRUE;

};
const CString& CRegistryKey::get_BaseKey ()
{
	return m_scsBaseKey;
}

CRegistryKey::CRegistryKey (const CString csRegSubPath)
      : m_bRegKeyOpen(false),
	  m_bCanWrite(false)
{

	if (!m_sbBaseKeySet) return; //if BaseKey was not set, this class 
								 //can never be used properly!


	CString csRegPath= m_scsBaseKey;
	csRegPath += "\\";
	csRegPath += csRegSubPath;


	if (m_RegKey.Open(HKEY_LOCAL_MACHINE, csRegPath, KEY_READ | KEY_WRITE | KEY_WOW64_32KEY | KEY_ALL_ACCESS) == ERROR_SUCCESS) {
//	if (m_RegKey.Open(HKEY_LOCAL_MACHINE, csRegPath, KEY_READ | KEY_WRITE ) == ERROR_SUCCESS) {
			m_bRegKeyOpen	= true;
		m_bCanWrite		= true;
	}

	else  	{
		if (m_RegKey.Create(HKEY_LOCAL_MACHINE, csRegPath, 0) == ERROR_SUCCESS)
			m_bRegKeyOpen = true;
	}
}

//##ModelId=397839850283
CRegistryKey::~CRegistryKey()
{
	if (m_bRegKeyOpen) 
		m_RegKey.Close();
}

//##ModelId=397839850265
bool CRegistryKey::get (const wchar_t *cRegParameter, DWORD& r_dwValue)
{
	if (m_bRegKeyOpen) {

		LONG lRes = m_RegKey.QueryValue(r_dwValue , (LPCTSTR) cRegParameter );
		
		if (lRes == ERROR_SUCCESS) 
			return true;
	}

	return false;
}

//##ModelId=397839850278
bool CRegistryKey::get (const wchar_t *cRegParameter, CString& r_csValue)
{
	if (m_bRegKeyOpen) {

		DWORD dwValueLength = _MAX_PATH;
	    
		LONG lRes = m_RegKey.QueryValue( r_csValue.GetBuffer(_MAX_PATH) , (LPCTSTR) cRegParameter, &dwValueLength);
		
		r_csValue.ReleaseBuffer();
		
		if (lRes == ERROR_SUCCESS) 
			return true;
	}

	return false;
}

//##ModelId=397839850247
bool CRegistryKey::set (const wchar_t *cRegParameter, const DWORD dwValue)
{
	if (! m_bCanWrite)
		return false;

	if (m_bRegKeyOpen) {

		LONG lRes = m_RegKey.SetValue(  dwValue , (LPCTSTR)cRegParameter );
		
		if (lRes == ERROR_SUCCESS) 
			return true;
	}

	return false;
}

//##ModelId=39783985025A
bool CRegistryKey::set (const wchar_t *cRegParameter, const CString csValue)
{
	if (! m_bCanWrite)
		return false;

	if (m_bRegKeyOpen) {

		LONG lRes = m_RegKey.SetValue(  csValue , (LPCTSTR) cRegParameter );
		
		if (lRes == ERROR_SUCCESS) 
			return true;
	}

	return false;
}

} // namespace


