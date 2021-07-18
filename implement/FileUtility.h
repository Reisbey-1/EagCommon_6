#ifndef FileUtility_h
#define FileUtility_h 1

#include <string>
#include <vector>

namespace eag {

#ifdef FILEUTILITY_EXPORTS
#define FILEUTILITY_API __declspec(dllexport)
#else
#define FILEUTILITY_API __declspec(dllimport)
#endif

  class FILEUTILITY_API CFileUtility 
  {
    public:
        CFileUtility();

        virtual ~CFileUtility();

        //	returns true if the file (parameter 1) exists
        static bool existFile (const std::string& sFullPathFileName);

        //	copy a file from source to destination, retruns true if
        //	successfull, false if not (or if the source does not
        //	exist)
        static bool copyFile (const std::string &sDestination, const std::string &sSource, const bool bOverwrite = false);

        //	moves a file from source to destination, retruns true if
        //	successfull, false if not (or if the source does not
        //	exist)
        //	(calls actually renameFile to perform the action)
        static bool moveFile (const std::string &sDestination, const std::string &sSource);

        //	delete the file from disk, retruns true if successfull,
        //	false if not (or if the file does not exist)
        static bool deleteFile (const std::string &sFileName);

        //	renames file retruns true if successfull, false if not
        //	(or if the source does not exist)
        static bool renameFile (const std::string &sOldName, const std::string &sNewName);

        //	returns true if the directory (parameter 1) exists
        static bool existDirectory (const std::string &sPath);

        //	creates a new directory
        static bool createDirectory (const std::string &sPath);

        //	delecters the dirctory and all its files and
        //	subdirectories
        static bool deleteDirectory (const std::string &sPath);

        //	clean the dirctory from temporary files
		// marked with an ~...
        static bool cleanDirectory (const std::string &sPath);

        //	clean the dirctory from all files
        static bool cleanDirectoryComplete (const std::string &sPath);

        //	This method tries to deep-copy a directory structure.
        //	Returns true on success and false on failure.
        static bool deepCopyDirectory (const std::string &destination, const std::string &source);

        //	renames directory retruns true if successfull, false if
        //	not (or if the source does not exist)
        static bool renameDirectory (const std::string &sOldName, const std::string &sNewName);

        //	If this is a directory, this method returns a list of
        //	all elements (files or directories).
        static void list (const std::string &sDirectoryName, std::vector<std::string> &rVectorOfNames);

        //	beautifies filenames (replacing forbidden characters with '_') 
        static bool cleanFileName (wchar_t* pName);

        //	beautifies pathnames (replacing forbidden characters with '_') 
        static bool cleanPathName (wchar_t* pName);

		static wchar_t * removeForbiddenChars(wchar_t * cStr, wchar_t * cPermitted = L"0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//	static wchar_t * removeForbiddenChars(wchar_t * cStr,  wchar_t* cPermitted = L"1" );

		// ensure, that file or directory is writable
        //	returns true if the file is writable and false, if readonly
        static bool isWritable (const std::string& sFullPathName, bool bRecurse = false);

		// check, if file or directory is writable
        //	returns true if the file is set successfully to writable and false, if readonly
        static bool setWritable (const std::string& sFullPathName, bool bRecurse = false);

		// check on free disk space
        static double getFreeDiskspace (const std::string& sPathName);
		private:
		//## Constructors (generated)
		CFileUtility(const CFileUtility &right);
		
		//## Assignment Operation (generated)
		const CFileUtility & operator=(const CFileUtility &right);
		
		static char* strconvch (char *string, char from, char to);

		static char* cleanPath (const char *path);
		
		//## Equality Operations (generated)
        bool operator==(const CFileUtility &right) const;
		
        bool operator!=(const CFileUtility &right) const;

  };

} // eag

#endif
