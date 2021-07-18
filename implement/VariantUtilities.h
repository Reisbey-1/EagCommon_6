#ifndef VariantUtilities_h
#define VariantUtilities_h 1

#include <string>
#include <afxtempl.h>
#include "DString.h"

namespace eag {
	
	#ifdef VARIANTUTILITIES_EXPORTS
	#define VARIANTUTILITIES_API __declspec(dllexport)
	#else
	#define VARIANTUTILITIES_API __declspec(dllimport)
	#endif
	
	class VARIANTUTILITIES_API CVariantUtilities 
	{
		
	public:
		static bool SafeArrayFromCIntArray( SAFEARRAY **dest, const CArray <int,int&> &src );
		static bool CIntArrayFromSafeArray(CArray <int,int&> &dest, SAFEARRAY *src );
		
		static bool SafeArrayFromCDoubleArray( SAFEARRAY **dest, const CArray <double,double&> &src );
		static bool CDoubleArrayFromSafeArray(CArray <double,double&> &dest, SAFEARRAY *src );
		
		static bool VariantFromCDoubleArray( VARIANT &dest, const CArray <double,double&> &src );
		static bool CDoubleArrayFromVariant(CArray <double,double&> &dest, const  VARIANT &src );
		static bool VariantFromCStringArray( VARIANT &dest,  const CStringArray &src );
		static bool CStringArrayFromVariant( CStringArray &dest, const  VARIANT &src );

		static bool SafeArrayFromDString( SAFEARRAY **pdest, DString &src);
		static bool DStringFromSafeArray( DString &dest, SAFEARRAY *src);
	
	protected:
		
	private:
		
	};
}

#endif