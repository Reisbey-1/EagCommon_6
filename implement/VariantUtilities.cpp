#include "stdafx.h"
#include "VariantUtilities.h"
#include "StringUtility.h"

namespace eag {
	
	bool CVariantUtilities::CStringArrayFromVariant(CStringArray &dest, const VARIANT &src)
	{
		if (src.vt == VT_ARRAY){
			
			if ( src.parray == NULL )
				return false;

			SAFEARRAY *psa=src.parray;

			long indice[1];
			BSTR value;
			dest.SetSize(psa->rgsabound->cElements);

			for (indice[0] = 0 ; indice[0] < psa->rgsabound->cElements ; indice[0]++) {
				
				SafeArrayGetElement( psa, indice, &value);
				dest[indice[0]] = CStringUtility::bstrToCString(value);
			}
		}
		else {
			return false;
		}
		return true;
	}
	
	bool CVariantUtilities::VariantFromCStringArray(VARIANT &dest,const CStringArray &src)
	{
		SAFEARRAYBOUND sab;
		sab.cElements=src.GetSize();
		sab.lLbound=0;

		SAFEARRAY *psa = SafeArrayCreate(VT_BSTR, 1, &sab); 

		if ( psa == NULL )
			return false;

		long indice[1];
		for ( indice[0] = 0 ; indice[0] < src.GetSize() ; indice[0]++) {
			SafeArrayPutElement( psa, indice, src[indice[0]].AllocSysString() );
		}

		dest.vt = VT_ARRAY;
		dest.parray=psa;

		return true;
	}
	
	bool CVariantUtilities::CDoubleArrayFromVariant(CArray <double,double&> &dest,const VARIANT &src)
	{
		if (src.vt == VT_ARRAY){

			if ( src.parray == NULL )
				return false;
			
			SAFEARRAY *psa=src.parray;

			long indice[1];
			VARIANT value;
			VariantInit(&value);
			value.vt = VT_R8;

			dest.SetSize(psa->rgsabound->cElements);

			for (indice[0] = 0 ; indice[0] < psa->rgsabound->cElements ; indice[0]++) {
				
				SafeArrayGetElement( psa, indice, &value);
				dest[indice[0]] = value.dblVal;
			}
		}
		else {
			return false;
		}
		return true;
	}
	
	bool CVariantUtilities::VariantFromCDoubleArray(VARIANT &dest,const CArray <double,double&> &src)
	{
		SAFEARRAYBOUND sab;
		sab.cElements=src.GetSize();
		sab.lLbound=0;

		VARIANT value;
		VariantInit(&value);
		value.vt = VT_R8;

		SAFEARRAY *psa = SafeArrayCreate(VT_VARIANT, 1, &sab); 

		if ( psa == NULL )
			return false;

		long indice[1];
		for ( indice[0] = 0 ; indice[0] < src.GetSize() ; indice[0]++) {

			value.dblVal = src[indice[0]];
			SafeArrayPutElement( psa, &indice[0], &value );
		}

		dest.vt = VT_ARRAY;
		dest.parray=psa;

		return true;
	}

	bool CVariantUtilities::SafeArrayFromDString( SAFEARRAY **pdest, DString &src)
	{
		SAFEARRAYBOUND sab;
		sab.cElements=src.laenge();
		sab.lLbound=0;

		wchar_t *pucData= src.getstr();
		
		HRESULT  hr;
		BYTE *pData = NULL;

		try
		{

			*pdest = NULL;

			SAFEARRAY *psa = SafeArrayCreate(VT_UI1, 1, &sab); 

			if ( psa == NULL )
				return false;

			hr = SafeArrayAccessData(psa, reinterpret_cast<PVOID*>(&pData)) ;

			if ( pData != NULL && hr == S_OK )
			{
				memcpy( pData, pucData, sab.cElements);
	
				hr = SafeArrayUnaccessData(psa); // write data back

				if ( hr == S_OK )
					*pdest = psa;
				else
					return false;

			}
			else
				return false;

		}
		catch(...)
		{
			return false;
		}

		return true;

	}
	
