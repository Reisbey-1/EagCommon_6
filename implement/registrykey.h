#ifndef registrykey_h
#define registrykey_h 1

//#include <atlbase.h>  // CRegKey

namespace eag {

#ifdef REGISTRYKEY_EXPORTS
#define REGISTRYKEY_API __declspec(dllexport)
#else
#define REGISTRYKEY_API __declspec(dllimport)
#endif

//##ModelId=39783985017E
class REGISTRYKEY_API CRegistryKey 
{

  public:

	//##ModelId=39783985028C
      CRegistryKey (const CString csRegSubPath);

	//##ModelId=397839850283
      ~CRegistryKey();


	//##ModelId=397839850265
      bool get (const wchar_t *cRegParameter, DWORD& r_dwValue);

	//##ModelId=397839850278
      bool get (const wchar_t *cRegParameter, CString& r_csValue);

	//##ModelId=397839850247
      bool set (const wchar_t *cRegParameter, const DWORD dwValue);

	//##ModelId=39783985025A
      bool set (const wchar_t *cRegParameter, const CString csValue);

     static void set_BaseKey (const CString csBaseKey);
     static const CString& get_BaseKey ();

  protected:

  private:
	//##ModelId=397839850296
      CRegistryKey();
	//##ModelId=3978398502A0
      CRegistryKey(const CRegistryKey &right);

	//##ModelId=39783985023C
      const CRegistryKey & operator=(const CRegistryKey &right);

  private:

	//##ModelId=3978398501A6
	  CRegKey m_RegKey;
	//##ModelId=397839850188
      BOOL m_bRegKeyOpen;

	  bool m_bCanWrite;

      static CString m_scsBaseKey;

      static BOOL  m_sbBaseKeySet;
};

} // namespace

#endif
