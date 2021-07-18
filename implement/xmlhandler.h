/*
//=============================================================================
//
// = PROJECT
//
//     XML -- XML TreeBuilder
//
// = FILENAME
//
//     XmlHandler.h
//
//
// = SUMMARY
//
//     SAX Header-File for the XmlHandler class, the base class for 
//     each class should be able to be used in building a C++ datastruct 
//     based on XML files or streams
//
//
// = AUTHOR(S)
//
//     Roland Kopetzky
//
// = COPYRIGHT
//
//     2000  Ennovatis -- All Rights Reserved
//
//
//=============================================================================
*/

#ifndef _XMLHANDLER_H__
#define _XMLHANDLER_H__

#include <string>
#include "ATLDateTime.h"


namespace eag
{

class XMLTREEBUILDER_API CXmlHandler

//=============================================================================
//
// = TITLE
//
//     XmlHandler
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//	   XmlHandler is a mixin interface that must be inherited
//	   by every object that can receive data from the
//	   XmlTreeBuilder dispatcher. These objects will
//	   never be called directly by SAX.
//
//=============================================================================

{
	friend class CXmlTreeBuilder;

public:
	CXmlHandler() {};

	// method to implement class building
	virtual CXmlHandler* startElement(const StartElementEvent &) = 0;

	// method to implement class streaming
	virtual bool streamElement(std::ostream& stream, std::string sName="", int level=0) const = 0;  /// DLG

	// Returns whether or not to pop the handler stack
	virtual bool endElement()
		{return true; };

	virtual void data(const DataEvent &)
		{};
	// helper method to convert CharString to CString
	std::string getString(CharString ChStr)
		{
			std::string stdString("");
			for (size_t i=0; i<ChStr.len; i++)
				stdString += char(ChStr.ptr[i]);
			return stdString;	
		};
	std::string getAttribute(std::string stdName, const StartElementEvent &event)
		{
			for (size_t num = 0; num < event.nAttributes; num++)
				if (stdName.compare(getString(event.attributes[num].name)) == 0)
					return getString(event.attributes[num].data);
			return "";
		};
	void tabs(std::ostream& stream, int number) const   /// DLG
		{
			for (int i = 0; i < number; i++)
				stream << "\t";
		};
	bool doEncode() const
		{
			return m_bEncode;
		}
	bool doOptimize() const
		{
			return m_bOptimize;
		}

	void replaceChars(std::string& modifyMe, std::string findMe, std::string newChars)
		{
			int i = modifyMe.find(findMe, 0);
			// Replace the find string with newChars
			if(i != std::string::npos)
				modifyMe.replace(i, newChars.size(), newChars);
		}


private:
	static bool m_bEncode;
	static bool m_bOptimize;
};

//=============================================================================

class XMLTREEBUILDER_API CXmlNullHandler : public CXmlHandler

//=============================================================================
//
// = TITLE
//
//     CXmlNullHandler
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//	   NULL Handler 
//
//=============================================================================

{
public:
	CXmlNullHandler() {};

	virtual CXmlHandler* startElement(const StartElementEvent &)
		{ return NULL; }

	virtual bool streamElement(std::ostream& stream, std::string sName="", int level=0) const   /// DLG
		{ return false; }

	virtual bool endElement()
		{ return true; }

	virtual void data(const DataEvent &)
		{};
};

//=============================================================================

class XMLTREEBUILDER_API CXmlTopLevelHandler : public CXmlHandler

//=============================================================================
//
// = TITLE
//
//     CXmlTopLevelHandler
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//	   NULL Handler 
//
//=============================================================================

{
public:
	CXmlTopLevelHandler(CXmlHandler* pTopHandler, std::string sVersion)
		: m_pTopHandler(pTopHandler),
		  m_sVersion(sVersion)
	{};

	virtual CXmlHandler* startElement(const StartElementEvent &)
	{ return m_pTopHandler; }

	virtual bool streamElement(std::ostream& stream, std::string sName, int level=0) const   /// DLG
	{
		// write header
		// z.B. <!DOCTYPE META-DAT SYSTEM "1.0" "META-DAT.DTD">
		stream << "<!DOCTYPE " << sName.c_str() << " SYSTEM";
		stream << " \"" << m_sVersion.c_str() << "\"";
		stream << " \"" << sName.c_str() << ".DTD\">" << std::endl;

		return m_pTopHandler->streamElement(stream, sName);
	}

	virtual bool endElement()
	{ return true; }

	virtual void data(const DataEvent &)
	{};

	CXmlHandler* m_pTopHandler;

protected:
	std::string m_sVersion;
};

//=============================================================================

template <class T>
class XMLTREEBUILDER_API CXmlValue : public CXmlHandler

//=============================================================================
//
// = TITLE
//
//     CXmlValue
//
// = CLASSTYPE
//
//     template class
//
//
// = DESCRIPTION
//
//     base class for value classes
//
//=============================================================================

{

public:
		
	CXmlValue()
	{ }

	CXmlValue(T value) : m_Value(value)
	{ }

	CXmlValue(const CXmlValue& orig) : m_Value(orig.m_Value)
	{ }

	virtual ~CXmlValue()
	{ }

	const CXmlValue& operator = (const CXmlValue& rhs)
	{ m_Value = rhs.m_Value; return *this; }

	const CXmlValue& operator = (T rhs)
	{ m_Value = rhs; return *this; }

	operator T () const
	{ return m_Value; } 

	bool operator == (const CXmlValue& rhs) const 
	{ return (m_Value == rhs.m_Value) ? true : false; }

	bool operator == (const T& ob) const 
	{ return (m_Value == ob) ? true : false; }

	bool operator != (const CXmlValue& rhs) const 
	{ return (! (*this == rhs));}

// specialized methods

	virtual CXmlHandler* startElement(const StartElementEvent &)
	{ return NULL; }

	virtual bool endElement()
	{ return true; }

	virtual void data(const DataEvent &event)
	{}

protected:

	T m_Value;
};

//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<std::string>;

class XMLTREEBUILDER_API CXmlString : public CXmlValue<std::string>

//=============================================================================
//
// = TITLE
//
//     CXmlString
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//    instead of in attributes. This handler is for
//     std::string data. 
//
//=============================================================================

{
public:
	CXmlString() : CXmlValue<std::string> ("") { }

	CXmlString(std::string str) : CXmlValue<std::string> (str){ }

// additional operator
	const CXmlString& operator = (std::string rhs)
	{ m_Value = rhs; return *this; }

	const char* string(void) const
	{ return m_Value.c_str(); }

	CXmlString operator + (const CXmlString& rhs)
	{ return CXmlString(m_Value + rhs.m_Value);} 

	bool isEmpty(void)
	{ return m_Value == ""; }

// xml events
	virtual void data(const DataEvent &event)
		{ m_Value = getString(event.data); }

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip empty strings (default)
		if ( m_Value.size() == 0 && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";

		if ( doEncode() )
		{
			for (unsigned int i=0; i<m_Value.size(); i++)
			{
				if ( m_Value.at(i) == '<' )
					stream << "&lt;";
				else if ( m_Value.at(i) == '>' )
					stream << "&gt;";
				else if ( m_Value.at(i) == '&' )
					stream << "&amp;";
				else
					stream << m_Value.at(i);
			}
		}
		else
		{
			stream << m_Value.c_str();
		}
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};


//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<double>;

class XMLTREEBUILDER_API CXmlDouble : public CXmlValue<double>

//=============================================================================
//
// = TITLE
//
//     CXmlDouble
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to double. 
//
//=============================================================================

{
public:
	
	CXmlDouble():CXmlValue<double> (0.0) {  }

	CXmlDouble(double value):CXmlValue<double> (value) {}

	virtual void data(const DataEvent &event)
		{
			m_Value = atof(event.data.ptr);  
			if ( m_Value == 0.0 )
			{
				// normally 0.0 is not allowed, because this is default and not written
				std::string sReplace = getString(event.data);
				replaceChars(sReplace, ",", ".");

				// try again
				m_Value = atof(sReplace.c_str());
			}
		}

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip 0.0 (default)
		if ( m_Value == 0.0  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value;
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<int>;

class XMLTREEBUILDER_API CXmlInteger : public CXmlValue<int>

//=============================================================================
//
// = TITLE
//
//     CXmlInteger
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to integer. 
//
//=============================================================================

{
public:
	CXmlInteger():CXmlValue<int> (0) {  }

	CXmlInteger(int value):CXmlValue<int> (value) {}

	virtual void data(const DataEvent &event)
		{ m_Value = atoi(event.data.ptr); }   

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip 0 (default)
		if ( m_Value == 0  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value;
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<bool>;

class XMLTREEBUILDER_API CXmlBool : public CXmlValue<bool>

//=============================================================================
//
// = TITLE
//
//     CXmlBool
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to bool. 
//
//=============================================================================

{
public:
	CXmlBool():CXmlValue<bool> (false) {  }

	CXmlBool(bool value):CXmlValue<bool> (value) {}

		
	virtual void data(const DataEvent &event)
	{
		m_Value = false;
		std::string sValue = getString(event.data);
		if ( sValue.compare("true") == 0 )
			m_Value = true;
	}

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip false (default)
		if ( m_Value == false  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		if ( m_Value )
			stream << "true";
		else
			stream << "false";
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<long>;

class XMLTREEBUILDER_API CXmlLong : public CXmlValue<long>

//=============================================================================
//
// = TITLE
//
//     CXmlBool
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to long. 
//
//=============================================================================

{
public:
	
	CXmlLong():CXmlValue<long> (0) {  }

	CXmlLong(long value):CXmlValue<long> (value) {}


	virtual void data(const DataEvent &event)
		{ m_Value = atol(event.data.ptr); }   

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip 0 (default)
		if ( m_Value == 0  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value;
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};


//=============================================================================

template class XMLTREEBUILDER_API CXmlValue<CDateTime>;

class XMLTREEBUILDER_API CXmlDateTime : public CXmlValue<CDateTime>

//=============================================================================
//
// = TITLE
//
//     CXmlDateTime
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to CDateTime. 
//
//=============================================================================

{
public:
	
	CXmlDateTime():CXmlValue<CDateTime> (NULL_DATE) {  }

	CXmlDateTime(double value):CXmlValue<CDateTime> (value) {}

	double date () const {return m_Value.GetDATE();}

	virtual void data(const DataEvent &event){ 
		m_Value.ParseDateTime((LPCTSTR)getString(event.data).c_str()); 
	}

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip NULL_DATE (default)
		if ( MS_TIME_EQUAL(NULL_DATE, m_Value.GetDATE())  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value.Format(LCID_GERMAN);
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

class XMLTREEBUILDER_API CXmlDate : public CXmlValue<CDateTime>

//=============================================================================
//
// = TITLE
//
//     CXmlDate
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to CDateTime. 
//
//=============================================================================

{
public:
	
	CXmlDate():CXmlValue<CDateTime> (NULL_DATE) {  }

	CXmlDate(double value):CXmlValue<CDateTime> (value) {}

	double date () const {return m_Value.GetDATE();}

	virtual void data(const DataEvent &event){ 
		m_Value.ParseDateTime((LPCTSTR)getString(event.data).c_str(),VAR_DATEVALUEONLY); 
	}

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip NULL_DATE (default)
		if ( MS_TIME_EQUAL(NULL_DATE, m_Value.GetDATE())  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value.Format(LCID_GERMAN,VAR_DATEVALUEONLY);
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

class XMLTREEBUILDER_API CXmlTime : public CXmlValue<CDateTime>

//=============================================================================
//
// = TITLE
//
//     CXmlTime
//
// = CLASSTYPE
//
//     class
//
//
// = DESCRIPTION
//
//     To be used if data will be held between tags
//     instead of in attributes. This handler is for
//     strings that get converted to CDateTime. 
//
//=============================================================================

{
public:
	
	CXmlTime():CXmlValue<CDateTime> (NULL_DATE) {  }

	CXmlTime(double value):CXmlValue<CDateTime> (value) {}

	double date () const {return m_Value.GetDATE();}

	virtual void data(const DataEvent &event){ 
		m_Value.ParseDateTime((LPCTSTR)getString(event.data).c_str(), VAR_TIMEVALUEONLY); 
	}

	virtual bool streamElement(std::ostream& stream, std::string sName, int level) const
	{
		// skip NULL_DATE (default)
		if ( MS_TIME_EQUAL(NULL_DATE, m_Value.GetDATE())  && doOptimize() )
			return true;

		tabs(stream,level);
		stream << "<" << sName.c_str() << ">";
		stream << m_Value.Format(LCID_GERMAN, VAR_TIMEVALUEONLY);
		stream << "</" << sName.c_str() << ">";
		stream << std::endl;

		return true;
	}
};

//=============================================================================

}  // namespace eag

#endif // #ifndef _XMLHANDLER_H__

//=============================================================================
