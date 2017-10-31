#include "JDX_Thread.h"

JDX_Thread::JDX_Thread(const std::string threadName)
    :m_threadName(threadName),m_threadID(0),m_bRun(false)
{

}

JDX_Thread::~JDX_Thread()
{
}

bool JDX_Thread::start(bool bSuspended)
{
    m_bRun=createThread(bSuspended);
    return m_bRun;
}

void JDX_Thread::join(int timeout)
{
#ifdef WIN
    if(m_handle&&m_bRun)
    {
        if(timeout<0)
            timeout=INFINITE;

        ::WaitForSingleObject(m_handle,timeout);
    }
#endif
}

void JDX_Thread::resume()
{
#ifdef WIN
    if(m_handle&&m_bRun)
        ::ResumeThread(m_handle);
#endif
}

void JDX_Thread::suspend()
{
#ifdef WIN
    if(m_handle&&m_bRun)
        ::SuspendThread(m_handle);
#endif
}

bool JDX_Thread::terminate(unsigned long exitCode)
{
#ifdef WIN
    if(m_handle&&m_bRun)
    {
        if(::TerminateThread(m_handle,exitCode))
        {
            ::CloseHandle(m_handle);
            m_handle=NULL;
            m_bRun=false;
            return true;
        }
    }
    return false;
#endif
}

unsigned int JDX_Thread::getThreadID()
{
    return m_threadID;
}

std::string JDX_Thread::getThreadName()
{
    return m_threadName;
}

void JDX_Thread::setThreadName(std::string threadName)
{
    m_threadName=threadName;
}

bool JDX_Thread::createThread(bool bSuspended)
{
#ifdef WIN
    if(!m_bRun)
    {
        if(bSuspended)
            m_handle=(HANDLE)_beginthreadex(NULL,0,staticThreadFunc,this,CREATE_SUSPENDED,&m_threadID);
        else
            m_handle=(HANDLE)_beginthreadex(NULL,0,staticThreadFunc,this,0,&m_threadID);
        m_bRun=(m_handle!=NULL);
    }
    return m_bRun;
#endif
}

JDX_THREAD_FUNC JDX_Thread::staticThreadFunc(void *arg)
{
    JDX_Thread* pThread=(JDX_Thread*)arg;
    pThread->run();

    return 0;
}



