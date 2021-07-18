// file EagCommonInclude.h
#if !defined(EAG_COMMOND__INCLUDED_)
#define EAG_COMMOND__INCLUDED_


////////////////////////////////////////////////////////
#include "xmldef.h"

#include "ATLDateTime.h"
#include "FileUtility.h"
#include "MathUtility.h"
#include "eag_monitor.h"
#include "Regexp.h"
#include "registrykey.h"
#include "dstring.h"
#include "dstringmutex.h"
//#include "extendeddstring.h"
#include "stringutility.h"
#include "xmlstruct.h"
#include "xmlhandle.h"
#include "xmlscanner.h"
#include "stringutility.h"
////////////////////////////////////////////////////////

// The following will ensure that when building an application (or another DLL)
// using this DLL, the appropriate .LIB file will automatically be used
// when linking.
#ifndef _MYLIB_NOAUTOLIB_
#ifdef _DEBUG
#pragma comment(lib, "eagcommond.lib")
#else
#pragma comment(lib, "eagcommon.lib")
#endif
#endif

#endif // !defined(EAG_COMMOND__INCLUDED_