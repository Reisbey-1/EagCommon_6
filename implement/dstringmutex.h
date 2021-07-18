/* ---------------------------------------------------------------------
Autoren:
<Freihofer, Hartmut>	<facg1328>	<freihofer@ike.uni-stuttgart.de>
----------------------------------------------------------------------- */

#ifndef _DStringMutex_h
#define _DStringMutex_h


#include "DString.h"
#include <afxmt.h>

namespace eag {

#ifdef DSTRINGMUTEX_EXPORTS
#define DSTRINGMUTEX_API __declspec(dllexport)
#else
#define DSTRINGMUTEX_API __declspec(dllimport)
#endif

//##ModelId=397839850386
class DSTRINGMUTEX_API DStringMutex : public DString ,public CMutex
{
public:
	
	//##ModelId=39783985039B
	DStringMutex();

	//##ModelId=3978398503A4
	DStringMutex(const DStringMutex& s);

	//##ModelId=397839850392
	DStringMutex& operator= (const DStringMutex& ob);
};

} // namespace

#endif
