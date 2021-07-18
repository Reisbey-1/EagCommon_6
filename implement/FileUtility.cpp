#include "stdafx.h"
#include "FileUtility.h"
#include "StringUtility.h"

#include <direct.h>

#define PATHEND _T('\\')

namespace eag {

  // Class CommonUtilities::CFileUtility 

  CFileUtility::CFileUtility()
  {
  }


  CFileUtility::~CFileUtility()
  {
  }

  //## Other Operations (implementation)
  bool CFileUtility::existFile (const std::string& sFullPathFileName)
  {
	  const std::wstring wsFullPathFileName  =   CStringUtility::stdToWSTR(sFullPathFileName);
	  if (GetFileAttributes(wsFullPathFileName.c_str()) == 0xffffffff)
		  return (false);
	  
	  return (true);
  }

  bool CFileUtility::copyFile (const std::string &sDestination, const std::string &sSource, const bool bOverwrite)
  {
    if (existFile (sSource))
		// does not overwrite existing files
		if ( CopyFile((LPCWSTR)(CStringUtility::stdToWSTR(sSource).c_str()), (LPCWSTR)(CStringUtility::stdToWSTR(sDestination).c_str()), !bOverwrite) )
			return ( existFile(sDestination) );

	return (false); 
  }

  bool CFileUtility::moveFile (const std::string &sDestination, const std::string &sSource)
  {
	if (existFile (sSource))
		if ( MoveFile((LPCWSTR)(CStringUtility::stdToWSTR(sSource).c_str()), (LPCWSTR) (CStringUtility::stdToWSTR(sDestination).c_str()) ) )
			return (true);

	return (false);
  }

  bool CFileUtility::deleteFile (const std::string &sFileName)
  {
	if ( existFile( sFileName ) )
	   if ( DeleteFile((LPCWSTR) CStringUtility::stdToWSTR(sFileName).c_str() ) )
			return (true);

	return (false); 
  }

  bool CFileUtility::renameFile (const std::string &sOldName, const std::string &sNewName)
  {
	// does not overwrite existing files
	if ( existFile(sNewName) )
		return (false);

	if ( existFile(sOldName) )
		return moveFile(sNewName,sOldName);

	return (false); 
  }

  bool CFileUtility::existDirectory (const std::string &sPath)
  {
	  DWORD   dwfa;
	  
	  // clean path
	  char *dir_name = cleanPath (sPath.c_str());
	  
	  // attributes
	  dwfa = GetFileAttributes ((LPCWSTR) (CStringUtility::stdToWSTR(dir_name)).c_str());
	  if (dwfa == 0xffffffff)
		  return (false);
	  free (dir_name);
	  
	  if (dwfa & FILE_ATTRIBUTE_DIRECTORY)
		  return (true);
	  
	  return (false);
  }
  
  bool CFileUtility::createDirectory (const std::string &sPath)
  {
	  char *path, *slash;
	  int rc = 0;
	  
	  path = _strdup (sPath.c_str()); //  Working copy
	  strconvch (path, _T('/'), _T('\\'));
	  
	  //  Create each component of directory as required
	  slash = strchr (path + 1, PATHEND); //  Find first slash
	  //  Create any parent directories
	  for (;;)   {
		  if (slash)
			  *slash = _T('\0'); //  Cut at slash
		  
		  if (!existDirectory (path))
		  {
			  if (CreateDirectory ((LPCWSTR)(CStringUtility::stdToWSTR(path)).c_str(), NULL))
				  rc = 0;
			  else
				  rc = -1;
			  if (rc)                     //  End if error
				  break;
		  }
		  if (slash == NULL)              //  End if last directory
			  break;
		  *slash = PATHEND;                //  Restore path name
		  slash = strchr (slash + 1, PATHEND);
	  }
	  free (path);
	  
	  return (rc == 0);
  }

  bool CFileUtility::deleteDirectory (const std::string &sPath)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  DWORD dwTest;
	  std::string sTemp;
	  bool bResult = true;
	  
	  if ( ! existDirectory(sPath) )
		  return (false );
	  
	 
	  std::string sWildCard = sPath;
	  std::string sExt = "\\*.*";
	  std::string sExt1 = "\\";

