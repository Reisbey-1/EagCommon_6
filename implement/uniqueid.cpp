#include "uniqueid.h"

namespace eag {

//##ModelId=397839840321
CUniqueId::CUniqueId(double dSeed)
	
{
	m_hostId    = 0;
	m_processId = 0;
	m_timestamp = 0;
	m_randId    = dSeed * 1000000000;
 
	SetHostId();
	SetProcessId();
	SetTimestamp();
	SetRandId();
}

//##ModelId=39783984032B
CUniqueId::CUniqueId(std::string sUid)
{
	if ( !SetUid(sUid) ) {
		m_hostId    = 0;
		m_processId = 0;
		m_timestamp = 0;
		m_randId    = 0;
	}
}

//##ModelId=397839840317
int CUniqueId::GetHostId() {
	return m_hostId;
}

//##ModelId=39783984030E
std::string CUniqueId::GetHostIdAsString() {
	std::string sHostId("");

	if (m_hostId != 0)
	{
		struct in_addr addr;
		addr.S_un.S_addr = m_hostId;
		sHostId = inet_ntoa(addr);
	}

	return sHostId;
}

//##ModelId=39783984030D
int CUniqueId::GetProcessId() {
	return m_processId;
}

//##ModelId=397839840303
std::string CUniqueId::GetProcessIdAsString() {
	char buffer[20];

	if (m_processId != 0)
	{
		_itoa_s( m_processId, buffer, 10 );
		std::string sProcessId(buffer);

		return sProcessId;
	}
	return "";
}

//##ModelId=3978398402FA
int CUniqueId::GetTimestamp() {
	return m_timestamp;
}

//##ModelId=3978398402F9
std::string CUniqueId::GetTimestampAsString() {
	std::string sTimestamp("");

	if (m_timestamp != 0)
	{
		// Convert time to struct in UTC
		time_t aclock = (time_t)m_timestamp;
		struct tm *gmt = gmtime( &aclock );

		// Convert to Format like "Sun May 01 20:27:01 1994"
		sTimestamp = asctime( gmt );
	}

	return sTimestamp;
}

//##ModelId=3978398402F0
int CUniqueId::GetRandId() {
	return m_randId;
}

//##ModelId=3978398402EF
std::string CUniqueId::GetRandIdAsString() {
	char buffer[20];

	if (m_randId != 0)
	{
		_itoa( m_randId, buffer, 10 );
		std::string sRandId(buffer);

		return sRandId;
	}
	return "";
}

// produce Unique-ID:
// "123456789012 12345 1234567890 1234567890"
//  host-id      pid   time       rand

//##ModelId=3978398402DD
std::string CUniqueId::GetUid()
{
	char buffer[64];

	_itoa( m_hostId, buffer, 10 );
	std::string sHostId(buffer);
	while ( sHostId.length() < 12 )
		sHostId = "0" + sHostId;

	_itoa( m_processId, buffer, 10 );
	std::string sProcessId(buffer);
	while ( sProcessId.length() < 5 )
		sProcessId = "0" + sProcessId;

	_itoa( m_timestamp, buffer, 10 );
	std::string sTimestamp(buffer);
	while ( sTimestamp.length() < 10 )
		sTimestamp = "0" + sTimestamp;

	_itoa( m_randId, buffer, 10 );
	std::string sRandId(buffer);
	while ( sRandId.length() < 10 )
		sRandId = "0" + sRandId;

	return sHostId + sProcessId + sTimestamp + sRandId;
}

//##ModelId=3978398402DB
bool CUniqueId::SetUid(std::string sUid)
{
	if ( sUid.length() < 32 )
		return false;

	std::string sHostId    = sUid.substr(0,12);
	while ( sHostId.at(0) == '0' )
		sHostId.erase(0,1);
	m_hostId = atol(sHostId.c_str());

	std::string sProcessId = sUid.substr(12,5);
	while ( sProcessId.at(0) == '0' )
		sProcessId.erase(0,1);
	m_processId = atol(sProcessId.c_str());

	std::string sTimestamp = sUid.substr(17,10);
	while ( sTimestamp.at(0) == '0' )
		sTimestamp.erase(0,1);
	m_timestamp = atol(sTimestamp.c_str());

	std::string sRandId    = sUid.substr(27,10);
	while ( sRandId.at(0) == '0' )
		sRandId.erase(0,1);
	m_randId = atol(sRandId.c_str());

	return true;
}

//##ModelId=3978398402E5
std::string CUniqueId::CreateId() {
	if (!SetTimestamp())
		return "";

	if (!SetRandId())
		return "";

	return GetUid();
}

//##ModelId=3978398402D1
bool CUniqueId::SetHostId() {
    char ac[80];
    WSAData wsaData;
	struct hostent* phe = NULL;
	struct in_addr addr;

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
		return false;

    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR)
		return false;

    if ((phe = gethostbyname(ac)) == 0)
		return false;

    memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	m_hostId = inet_addr(inet_ntoa(addr));

	WSACleanup();

	return true;
}

//##ModelId=3978398402C8
bool CUniqueId::SetProcessId() {
	m_processId = getpid();
	return true;
}

//##ModelId=3978398402C7
bool CUniqueId::SetTimestamp() {
	time_t aclock;

	// Get time in seconds 
	time( &aclock );
	m_timestamp = aclock;

	return true;
}

//##ModelId=3978398402BE
bool CUniqueId::SetRandId()
{
	// generate a random number
	m_randId = m_randId-1;
	if ( m_randId == 0 )
		m_randId = 1000000000;

	return true;
}

// generates a random double uniformly distributed from 0.0 to 1.0
//##ModelId=3978398402BD
double CUniqueId::Unif()
{
	// not used
	return 0.0;
}

} // namespace

