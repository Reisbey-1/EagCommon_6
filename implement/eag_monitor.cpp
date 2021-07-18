#include "stdafx.h"
#include "eag_monitor.h"
#include "registrykey.h"
#include "AtlDateTime.h"

namespace eag {

//instance of m_pMonitor 
//##ModelId=3978398F03C9
CMonitor * CMonitor::m_pMonitor = NULL;


//##ModelId=39783990009D
CMonitor::CMonitor()
{  
	m_pMonitor				= this ;

	InitializeCriticalSection(&m_sendSection);
	InitializeCriticalSection(&m_JobQueSection);
	m_csarrayJobQue.SetSize(0,30);

	m_pCallbackMessageFunction	= NULL;

	cp.dwData					= 0;
	cp.cbData					= 1;
	cp.lpData					= "\0";
	m_hWnd						= NULL;

	m_hAppWnd					= NULL;
	m_iAppWindowPriority		= 0;

	m_iMaxPriority				= 0;
	m_iWindowPriority			= 0;
	m_iFilePriority				= 0;	
	m_iEmailPriority			= 0;

	m_hWorkerThreadStopped		= CreateEvent(NULL,TRUE,TRUE,NULL); // signaled, since Thread is stopped
	m_hNewJob					= CreateEvent(NULL,TRUE,FALSE,NULL);

	m_hWorkerThread				= NULL;

#ifdef _DEBUG
	m_iRefCount				= 0;
//	init();
#else
	m_iRefCount				= 0;
#endif

} 

//##ModelId=397839900075
CMonitor::~CMonitor()
{
	DeleteCriticalSection(&m_sendSection);
	DeleteCriticalSection(&m_JobQueSection);
}

void CMonitor::initialize(const CString &csBaseKey)
{
	eag::CRegistryKey::set_BaseKey( csBaseKey );
	
	CMonitor *pMonitor = getMonitor();
	
	if ( pMonitor ) {
		pMonitor->m_iRefCount++;
		pMonitor->init();
	}

}
 

void CMonitor::cleanup()
{
	m_iRefCount--;

	if ( m_iRefCount <= 0 ) {

		SetEvent(m_hWorkerThreadStopped);

		if (m_csarrayJobQue.GetSize() > 10)
			Sleep(1000);
		else
			Sleep(100);
		
		EnterCriticalSection(&m_JobQueSection);
			m_csarrayJobQue.RemoveAll();
		LeaveCriticalSection(&m_JobQueSection);

		if ( m_hWorkerThread != NULL)
		{
			WaitForSingleObject( m_hWorkerThread, 400) ;
		}

		m_hWorkerThread = NULL;

		CMonitor::deleteMonitor();
	}
}


//##ModelId=39783990007F
CMonitor * CMonitor::getMonitor()
{

	if ( m_pMonitor )
		return m_pMonitor;
	else 
		return new CMonitor;

}

void CMonitor::deleteMonitor()
{
	if ( m_pMonitor != NULL )
	{	
		delete m_pMonitor;
		m_pMonitor=NULL;
	}
}

//##ModelId=397839900094
bool CMonitor::init()
{
	m_iRefCount++;

	bool bInitOK = true;
	m_iMaxPriority = 7; //during startup

	if ( CRegistryKey::get_BaseKey().IsEmpty() ) {
	
		CRegistryKey::set_BaseKey( L"SOFTWARE\\ennovatis\\VEC - Visual Energy Center" );
	}

	CRegistryKey eagRegKey(L"Monitoring");
	DWORD dwValue;


//first things first:

//*************Window logging**************

	if (! eagRegKey.get(L"WindowPriority", dwValue ))
		bInitOK = false;
	else
		m_iWindowPriority = dwValue;

	if (! eagRegKey.get(L"WindowName", m_csWindowName ))
		bInitOK = false;

//***************Application Window logging*******************

	if ( eagRegKey.get(L"ApplicationWindowPriority", dwValue ))
		m_iAppWindowPriority = dwValue;

//***************File logging*******************
	
	if (! eagRegKey.get(L"FilePriority", dwValue ))
		bInitOK = false;
	else
		m_iFilePriority = dwValue;

	if (! eagRegKey.get(L"FileName", m_csFileName ))
		bInitOK = false;

#ifdef _DEBUG 
	m_csFileName += L".DEBUG";
#endif	

	//m_logFile.open(m_csFileName, ios::out ,filebuf::sh_write || filebuf::sh_read);
	m_logFile.open(m_csFileName) ;/// DLG , ios::out ,filebuf::sh_write || filebuf::sh_read);

	if (!m_logFile.is_open()) {
		CString csMessage;
		csMessage.Format(L"CMonitor::init -> can not open logfile '%s'", m_csFileName );
		send(LOG_INFO,csMessage);
	}

//*************Email logging:***************

	if (! eagRegKey.get(L"EmailPriority", dwValue ))
		bInitOK = false;
	else
		m_iEmailPriority = dwValue;
	

	if (! eagRegKey.get(L"EmailAddress", m_csEmailAddress ))
		bInitOK = false;


//*** find maximum priority for performance:

	if ( bInitOK )
		m_iMaxPriority = 0;
	else
		m_iMaxPriority = 6;
	

	if (m_iWindowPriority > m_iMaxPriority)
		m_iMaxPriority = m_iWindowPriority;
	
	if (m_iFilePriority > m_iMaxPriority)
		m_iMaxPriority = m_iFilePriority;

	if (m_iEmailPriority > m_iMaxPriority)
		m_iMaxPriority = m_iEmailPriority;

	if ( bInitOK ) {

		if ( WaitForSingleObject( m_hWorkerThreadStopped, 0  ) == WAIT_OBJECT_0 ) {

			DWORD dwThreadID=0;
			m_hWorkerThread = CreateThread( NULL,0, StartProc, NULL, 0, &dwThreadID);
		}
	}

	m_iRefCount--;

	return bInitOK;
}

DWORD WINAPI CMonitor::StartProc(LPVOID pParam){

	// because its a Singleton, I don't have to use getMonitor:
	return m_pMonitor->WorkerThread();
}

UINT CMonitor::WorkerThread()
{

	if ( WaitForSingleObject( m_hWorkerThreadStopped, 0  ) == WAIT_TIMEOUT ) 
		return 0;

	ResetEvent(m_hWorkerThreadStopped);

	HANDLE pHandles[2];
	pHandles[0] = m_hNewJob;
	pHandles[1] = m_hWorkerThreadStopped;

	clock_t clockWndRefresh = clock();;
	DWORD ObjectSignaled;
	CJobData JobData;
	int iJobs = 0;

	CoInitializeEx(NULL, COINIT_MULTITHREADED); 

	do {
	
		ObjectSignaled = WaitForMultipleObjects(2,pHandles,FALSE,10000);

		if ( ObjectSignaled - WAIT_OBJECT_0 == 1 )  // means m_hWorkerThreadStopped is signaled
			break;

		// else a new job arraived:

		iJobs = 1;
		
		while ( iJobs > 0) {

			// first get the message:
			EnterCriticalSection(&m_JobQueSection);

			try 
			{
				iJobs = m_csarrayJobQue.GetSize();
				
				if ( iJobs > 0 ) 
				{
					JobData = m_csarrayJobQue[0]; // get one message at a time
					m_csarrayJobQue.RemoveAt(0);
					iJobs--; 
				}
				else 
				{
					LeaveCriticalSection(&m_JobQueSection);
					break;
				}
			}
			catch(...)
			{
			}
			
			LeaveCriticalSection(&m_JobQueSection);
		
			try
			{
				// send the message:
				SendData(JobData);	// send one message at a time
			}
			catch(...)
			{
			}

/*			if (clockWndRefresh < (clock() - 60000) ) // every 60 seconds refresh window pointer
			{
				clockWndRefresh = clock();
				m_hWnd = NULL;
			}
*/
		}

		// and last but not least:
		ResetEvent(m_hNewJob);
			
	} while (1);

	JobData.m_csMessage = L"CMonitor::WorkerThread - stopped";
	JobData.m_enLogLevel = LOG_INFO;
	SendData(JobData);

	return 0;
}


//##ModelId=39783990004D
BOOL	
CMonitor::setEmailAddress(CString & r_csEmailAddress)
{

	m_csEmailAddress = r_csEmailAddress;

	CRegistryKey eagRegKey(L"Monitoring");

	return eagRegKey.set(L"EmailAddress", r_csEmailAddress);

}

//##ModelId=397839900039
BOOL	
CMonitor::setEmailPriority(int iEmailPriority)
{

	m_iEmailPriority = iEmailPriority;

//	if (m_iEmailPriority > m_iMaxPriority)
//		m_iMaxPriority = m_iEmailPriority;

	CRegistryKey eagRegKey(L"Monitoring");

	DWORD dwValue = iEmailPriority;

	return eagRegKey.set(L"EmailPriority", dwValue);
}


//##ModelId=397839900025
BOOL	
CMonitor::setFileName(CString & r_csFileName)
{

	m_csFileName = r_csFileName;

#ifdef _DEBUG 
	m_csFileName += L".DEBUG";
#endif	

	if (m_logFile.is_open())
		m_logFile.close();

	///m_logFile.open(m_csFileName, std::ios::app ,filebuf::sh_read);
	m_logFile.open(m_csFileName);

	if (!m_logFile.is_open()) {
		CString csMessage;
		csMessage.Format(_T("CMonitor::init -> can not open logfile '%s'"), m_csFileName );
		send(LOG_WARNING,csMessage);
		return false;
	}

	CRegistryKey eagRegKey(_T("Monitoring"));

	const wchar_t* fln = L"FileName";
	return	eagRegKey.set(fln, r_csFileName);
 
}


//##ModelId=39783990001B
BOOL	
CMonitor::setFilePriority(int iFilePriority)
{

	m_iFilePriority = iFilePriority;

//	if (m_iFilePriority > m_iMaxPriority)
//		m_iMaxPriority = m_iFilePriority;

	
	CRegistryKey eagRegKey(L"Monitoring");

	DWORD dwValue = iFilePriority;

	return eagRegKey.set(L"FilePriority", dwValue);
}


//##ModelId=397839900007
BOOL	
CMonitor::setWindowName(CString & r_csWindowName)
{
	m_csWindowName = r_csWindowName;

	CRegistryKey eagRegKey(L"Monitoring");

	return eagRegKey.set(L"WindowName", r_csWindowName);
}

	
//##ModelId=3978398F03DB
BOOL	
CMonitor::setWindowPriority(int  iWindowPriority)
{

	m_iWindowPriority = iWindowPriority;

//	if (m_iWindowPriority > m_iMaxPriority)
//		m_iMaxPriority = m_iWindowPriority;

	CRegistryKey eagRegKey(L"Monitoring");

	DWORD dwValue = iWindowPriority;

	return eagRegKey.set(L"WindowPriority", dwValue);
}


void CMonitor::setCallbackMessageFunction( PFMESSAGECALLBACK pCallbackMessage )
{
	m_pCallbackMessageFunction = pCallbackMessage;

}


//##ModelId=39783990008A
bool 
CMonitor::GetWindowHandle()
{
// find the CMonitor application window

	m_hWnd = ::FindWindow(NULL,(LPCTSTR) m_csWindowName.GetString()) ;
	
	if(m_hWnd == NULL) 
	{

		ATOM WindowAtom = GlobalFindAtom(m_csWindowName);

		if ( WindowAtom != 0)
		{
			union  {
			LPCTSTR lpClassName;
			ATOM    WindowAtom[2];
			} className;

			className.lpClassName		= NULL;
			className.WindowAtom[0]		= WindowAtom;
			m_hWnd = ::FindWindow(className.lpClassName ,NULL );
		}

		if ( m_hWnd == NULL) 
			return false;
	}
	
	return true;
}

bool 
CMonitor::GetAppWindowHandle()
{

// find the CMonitor application window
	CWnd* pAppWnd = AfxGetMainWnd();
	if ( pAppWnd )
	{
		m_hAppWnd = pAppWnd->m_hWnd;
		return true;
	}

	m_hAppWnd = NULL;

	return false;
}

//##ModelId=397839900093
void CMonitor::SendData(CJobData & JobData)
{
	CString csMessage;

	switch (JobData.m_enLogLevel) {

	case LOG_INFO:
		csMessage = L"INFO:     " + JobData.m_csMessage;
		break;
	
	case LOG_NOTICE:
		csMessage = L"NOTICE:   " + JobData.m_csMessage;
		break;

	case LOG_DEBUG:
		csMessage = L"DEBUG:    " + JobData.m_csMessage;
		break;

	case LOG_ERROR:
		csMessage = L"ERROR:    " + JobData.m_csMessage;
		break;

	case LOG_WARNING:
		csMessage = L"WARNING:  " + JobData.m_csMessage;
		break;

	case LOG_EMERGENCY:
		csMessage = "EMERGENCY:" + JobData.m_csMessage;
		break;

	case LOG_ALERT:
		csMessage = L"ALERT:    " + JobData.m_csMessage;
		break;

	case LOG_CRITICAL:
		csMessage = L"CRITICAL: " + JobData.m_csMessage;
		break;

	default:
		csMessage = "          " + JobData.m_csMessage;
		break;
	}

	// get the current UTC time
	csMessage = CDateTime(JobData.m_date).Format_special(_T("%d.%m.%Y %H:%M:%S ")) + csMessage;

	if (m_hWnd == NULL )
		GetWindowHandle();


	// send the structure to LogWindow via the system
	if ((JobData.m_enLogLevel <= m_iWindowPriority) && m_hWnd != NULL ) {
		USES_CONVERSION;
		wchar_t *pcMessage=new wchar_t[csMessage.GetLength() +1];
		wcscpy(pcMessage, csMessage.GetString());

		cp.dwData = 0;
		cp.cbData = 2*csMessage.GetLength() +1;
		cp.lpData = pcMessage;

		if ( ::SendMessage(m_hWnd,WM_COPYDATA,(UINT)NULL,(long)&cp) == 0)
			m_hWnd = NULL;


		delete pcMessage;
	}
/*
	if ( m_hAppWnd == NULL) 
		GetAppWindowHandle();

	// send the structure to ApplicationWindow via the system
	if ((JobData.m_enLogLevel <= m_iAppWindowPriority) && m_hAppWnd != NULL ) 
	{
		//USES_CONVERSION;
		wchar_t *pcMessage=new wchar_t[csMessage.GetLength() +1];
		wcscpy(pcMessage, csMessage);

		cp.dwData = 0;
		cp.cbData = csMessage.GetLength() +1;
		cp.lpData = pcMessage;

		if ( ::PostMessage(m_hAppWnd,WM_COPYDATA,(UINT)NULL,(long)&cp) == 0)
			m_hAppWnd = NULL;

		delete pcMessage;
	}
*/
	// send message to Log File
	if (JobData.m_enLogLevel <= m_iFilePriority) 
	{
		m_logFile << csMessage << std::endl << std::flush;
	}

	// send message to callback funktion (if set)
	if ( m_pCallbackMessageFunction )
	{
		try 
		{
			m_pCallbackMessageFunction( JobData.m_enLogLevel, JobData.m_csMessage );
		}
		catch(...)
		{
			m_pCallbackMessageFunction = NULL;
		}
	}

	// send message to Mail File
	if (JobData.m_enLogLevel <= m_iEmailPriority) {
		std::ofstream logFile( "mailmessage.txt", std::ios::out );
		logFile << csMessage << std::endl;
		logFile.close();

		// Stelle die Startinformationen fuer den zu startenden Treiber zusammen:
		STARTUPINFO si  = {0};
		si.cb			=sizeof (si);
		si.lpTitle		=NULL; 
		si.wShowWindow	=SW_HIDE;
		PROCESS_INFORMATION pi; //wird fuer die Prozessueberwachung eingesetzt

		if(CreateProcess(NULL,	//
				m_csEmailAddress.GetBuffer(m_csEmailAddress.GetLength()),// 
				NULL,					// keine Process Security Informationen
				NULL,					// keine Thread Security Informationen
				TRUE,					// erbbare handles
				NORMAL_PRIORITY_CLASS,	// Normale Prioritaet
				NULL,					// Environment dieses Programms
				NULL,
				&si,					// Startupinformation
				&pi)					// Processinformation
			== FALSE) {
		}
		else {
		
			TRACE(L"PID:%li, TID:%li\n",pi.dwProcessId,pi.dwThreadId); 
		}

		m_csEmailAddress.ReleaseBuffer();

	}
	return;
}

void CMonitor::send(enum typLogLevels enPriority, const CString & rcsMessage)
{
	EnterCriticalSection(&m_sendSection);

	if ( m_iMaxPriority < enPriority) 
	{
		LeaveCriticalSection(&m_sendSection);
		return;
	}

	try {

		CJobData JobData;
		JobData.m_enLogLevel = enPriority;
		JobData.m_csMessage = rcsMessage;

		CDateTime cdtNow;
		cdtNow.SetCurrentTime(true);
		JobData.m_date = cdtNow.GetDATE();

		EnterCriticalSection(&m_JobQueSection);

			if (m_csarrayJobQue.GetSize() > 150 ) // in case thread isn't working
				m_csarrayJobQue.RemoveAt(0,50);   // spill away some messages

			m_csarrayJobQue.Add(JobData);

		LeaveCriticalSection(&m_JobQueSection);

		SetEvent(m_hNewJob);
	}
	catch (...){ // don't leave this section, without releasing critical section:
		TRACE(L"CMonitor::send - exception"); 
	};

	if ( m_iRefCount <= 0 ) {

		LeaveCriticalSection(&m_sendSection);
		cleanup();
		return; // don't call any other function, because monitor doesn't exist any more
	}

	LeaveCriticalSection(&m_sendSection);

} 


bool 
CMonitor::CriticalFromSystem( const CString & rcsMessage, int lineno ,DWORD errnum ){

	LPWSTR lpBuffer=NULL;
	//FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errnum, LANG_NEUTRAL, (LPWSTR)&lpBuffer, 0, NULL);
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, errnum, LANG_NEUTRAL, lpBuffer, 0, NULL);

	wchar_t cBuf[64];
	CString csBuffer = rcsMessage;
	csBuffer += L" / ";
	csBuffer += lpBuffer;
	csBuffer.TrimRight();
	csBuffer += L" / #";
	csBuffer += _itow( lineno, cBuf, 10);

	send(LOG_CRITICAL, csBuffer);

	LocalFree(lpBuffer);

	return false;
}


} // namespace