	  hFile = FindFirstFile((LPCWSTR)(CStringUtility::stdToWSTR(sWildCard + sExt).c_str()) , &stFileData);
	  while (hFile != INVALID_HANDLE_VALUE && bResult)
	  {
		  // ignore . and ..
		 // if ((0 != wcscmp((wchar_t *)stFileData.cFileName, L".")) && (0 != wcscmp((wchar_t *)stFileData.cFileName, L"..")))
		if ((0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))))
			  {
			  sTemp = sPath + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);
			  //sTemp = sPath + sExt1 + stFileData.cFileName;
			  // check on directory
			  dwTest = stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			  if (dwTest != 0)
			  {
				  if ( ! deleteDirectory(sTemp) )
				  {
					  FindClose(hFile);	
					  return (false);
				  }
			  }
			  else
			  {	
				  // delete file
				  if ( 0 != _unlink(sTemp.c_str()) )
				  {
					  FindClose(hFile);	
					  return (false);
				  } 
			  }
		  }
		  
		  // next
		  bResult = FindNextFile(hFile, &stFileData) == TRUE;
	  }
	  
	  FindClose(hFile);	
	  
	  // delete directory
	  if (!RemoveDirectory(CStringUtility::stdToWSTR(sPath).c_str()))
		//if (!RemoveDirectory(sPath.c_str()))
		return (false);
	  
	  return (true);
  }

  bool CFileUtility::cleanDirectoryComplete (const std::string &sPath)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  DWORD dwTest;
	  std::string sTemp;
	  bool bResult = true;
	  
	  if ( ! existDirectory(sPath) )
		  return (false );
	
		std::string sWildCard = ""; // = sPath;
		std::string sExt = "\\*.*";
		std::string sExt1 = "\\";
		sWildCard = sPath + sExt;
	  
		hFile = FindFirstFile(CStringUtility::stdToWSTR(sWildCard).c_str(), &stFileData);
		///hFile = FindFirstFile(sWildCard.c_str(), &stFileData);
		while (hFile != INVALID_HANDLE_VALUE && bResult)
	  {
		  // ignore . and ..
		  if ( (0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))) )
		  {
			  sTemp = sPath + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);
			  // check on directory
			  dwTest = stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
			  if (dwTest != 0)
			  {
				  if ( ! deleteDirectory(sTemp) )
				  {
					  FindClose(hFile);	
					  return (false);
				  }
			  }
			  else
			  {	
				  // delete file
				  if ( 0 != _unlink(sTemp.c_str()) )
				  {
					  FindClose(hFile);	
					  return (false);
				  } 
			  }
		  }
		  
		  // next
		  bResult = FindNextFile(hFile, &stFileData) == TRUE;
	  }
	  
	  FindClose(hFile);	
	  	  
	  return (true);
  }

  bool CFileUtility::cleanDirectory (const std::string &sPath)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  std::string sTemp;
	  bool bResult = true;
	  
	  if ( ! existDirectory(sPath) )
		  return (false );

	  std::string sWildCard = ""; 
	  std::string sExt		= "\\~*.*" ;
	  std::string sExt1		= "\\";
	  sWildCard = sPath + sExt;
	
	   hFile = FindFirstFile(CStringUtility::stdToWSTR(sWildCard).c_str(), &stFileData);
	  //hFile = FindFirstFile(sWildCard.c_str(), &stFileData);

	  while (hFile != INVALID_HANDLE_VALUE && bResult)
	  {
		  sTemp = sPath + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);

		  // delete file
		  if ( 0 != _unlink(sTemp.c_str()) )
		  {
			  FindClose(hFile);	
			  return (false);
		  } 
		  
		  // next
		  bResult = FindNextFile(hFile, &stFileData) == TRUE;
	  }
	  
	  FindClose(hFile);	
	  
	  return (true);
  }

  bool CFileUtility::deepCopyDirectory (const std::string& destination, const std::string &source)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  DWORD dwTest;
	  std::string sTempSource;
	  std::string sTempDestination;
	  bool bResult = true;

	  std::string sWildCard = "";
	  std::string sExt = "\\*.*";
	  std::string sExt1 = "\\";
