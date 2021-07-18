#include "stdafx.h"
#include "DStringMutex.h"

namespace eag {

//##ModelId=39783985039B
DStringMutex::DStringMutex(){//Konstruktor ohne initialisierung

};



//=====================COPY===========================================
//##ModelId=3978398503A4
DStringMutex::DStringMutex(const DStringMutex& s)
: DString(s)
{ 
};

//##ModelId=397839850392
DStringMutex& 
DStringMutex::operator= (const DStringMutex& ob){

	DString::operator=(ob);

return *this;
};

} // namespace
