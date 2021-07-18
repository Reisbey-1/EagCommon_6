// MddlHandle Implementation File
//

#include "stdafx.h"
#include "XmlHandle.h"


/////////////////////////////////////////////////////////////////////////////
// namespace eag

namespace eag
{

//===========================================================================
// CXmlElementHandle
//===========================================================================

CXmlElementHandle::CXmlElementHandle()
{
	val = 0;
}

CXmlElementHandle::CXmlElementHandle(const CXmlElementHandle& h)
{
	SetValue(h);
}

CXmlElementHandle::CXmlElementHandle(const unsigned long l)
{
	SetValue(l);
}

CXmlElementHandle::CXmlElementHandle(const int i)
{
	SetValue(i);
}

unsigned long CXmlElementHandle::Value(void)
{
  return val;
}

BOOL CXmlElementHandle::isValid(void)
{
  if ( val == 0 )
	  return FALSE;

  return TRUE;
}

CXmlElementHandle& CXmlElementHandle::operator=(const CXmlElementHandle& h)
{
  SetValue(h);
  return *this;
}

CXmlElementHandle& CXmlElementHandle::operator=(const unsigned long l)
{
  SetValue(l);
  return *this;
}

CXmlElementHandle& CXmlElementHandle::operator=(const int i)
{
  SetValue(i);
  return *this;
}

void CXmlElementHandle::SetValue(const CXmlElementHandle& h)
{
	val = h.val;
}

void CXmlElementHandle::SetValue(const unsigned long l)
{
	val = l;
}

void CXmlElementHandle::SetValue(const int i)
{
	val = i;
}

//===========================================================================
// CXmlItemHandle
//===========================================================================

CXmlItemHandle::CXmlItemHandle()
{
	val = 0;
}

CXmlItemHandle::CXmlItemHandle(const CXmlItemHandle& h)
{
  SetValue(h);
}

CXmlItemHandle::CXmlItemHandle(const unsigned long l)
{
  SetValue(l);
}

CXmlItemHandle::CXmlItemHandle(const int i)
{
  SetValue(i);
}

unsigned long CXmlItemHandle::Value(void)
{
  return val;
}

BOOL CXmlItemHandle::isValid(void)
{
  if ( val == 0 )
	  return FALSE;

  return TRUE;
}

CXmlItemHandle& CXmlItemHandle::operator=(const CXmlItemHandle& h)
{
  SetValue(h);
  return *this;
}

CXmlItemHandle& CXmlItemHandle::operator=(const unsigned long l)
{
  SetValue(l);
  return *this;
}

CXmlItemHandle& CXmlItemHandle::operator=(const int i)
{
  SetValue(i);
  return *this;
}

void CXmlItemHandle::SetValue(const CXmlItemHandle& h)
{
	val = h.val;
}

void CXmlItemHandle::SetValue(const unsigned long l)
{
	val = l;
}

void CXmlItemHandle::SetValue(const int i)
{
	val = i;
}

} // namespace eag

//===========================================================================
// ENDE
//===========================================================================