//	  sWildCard = sPath + sExt;


	  if ( existDirectory (source) )
	  {
		  // create destination directory this directory
		  if ( ! createDirectory( destination ) )
			  return (false);  // we do not deepCopy into an existing directory.
		  
		  sWildCard = source + sExt;

		  hFile = FindFirstFile((CStringUtility::stdToWSTR(sWildCard)).c_str(), &stFileData);
		 // hFile = FindFirstFile( sWildCard.c_str(), &stFileData);
		  while (hFile != INVALID_HANDLE_VALUE && bResult)
		  {
			  // ignore . and ..
			  if ( (0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))) )
			  {
				  sTempSource = source + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);
				  sTempDestination = destination + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);
				  // check on directory
				  dwTest = stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
				  if (dwTest != 0)
				  {
					  if ( ! deepCopyDirectory(sTempDestination, sTempSource) )
						  break;
				  }
				  else
				  {	
					  if ( ! copyFile(sTempDestination, sTempSource) )
						  break;
				  }
			  }
			  
			  // next
			  bResult = FindNextFile(hFile, &stFileData) == TRUE;
		  }

		  FindClose(hFile);	

		  return (true);
	  }
	  
	  return (false);
  }

  bool CFileUtility::renameDirectory (const std::string &sOldName, const std::string &sNewName)
  {
	  if ( existDirectory (sOldName) )
		  return ( renameFile (sOldName, sNewName) ); 
	  else
		  return (false);
  }

  void CFileUtility::list (const std::string &sDirectoryName, std::vector<std::string> &rVectorOfNames)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  bool bResult = true;
	  
	  rVectorOfNames.clear();
	  
	  if ( ! existDirectory(sDirectoryName) )
		  return;


	  std::string sExt = "\\*.*";
	  std::string sExt1 = "\\";

	  std::string sWildCard = sDirectoryName + sExt;
	  
	  hFile = FindFirstFile((LPCWSTR)(CStringUtility::stdToWSTR(sWildCard)).c_str(), &stFileData);
	  while (hFile != INVALID_HANDLE_VALUE && bResult)
	  {
		  // ignore . and ..
		  if ( (0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))) )
		  {
			  rVectorOfNames.push_back(CStringUtility::WSTRToStr(stFileData.cFileName));
		  }
		  // next
		  bResult = FindNextFile(hFile, &stFileData) == TRUE;
	  }
	  FindClose(hFile);	
  }

  char* CFileUtility::strconvch (char *string, char from, char to)
  {
	  char *scan;
	  if (string)
	  {
		  scan = string;
		  while (*scan)
		  {
			  if (*scan == from)
				  *scan = to;
			  scan++;
		  }
	  }
	  return (string);
  }
  
  char* CFileUtility::cleanPath (const char *path)
  {
	  char new_path [_MAX_PATH + 1];        //  Returned path value
	  char *slash;
	  
	  strncpy_s (new_path, path, _MAX_PATH);
	  new_path [_MAX_PATH] = _T('\0');
	  //  For DOS filesystems, use only back slashes
	  strconvch (new_path, _T('/'), _T('\\'));
	  slash = strrchr (new_path, PATHEND);    //  Find last slash
	  
	  //  If slash is last character in string, maybe squash it
	  if (slash && slash [1] == _T('\0'))
	  {
		  if (slash > new_path && slash [-1] != _T(':'))
			  *slash = _T('\0');
	  }
	  else //  Turn X: into X:
		  if (new_path [1] == _T(':') && new_path [2] == _T('\0'))
		  {
			  new_path [2] = _T('\\');
			  new_path [3] = _T('\0');
		  }
		  return _strdup(new_path);
  }
  
  bool CFileUtility::cleanFileName(wchar_t* pName)
  {
	  removeForbiddenChars( pName );

	  return (true);
  }

  bool CFileUtility::cleanPathName(wchar_t* pName)
  {
//	  removeForbiddenChars( pName, "0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" );

	  return (true);
  }
  
  bool CFileUtility::isWritable (const std::string& sFullPathName, bool bRecurse)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  DWORD dwTest;
	  std::string sTemp;
	  bool bResult = true;
	  std::string sExt = "\\*.*";
	  std::string sExt1 = "\\";

	  // given path
	  hFile = FindFirstFile((LPCWSTR)(CStringUtility::stdToWSTR(sFullPathName).c_str()), &stFileData);
	  if ( stFileData.dwFileAttributes &  FILE_ATTRIBUTE_READONLY )
	  {
		  FindClose(hFile);	
		  return (false);
	  }
	  
	  if ( bRecurse && existDirectory(sFullPathName) )
	  {
		  std::string sWildCard = sFullPathName + sExt;
		  
		  ///hFile = FindFirstFile((LPCWSTR)(CStringUtility::stdToWSTR(sFullPathName).c_str()), &stFileData);

		  hFile = FindFirstFile((LPCWSTR)(CStringUtility::stdToWSTR(sWildCard).c_str()), &stFileData);
		  while (hFile != INVALID_HANDLE_VALUE && bResult)
		  {
			  // ignore . and ..
			  if ( (0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))) )
			  {
				  sTemp = sFullPathName + sExt1 + (CStringUtility::WSTRToStr(stFileData.cFileName));
				  // check on directory
				  dwTest = stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
				  if (dwTest != 0)
				  {
					  if ( ! isWritable(sTemp, true) )
					  {
						  FindClose(hFile);	
						  return (false);
					  }
				  }
				  else
				  {	
					  if ( stFileData.dwFileAttributes &  FILE_ATTRIBUTE_READONLY )
					  {
						  FindClose(hFile);	
						  return (false);
					  }
				  }
			  }
			  
			  // next
			  bResult = FindNextFile(hFile, &stFileData) == TRUE;
		  }
	  }
	  
	  FindClose(hFile);	
	  
	  return (true);
  }

  bool CFileUtility::setWritable (const std::string& sFullPathName, bool bRecurse)
  {
	  WIN32_FIND_DATA stFileData;
	  HANDLE hFile;
	  DWORD dwTest;
	  std::string sTemp;
	  bool bResult = true;
	  std::string sExt = "\\*.*";
	  std::string sExt1 = "\\";

	  // given path
	  hFile = FindFirstFile((LPCWSTR)((CStringUtility::stdToWSTR(sFullPathName)).c_str()), &stFileData);
	  if ( ! SetFileAttributes((LPCWSTR)(CStringUtility::stdToWSTR(sFullPathName)).c_str(), stFileData.dwFileAttributes &~  FILE_ATTRIBUTE_READONLY) )
	  {
		  FindClose(hFile);	
		  return (false);
	  }
	  FindClose(hFile);	
	  
	  if ( bRecurse && existDirectory(sFullPathName) )
	  {
		  std::string sWildCard = sFullPathName + sExt;
		  
		  hFile = FindFirstFile((CStringUtility::stdToWSTR(sWildCard)).c_str(), &stFileData);
		  while (hFile != INVALID_HANDLE_VALUE && bResult)
		  {
			  // ignore . and ..
			  if ( (0 != wcscmp(stFileData.cFileName, _T("."))) && (0 != wcscmp(stFileData.cFileName, _T(".."))) )
			  {
				  sTemp = sFullPathName + sExt1 + CStringUtility::WSTRToStr(stFileData.cFileName);
				  // check on directory
				  dwTest = stFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
				  if (dwTest != 0)
				  {
					  if ( ! setWritable(sTemp, true) )
					  {
						  FindClose(hFile);	
						  return (false);
					  }
				  }
				  else
				  {	
					  if ( ! SetFileAttributes(  (LPCWSTR)((CStringUtility::stdToWSTR(sTemp)).c_str()), stFileData.dwFileAttributes &~ FILE_ATTRIBUTE_READONLY ) )
					  {
						  FindClose(hFile);	
						  return (false);
					  }
				  }
			  }
			  
			  // next
			  bResult = FindNextFile(hFile, &stFileData) == TRUE;
		  }
		  FindClose(hFile);	
	  }
	  
	  return (true);
  }
  

  wchar_t* CFileUtility::removeForbiddenChars(wchar_t *str, wchar_t *cPermitted)
  {
	  wchar_t *obuf, *nbuf;
	  bool bFound = false;
	  
      if (str)
      {
		  for (obuf = str, nbuf = str; *obuf; ++obuf)
		  {
			  bFound = false;
			  for ( int i = 0 ; cPermitted[i] ; i++ ) {
				  if ( cPermitted[i] == *obuf ) { // allowed sign found
					  bFound = true;
					  break;					// and check next char
				  }
			  }
			  if ( !bFound )
				  *nbuf = _T('_');
			  *nbuf++;
		  }
		  *nbuf = NULL;
      }
      return str;
	  
  }


  // check on free disk space
  double CFileUtility::getFreeDiskspace (const std::string& sPathName)
  {
	  ULARGE_INTEGER  lFreeBytesAvailableToCaller;
	  ULARGE_INTEGER  lTotalNumberOfBytes;
	  ULARGE_INTEGER  lTotalNumberOfFreeBytes;
	
	  if (GetDiskFreeSpaceEx(CStringUtility::stdToWSTR((sPathName)).c_str(),&lFreeBytesAvailableToCaller,&lTotalNumberOfBytes,&lTotalNumberOfFreeBytes))
		  return (double)((signed __int64)lTotalNumberOfFreeBytes.QuadPart /1024/1024);
	  
	  return 0.0 ;
  }


} // namespace eag

