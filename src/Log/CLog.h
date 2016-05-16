#ifndef _LOG_H_
#define _LOG_H_

class CLog
{
public:
	void write(const char* format, ...);
};

extern CLog g_Log;

#endif //_LOG_H_