	bool CVariantUtilities::DStringFromSafeArray(DString &dest, SAFEARRAY *src)
	{

		wchar_t *pucData = NULL;
		HRESULT  hr;

		try
		{
			if (src == NULL )
				return false;

			dest.leere();

			hr = SafeArrayAccessData( src , reinterpret_cast<PVOID*>(&pucData)) ;

			if ( hr == S_OK && pucData != NULL )
			{
				if ( (*src).cbElements == 1 ) // there must be exactly one array dimension
				{
					dest.addstr( pucData , (*src).rgsabound[0].cElements );
				}
				else
					return false;
			}

			hr = SafeArrayUnaccessData( src ); // write data back

		}
		catch(...)
		{
			return false;
		}
		return true;
	
	}

	
	bool CVariantUtilities::SafeArrayFromCDoubleArray( SAFEARRAY **pdest, const CArray <double,double&> &src )
	{
		SAFEARRAYBOUND sab;
		sab.cElements=src.GetSize();
		sab.lLbound=0;

		double *pData = NULL;
		HRESULT  hr;

		try
		{

			*pdest = NULL;

			SAFEARRAY *psa = SafeArrayCreate(VT_R8, 1, &sab); 

			hr = SafeArrayAccessData(psa, reinterpret_cast<PVOID*>(&pData)) ;

			if ( pData != NULL && hr == S_OK )
			{
				memcpy( pData, src.GetData(), sab.cElements * sizeof(double));
	
				hr = SafeArrayUnaccessData(psa); // write data back

				if ( hr == S_OK )
					*pdest = psa;
				else
					return false;

			}
			else
				return false;

		}
		catch(...)
		{
			return false;
		}

		return true;
	}
	
	bool CVariantUtilities::CDoubleArrayFromSafeArray(CArray <double,double&> &dest, SAFEARRAY *src )
	{
		double *pucData = NULL;
		HRESULT  hr;

		try
		{
			if (src == NULL )
				return false;

			dest.SetSize( (*src).rgsabound[0].cElements );

			hr = SafeArrayAccessData( src , reinterpret_cast<PVOID*>(&pucData)) ;
		
			if ( hr == S_OK && pucData != NULL )
			{
				memcpy( dest.GetData(), pucData , (*src).rgsabound[0].cElements*sizeof(double) );
			}

			hr = SafeArrayUnaccessData( src ); // write data back

		}
		catch(...)
		{
			return false;
		}
		return true;

	}

	bool CVariantUtilities::SafeArrayFromCIntArray( SAFEARRAY **pdest, const CArray <int,int&> &src )
	{

		SAFEARRAYBOUND sab;
		sab.cElements=src.GetSize();
		sab.lLbound=0;

		int *pData = NULL;
		HRESULT  hr;

		try
		{

			SAFEARRAY *psa = SafeArrayCreate(VT_I4, 1, &sab); 

			if ( psa == NULL )
				return false;


			hr = SafeArrayAccessData(psa, reinterpret_cast<PVOID*>(&pData)) ;

			if ( pData != NULL && hr == S_OK )
			{
				memcpy( pData, src.GetData(), sab.cElements * sizeof(int));
	
				hr = SafeArrayUnaccessData(psa); // write data back

				if ( hr == S_OK )
					*pdest = psa;
				else
					return false;

			}
			else
				return false;

		}
		catch(...)
		{
			return false;
		}

		return true;
	}

	bool CVariantUtilities::CIntArrayFromSafeArray(CArray <int,int&> &dest, SAFEARRAY *src )
	{
		int *pucData = NULL;
		HRESULT  hr;

		try
		{
			if (src == NULL )
				return false;

			dest.SetSize( (*src).rgsabound[0].cElements );

			hr = SafeArrayAccessData( src , reinterpret_cast<PVOID*>(&pucData)) ;
		
			if ( hr == S_OK && pucData != NULL )
			{
				memcpy( dest.GetData(), pucData , (*src).rgsabound[0].cElements*sizeof(int) );
			}

			hr = SafeArrayUnaccessData( src ); // write data back

		}
		catch(...)
		{
			return false;
		}
		return true;
	
	}

	


}

