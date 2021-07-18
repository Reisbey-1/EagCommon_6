#ifndef uniqueid_h
#define uniqueid_h 1

#include <string>
#include <winsock.h>
#include <process.h> // getpid()
#include <time.h>    // time()

namespace eag {

#ifdef UNIQUEID_EXPORTS
#define UNIQUEID_API __declspec(dllexport)
#else
#define UNIQUEID_API __declspec(dllimport)
#endif

//##ModelId=39783984028B
class UNIQUEID_API CUniqueId
{
public:
	//##ModelId=397839840321
	CUniqueId(double dSeed = 1.0);
	//##ModelId=39783984032B
	CUniqueId(std::string sUid);

	//##ModelId=397839840317
	int GetHostId();
	//##ModelId=39783984030E
	std::string GetHostIdAsString();
	//##ModelId=39783984030D
	int GetProcessId();
	//##ModelId=397839840303
	std::string GetProcessIdAsString();
	//##ModelId=3978398402FA
	int GetTimestamp();
	//##ModelId=3978398402F9
	std::string GetTimestampAsString();
	//##ModelId=3978398402F0
	int GetRandId();
	//##ModelId=3978398402EF
	std::string GetRandIdAsString();

	//##ModelId=3978398402E5
	std::string CreateId();
	//##ModelId=3978398402DD
	std::string GetUid();
	//##ModelId=3978398402DB
	bool SetUid(std::string sUid);

private:
	//##ModelId=3978398402D1
	bool SetHostId();
	//##ModelId=3978398402C8
	bool SetProcessId();
	//##ModelId=3978398402C7
	bool SetTimestamp();
	//##ModelId=3978398402BE
	bool SetRandId();

	//##ModelId=3978398402BD
	double Unif();

private:
	//##ModelId=3978398402B3
	long m_hostId;
	//##ModelId=3978398402A9
	long m_processId;
	//##ModelId=3978398402A0
	long m_timestamp;
	//##ModelId=39783984029F
	long m_randId;
};

} // namespace

#endif // ifndef uniqueid_h
