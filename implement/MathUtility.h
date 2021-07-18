#ifndef MathUtility_h
#define MathUtility_h 1

#include <math.h>

namespace eag {
	
#ifdef MATHUTILITY_EXPORTS
#define MATHUTILITY_API __declspec(dllexport)
#else
#define MATHUTILITY_API __declspec(dllimport)
#endif
	
	class MATHUTILITY_API CMathUtility 
	{
		
	public:
		
		static float Round(const float &number, const int num_digits);

		static double RoundDouble(double doValue, int nPrecision);

		static float SigFig(float X, int SigFigs);

		static CString FloatToText(float n, int nNumberOfDecimalPlaces = -1);

		static long RoundValue(const float param);
	};
	
} // namespace eag

#endif
