#include "stdafx.h"
#include "MathUtility.h"

namespace eag {
	
	// Rounds a number to a specified number of digits.
	// Number is the number you want to round.
	// Num_digits specifies the number of digits to which you want to round number.
	// If num_digits is greater than 0, then number is rounded to the specified number of decimal places.
	// If num_digits is 0, then number is rounded to the nearest integer.
	// Examples
	//		ROUND(2.15, 1)		equals 2.2
	//		ROUND(2.149, 1)		equals 2.1
	//		ROUND(-1.475, 2)	equals -1.48
	float CMathUtility::Round(const float &number, const int num_digits)
	{
		float doComplete5i, doComplete5(number * powf(10.0f, (float) (num_digits + 1)));
		
		if(number < 0.0f)
			doComplete5 -= 5.0f;
		else
			doComplete5 += 5.0f;
		
		doComplete5 /= 10.0f;
		modff(doComplete5, &doComplete5i);
		
		return doComplete5i / powf(10.0f, (float) num_digits);
	}
	
	double CMathUtility::RoundDouble(double doValue, int nPrecision)
	{
		static const double doBase = 10.0f;
		double doComplete5, doComplete5i;
		
		doComplete5 = doValue * pow(doBase, (double) (nPrecision + 1));
		
		if(doValue < 0.0f)
			doComplete5 -= 5.0f;
		else
			doComplete5 += 5.0f;
		
		doComplete5 /= doBase;
		modf(doComplete5, &doComplete5i);
		
		return doComplete5i / pow(doBase, (double) nPrecision);
	}
	
	// Rounds X to SigFigs significant figures.
	// Examples
	//		SigFig(1.23456, 2)		equals 1.2
	//		SigFig(1.23456e-10, 2)	equals 1.2e-10
	//		SigFig(1.23456, 5)		equals 1.2346
	//		SigFig(1.23456e-10, 5)	equals 1.2346e-10
	//		SigFig(0.000123456, 2)	equals 0.00012
	float CMathUtility::SigFig(float X, int SigFigs)
	{
		if(SigFigs < 1)
		{
			ASSERT(FALSE);
			return X;
		}
		
		int Sign;
		if(X < 0.0f)
			Sign = -1;
		else
			Sign = 1;
		
		X = fabsf(X);
		float Powers = powf(10.0f, floorf(log10f(X)) + 1.0f);
		
		return Sign * Round(X / Powers, SigFigs) * Powers;
	}
	
	// Converts a floating point number to ascii (without the appended 0's)
	// Rounds the value if nNumberOfDecimalPlaces >= 0
	CString CMathUtility::FloatToText(float n, int nNumberOfDecimalPlaces)
	{
		CString str;
		
		if(nNumberOfDecimalPlaces >= 0)
		{
			int decimal, sign;
			char *buffer = _fcvt((double)n, nNumberOfDecimalPlaces, &decimal, &sign);
			
			CString temp(buffer);
			
			// Sign for +ve or -ve
			if(sign != 0)
				str = "-";
			
			// Copy digits up to decimal point
			if(decimal <= 0)
			{
				str += "0.";
				for(; decimal < 0; decimal++)
					str += "0";
				str += temp;
			} else {
				str += temp.Left(decimal);
				str += ".";
				str += temp.Right(temp.GetLength() - decimal);
			}
		} else {
			str.Format(_T("%-g"), n);
		}
		
		// Remove appended zero's. "123.45000" become "123.45"
		int nFind = str.Find(_T("."));
		if(nFind >= 0)
		{
			int nFinde = str.Find(_T("e"));	// 1.0e-010 Don't strip the ending zero
			if(nFinde < 0)
			{
				while(str.GetLength() > 1 && str.Right(1) == _T("0"))
					str = str.Left(str.GetLength() - 1);
			}
		}
		
		// Remove decimal point if nothing after it. "1234." becomes "1234"
		if(str.Right(1) == ".")
			str = str.Left(str.GetLength() - 1);
		
		return str;
	}

	long CMathUtility::RoundValue(const float param)
	{
		if((param - floor(param)) < 0.5f) 
	        return long(floor(param));
	    else 
	        return long(ceil(param));
	}
	
} // namespace eag

