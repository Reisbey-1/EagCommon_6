//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%38F719860399.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%38F719860399.cm

//## begin module%38F719860399.cp preserve=no
//## end module%38F719860399.cp

//## Module: StringUtility%38F719860399; Package specification
//## Subsystem: common%38F7195F0086
//## Source file: Z:\app_hte\common\implement\StringUtility.h

#ifndef StringUtility_h
#define StringUtility_h 1

//## begin module%38F719860399.additionalIncludes preserve=no
//## end module%38F719860399.additionalIncludes

//## begin module%38F719860399.includes preserve=yes
#include <string>
#include <ostream>   /// DLG
#include "xmldef.h"
#include "xmlhandler.h"
#include <afxtempl.h>
#include "DString.h"

//## end module%38F719860399.includes

//## begin module%38F719860399.declarations preserve=no
//## end module%38F719860399.declarations

//## begin module%38F719860399.additionalDeclarations preserve=yes
//## end module%38F719860399.additionalDeclarations


//## Modelname: common%38F717B70177
namespace eag {
  //## begin eag%38F717B70177.initialDeclarations preserve=yes
  //## end eag%38F717B70177.initialDeclarations

  //## begin eag::CStringUtility%38F717D6004F.preface preserve=yes
	#ifdef STRINGUTILITY_EXPORTS
	#define STRINGUTILITY_API __declspec(dllexport)
	#else
	#define STRINGUTILITY_API __declspec(dllimport)
	#endif
  //## end eag::CStringUtility%38F717D6004F.preface

  //## Class: CStringUtility%38F717D6004F; Class Utility
  //	The class is a common class utility performing diverse
  //	conversions of strings.
  //## Category: common%38F717B70177
  //## Subsystem: common%38F7195F0086
  //## Persistence: Transient
  //## Cardinality/Multiplicity: n

//##ModelId=3978398E0339
  class STRINGUTILITY_API CStringUtility 
  {
    //## begin eag::CStringUtility%38F717D6004F.initialDeclarations preserve=yes
    //## end eag::CStringUtility%38F717D6004F.initialDeclarations

    public:

      //## Other Operations (specified)
        //## Operation: stdToBSTR%38F718730087
        //	Converts an std::string into BSTR.
	//##ModelId=3978398E034E
        static BSTR stdToBSTR (std::string str);

        //## Operation: bstrToStd%38F718B2018C
        //	Converts a BSTR into an std::string.
	//##ModelId=3978398E0343
        static std::string bstrToStd (BSTR bstr);

      // Additional Public Declarations
        //## begin eag::CStringUtility%38F717D6004F.public preserve=yes
        //## end eag::CStringUtility%38F717D6004F.public

		static BSTR xmlStringToBSTR (CXmlString str);

        static CXmlString bstrToXmlString (BSTR bstr);

		static BSTR cStringToBSTR(CString cstr);

		static wchar_t* CHARToWCHAR(char* szStr);

		static PCHAR WCHARToCHAR(PWCHAR szStr);

        static CString bstrToCString (BSTR bstr);
		static std::wstring stdToWSTR(std::string str);
		static std::string WSTRToStr(std::wstring wstr);

		static bool CStringArrayFromVariant(CStringArray &dest, VARIANT &src);

		static bool VariantFromCStringArray( VARIANT &dest, CStringArray &src);

		static CString CLSIDFromModulename( CString& rModule );

		static CString ModulenameFromCLSID( CString& rId );

		static void RemoveLastLF (wchar_t* txt);
	
		static void GetNextToken (DString &r_dstrSource, CString &Key, CString &value, CString& trash);


		// base64 implementation:

		static const wchar_t base64table[];

		static  wchar_t base64_dec( const  wchar_t Ch );

		static void base64_decode(eag::DString &dstr_in, eag::DString &dstr_out);

#define B64_Mask(Ch) (wchar_t) base64table[ (Ch) & 0x3F ]

		static void base64_encode(eag::DString & source, eag::DString & out, int inclCrLf );

    protected:
      // Additional Protected Declarations
        //## begin eag::CStringUtility%38F717D6004F.protected preserve=yes
        //## end eag::CStringUtility%38F717D6004F.protected

    private:
      // Additional Private Declarations
        //## begin eag::CStringUtility%38F717D6004F.private preserve=yes
        //## end eag::CStringUtility%38F717D6004F.private

    private: //## implementation
      // Additional Implementation Declarations
        //## begin eag::CStringUtility%38F717D6004F.implementation preserve=yes
        //## end eag::CStringUtility%38F717D6004F.implementation

  };

  //## begin eag::CStringUtility%38F717D6004F.postscript preserve=yes
  //## end eag::CStringUtility%38F717D6004F.postscript

  // Class Utility eag::CStringUtility 

} // namespace eag

//## begin module%38F719860399.epilog preserve=yes
//## end module%38F719860399.epilog


#endif
