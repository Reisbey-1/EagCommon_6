#ifndef monitor_h
#define monitor_h 1

#include <afxmt.h>    // CCriticalSection
#include <fstream>    /// DLG
#include <crtdbg.h>
#include <afxtempl.h>

namespace eag {

#ifdef MONITOR_EXPORTS
#define MONITOR_API __declspec(dllexport)
#else
#define MONITOR_API __declspec(dllimport)
#endif

// Macro Specification
#define EAG_LOG_INITIALIZE(key) \
	eag::CMonitor::initialize(key);

#define EAG_LOG_CLEANUP() \
	eag::CMonitor::getMonitor()->cleanup();

#define EAG_LOG_EMERGENCY(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_EMERGENCY, notice);
#define EAG_LOG_ALERT(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_ALERT, notice); 
#define EAG_LOG_CRITICAL(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_CRITICAL, notice); 
#define EAG_LOG_ERROR(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_ERROR, notice);
#define EAG_LOG_WARNING(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_WARNING, notice); 
#define EAG_LOG_NOTICE(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_NOTICE, notice);
#define EAG_LOG_INFO(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_INFO, notice);
#ifdef _DEBUG
	#define EAG_LOG_DEBUG(notice) \
	eag::CMonitor::getMonitor()->send(eag::CMonitor::LOG_DEBUG, notice);
#else
	#define EAG_LOG_DEBUG(notice)
#endif

#define EAG_VERIFY_CRITICAL(a,notice) \
	((a) ? (true):(eag::CMonitor::getMonitor()->CriticalFromSystem(notice, __LINE__,GetLastError())))


// Monitor Class
//##ModelId=3978398F02E1
class MONITOR_API CMonitor
{
public:

	typedef void (_stdcall* PFMESSAGECALLBACK)(int enLogLevel, CString&);

typedef enum {  /// md
		LOG_EMERGENCY   = 0, 
		LOG_ALERT, 
		LOG_CRITICAL, 
		LOG_ERROR, 
		LOG_WARNING, 
		LOG_NOTICE, 
		LOG_INFO, 
		LOG_DEBUG
		} typLogLevels;

		class CJobData {
		public:
			CJobData(){};
			~CJobData(){};
			typLogLevels m_enLogLevel;
			DATE m_date;
			CString m_csMessage;
		};
private:
	int m_iRefCount;
	//##ModelId=3978398F03C9
	static CMonitor * m_pMonitor;
	
	static DWORD WINAPI StartProc(LPVOID pParam);
	UINT WorkerThread();
	HANDLE m_hWorkerThreadStopped;
	HANDLE m_hNewJob;
	HANDLE m_hWorkerThread;


	PFMESSAGECALLBACK m_pCallbackMessageFunction;


// internal data variables
	CArray <CJobData, CJobData&> m_csarrayJobQue;

	//##ModelId=3978398F038B
	COPYDATASTRUCT cp;
	//##ModelId=3978398F036D
	HWND m_hWnd;

	HWND m_hAppWnd;
	int m_iAppWindowPriority;

	//##ModelId=3978398F0345
	int m_iMaxPriority;

	//##ModelId=3978398F033B
	CString m_csWindowName;
	//##ModelId=3978398F0331
	int m_iWindowPriority;

	//##ModelId=3978398F0327
	CString m_csFileName;
	//##ModelId=3978398F031D
	int m_iFilePriority;

	std::ofstream m_logFile;

	//##ModelId=3978398F0313
	CString m_csEmailAddress;
	//##ModelId=3978398F0309
	int m_iEmailPriority;


	//##ModelId=3978398F02F7
	CRITICAL_SECTION m_sendSection;

	CRITICAL_SECTION m_JobQueSection;

// internal class members
	//##ModelId=39783990009D
	CMonitor();	

	//##ModelId=397839900094
	bool init();
	//##ModelId=397839900093
	void SendData(CJobData & JobData);
	//##ModelId=39783990008A
	bool GetWindowHandle();

	bool GetAppWindowHandle();

	static void deleteMonitor();

public:
	void cleanup();
	static void initialize(const CString& csBaseKey);

	void setCallbackMessageFunction( PFMESSAGECALLBACK pCallbackMessage );

	//##ModelId=39783990007F
	static CMonitor * getMonitor();

// public class members

	//##ModelId=397839900075
	~CMonitor();


// show CStrings

	//##ModelId=397839900061
	void send(enum typLogLevels enPriority, const CString & rcsMessage);
	
	bool CriticalFromSystem(const CString & rcsMessage , int lineno ,DWORD errnum );


// set new priorities and Lognames:

	//##ModelId=39783990004D
	BOOL setEmailAddress(CString & r_csEmailAddress);

	//##ModelId=397839900039
	BOOL setEmailPriority(int  iEmailPriority);

	//##ModelId=397839900025
	BOOL setFileName(CString & r_csFileName);

	//##ModelId=39783990001B
	BOOL setFilePriority(int iFilePriority);

	//##ModelId=397839900007
	BOOL setWindowName(CString & r_csWindowName);
	
	//##ModelId=3978398F03DB
	BOOL setWindowPriority(int iWindowPriority);
};

} // namespace

#endif	















