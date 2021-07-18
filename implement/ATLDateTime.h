// DateTime.h: interface for the CDateTime class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_DATETIME_H__A3E968D9_455B_11D2_9288_00E02921E6D0__INCLUDED_
#define AFX_DATETIME_H__A3E968D9_455B_11D2_9288_00E02921E6D0__INCLUDED_

#include <time.h>
#include <comdef.h>

namespace eag {

#ifdef DATETIME_EXPORTS
#define DATETIME_API __declspec(dllexport)
#else
#define DATETIME_API __declspec(dllimport)
#endif


////////////////////////////////////////////////////////////////////////////
// CDateTime class HELPER definitions

// Verifies will fail if the needed buffer size is too large
#define MAX_TIME_BUFFER_SIZE 128// matches that in timecore.cpp
#define MIN_DATE (-657434.)// about year 100
#define MAX_DATE 2958465. // about year 9999
#define NULL_DATE (-700000.)// for initilizing


// Half a second, expressed in days
#define HALF_SECOND (1.0/172800.0)

// One-based array of days in year at month start
static int rgMonthDays[13] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

////////////////////////////////////////////////////////////////////////////

class CDateTime;
class CDateTimeSpan;
////////////////////////////////////////////////////////////////////////////

// CDateTime class helpers

#define AFX_OLE_DATETIME_ERROR (-1)

DATETIME_API BOOL OleDateFromTm(WORD wYear, WORD wMonth, WORD wDay, WORD wHour, WORD wMinute, WORD wSecond, DATE& dtDest);
DATETIME_API BOOL TmFromOleDate(DATE dtSrc, struct tm& tmDest);
DATETIME_API void TmConvertToStandardFormat(struct tm& tmSrc);
DATETIME_API double DoubleFromDate(DATE dt);
DATETIME_API DATE DateFromDouble(double dbl);


//The MS-time format DATE ends in the year 4637 (15 digits)

//todo: make CDateTime class millisecond conform:						  
//#define  MS_EPSILONTIME  .0000000051
#define  MS_MILLISECOND  (1.0/86400000.0) 

// 10th of a second:
#define  MS_EPSILONTIME   .0000011
#define  MS_SECOND       (1.0/86400.0) 
#define  MS_MINUTE       (1.0/1440.0)
#define  MS_HOUR         (1.0/24) 
#define  MS_DAY          1.0000000000

// 1/1000s could be seperated (+-10%) by the following definition:

#define MS_TIME_EQUAL(value1,value2)\
	(value1 - MS_EPSILONTIME) < value2 && (value1 + MS_EPSILONTIME) > value2

#define MS_TIME_LESSOREQUAL(value1,value2)\
	( value1 - MS_EPSILONTIME ) <= value2

#define MS_TIME_LESS(value1,value2)\
	(( value1 + MS_EPSILONTIME ) < value2)


#define LCID_GERMAN	MAKELCID(MAKELANGID(LANG_GERMAN,SUBLANG_GERMAN), SORT_DEFAULT)

#define LCID_ENGLISH MAKELCID(MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_UK), SORT_DEFAULT)

////////////////////////////////////////////////////////////////////////////

// CDateTime class

class DATETIME_API CDateTime
{
    // Constructors
public:
    CDateTime();
    
    CDateTime(const CDateTime& dateSrc);
    CDateTime(const VARIANT& varSrc);
    CDateTime(DATE dtSrc);
    
    CDateTime(time_t timeSrc);
    CDateTime(const SYSTEMTIME& systimeSrc);
    CDateTime(const FILETIME& filetimeSrc);
    CDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);

    CDateTime(bool bSetNormalCurrentTime, bool bSetUTC);
	

    CDateTime(WORD wDosDate, WORD wDosTime);
    
    // Attributes
public:
    enum DateTimeStatus
    { valid = 0,invalid = 1,null = 2};
    
    enum SummerTimerSystem
    { SUMMERTIME_EU= 0, SUMMERTIME_USA = 1};

    DateTimeStatus GetStatus() const { return m_status;}

    int GetYear() const;
    int GetMonth() const;		// month of year (1 = Jan)
    int GetDay() const;			// day of month (1-31)
    int GetHour() const;		// hour in day (0-23)
    int GetMinute() const;		// minute in hour (0-59)
    int GetSecond() const;		// second in minute (0-59)
    int GetDayOfWeek() const;	// 1=Sun, 2=Mon, ..., 7=Sat
    int GetDayOfYear() const;	// days since start of year, Jan 1 = 1
    int GetHourOfYear() const;	// hours since start of year, Jan 1 00:00:00 = 1
    
	bool GetIsSummerTime( SummerTimerSystem STS=SUMMERTIME_EU ) const; // true if at the current time
	bool CalcSummerTimeRange( SummerTimerSystem STS, DATE &begin, DATE &end ); // true if at the current time


	BOOL IsLeapYear() const;

    DATE GetDATE() const;
	void SetDATE(const DATE& date);
	
	// bNormal == true: sets current normal time (winter time) 
	// despite any local machine settings
	// despite it's winter or summer 
	// despite daylight saving is on or off:

