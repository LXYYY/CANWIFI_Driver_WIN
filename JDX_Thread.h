#ifndef JDX_THREAD_H
#define JDX_THREAD_H
#include <iostream>
#include <string>

#define WIN
#ifndef WIN
    #define LINUX
#endif

#ifdef WIN
    #include "windows.h"
#endif
#ifdef LINUX
    #include "pthread.h"
#endif

class JDX_Thread
{
public:
    JDX_Thread(const std::string threadName="default");
    ~JDX_Thread();

    virtual void run()=0;
    bool start(bool bSuspended);

    void join(int timeout=-1);
    void resume();
    void suspend();
    bool terminate(unsigned long exitCode);

    unsigned int getThreadID();
    std::string getThreadName();
    void setThreadName(std::string threadName);

private:
    bool createThread(bool bSuspended=false);

protected:
    std::string m_threadName;
    unsigned int m_threadID;
    volatile bool m_bRun;

#ifdef WIN
private:
    static unsigned int WINAPI staticThreadFunc(void* arg);

protected:
    HANDLE m_handle;

#endif

#ifdef LINUX
private:

protected:

#endif
};

#endif // JDX_THREAD_H