	// UTC == true: Coordinated Universal Time: sets current UTC despite any local machine settings
	// despite its winter or summer 
	// despite daylight is on or off:
	void SetCurrentTime(bool bNormal = false, bool bUTC = false);  

	
	void SetTime_t(time_t time);
  	// Operations
public:
    const CDateTime& operator=(const CDateTime& dateSrc);
    const CDateTime& operator=(const VARIANT& varSrc);
    const CDateTime& operator=(DATE dtSrc);
    
    const CDateTime& operator=(const time_t& timeSrc);
    const CDateTime& operator=(const SYSTEMTIME& systimeSrc);
    const CDateTime& operator=(const FILETIME& filetimeSrc);
    
    BOOL operator==(const CDateTime& date) const;
    BOOL operator!=(const CDateTime& date) const;
    BOOL operator<(const CDateTime& date) const;
    BOOL operator>(const CDateTime& date) const;
    BOOL operator<=(const CDateTime& date) const;
    BOOL operator>=(const CDateTime& date) const;
    
    // DateTime math
    CDateTime operator+(const CDateTimeSpan& dateSpan) const;
    CDateTime operator-(const CDateTimeSpan& dateSpan) const;
    const CDateTime& operator+=(const CDateTimeSpan dateSpan);
    const CDateTime& operator-=(const CDateTimeSpan dateSpan);


    // DateTimeSpan math
    CDateTimeSpan operator-(const CDateTime& date) const;
    
    int SetDateTime(int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec);
    int SetDate(int nYear, int nMonth, int nDay);
    int SetTime(int nHour, int nMin, int nSec);
    BOOL ParseDateTime(LPCTSTR lpszDate, DWORD dwFlags = 0, LCID lcid = LCID_GERMAN);
    BOOL ParseDateTimeEx(LPCTSTR lpszDate, DWORD dwFlags = 0, LCID lcid = LCID_GERMAN);
    
    
    // formatting
    _bstr_t Format( LCID lcid , DWORD dwFlags = 0) const;
    
    _bstr_t Format_special(LPCTSTR lpszFormat=_T("%d.%m.%Y %H:%M:%S")) const;
    //CComString Format(UINT nFormatID) const;
    
    // Implementation
protected:
   
    void SetStatus(DateTimeStatus status) { m_status=status;}
    DATE m_dt;
    DateTimeStatus m_status;
     void CheckRange();
    friend CDateTimeSpan;
};



////////////////////////////////////////////////////////////////////////////

// CDateTimeSpan class
class DATETIME_API CDateTimeSpan
{
    // Constructors
public:
    CDateTimeSpan();
    
    CDateTimeSpan(double dblSpanSrc);
    CDateTimeSpan(const CDateTimeSpan& dateSpanSrc);
    CDateTimeSpan(long lDays, int nHours, int nMins, int nSecs);
    
    // Attributes
public:
    enum DateTimeSpanStatus
    {valid = 0,invalid = 1,null = 2,};
    
    double m_span;
    DateTimeSpanStatus m_status;
    
    void SetStatus(DateTimeSpanStatus status) { m_status=status;}
    DateTimeSpanStatus GetStatus() const { return m_status;}
    
    
    double GetTotalDays() const;// span in days (about -3.65e6 to 3.65e6)
    double GetTotalHours() const;// span in hours (about -8.77e7 to 8.77e6)
    double GetTotalMinutes() const;// span in minutes (about -5.26e9 to 5.26e9)
    double GetTotalSeconds() const;// span in seconds (about -3.16e11 to 3.16e11)
    long GetDays() const;// component days in span
    long GetHours() const;// component hours in span (-23 to 23)
    long GetMinutes() const;// component minutes in span (-59 to 59)
    long GetSeconds() const;// component seconds in span (-59 to 59)
    
    // Operations
public:
    const CDateTimeSpan& operator=(double dblSpanSrc);
    const CDateTimeSpan& operator=(const CDateTimeSpan& dateSpanSrc);
    
    BOOL operator==(const CDateTimeSpan& dateSpan) const;
    BOOL operator!=(const CDateTimeSpan& dateSpan) const;
    BOOL operator<(const CDateTimeSpan& dateSpan) const;
    BOOL operator>(const CDateTimeSpan& dateSpan) const;
    BOOL operator<=(const CDateTimeSpan& dateSpan) const;
    BOOL operator>=(const CDateTimeSpan& dateSpan) const;
    
    // DateTimeSpan math
    CDateTimeSpan operator+(const CDateTimeSpan& dateSpan) const;
    CDateTimeSpan operator-(const CDateTimeSpan& dateSpan) const;
    const CDateTimeSpan& operator+=(const CDateTimeSpan dateSpan);
    const CDateTimeSpan& operator-=(const CDateTimeSpan dateSpan);
    CDateTimeSpan operator-() const;
    
    operator double() const;
    
    void SetDateTimeSpan(long lDays, int nHours, int nMins, int nSecs);
    
    // formatting
    _bstr_t Format(LPCTSTR pFormat) const;
    //CComString Format(UINT nID) const;
    
    // Implementation
public:
    void CheckRange();
    friend DATETIME_API CDateTime;
};

}// namespace eag

#endif // AFX_DATETIME_H__A3E968D9_455B_11D2_9288_00E02921E6D0__INCLUDED_
