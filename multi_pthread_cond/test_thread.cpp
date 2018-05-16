#include <iostream>
#include <unistd.h>
#include "test_thread.hpp"

TestThreadBase::TestThreadBase(Def_Mutex* pMutx , ThreadCondVar<TestThreadBase>* pConnVar, 
                               std::deque<int>* pMQ)
    :m_pMutx(pMutx), m_pThreadConVar(pConnVar), m_pQueMsg(pMQ)
{
    m_pThreadConVar = new ThreadCondVar<TestThreadBase>();
    std::cout << "new thread cond var: " <<  m_pThreadConVar  << std::endl;
}

TestThreadBase::TestThreadBase()
{

}

TestThreadBase::~TestThreadBase()
{
    if (m_pThreadConVar)
    {
        delete m_pThreadConVar;
        m_pThreadConVar = NULL;
    }
}

void TestThreadBase::SetMutx(Def_Mutex* pMutx)
{
    m_pMutx = pMutx;
    m_pThreadConVar->SetMutx(m_pMutx);
    m_pThreadConVar->SetThread(this);
}

void TestThreadBase::SetConVar(ThreadCondVar<TestThreadBase>* pConVar)
{
    m_pThreadConVar = pConVar;
    m_pThreadConVar->SetThread(this);
}

void TestThreadBase::SetQue(std::deque<int>* pMQ)
{
    m_pQueMsg = pMQ;
    m_pThreadConVar->SetThread(this);
}

//
bool TestThreadBase::StartThread()
{
    m_Thread = std::thread(&TestThreadBase::ThreadWork,this);
    return true;
}

void TestThreadBase::ThreadWork()
{
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;
    while(1)
    {
        ThreadWorkInner();
    }
}

void TestThreadBase::Join()
{
    m_Thread.join();
}

//======================= produce thread;
ProduceThread::ProduceThread(Def_Mutex* pMutx, ThreadCondVar<TestThreadBase>* pConnVar, std::deque<int>* pMQ)
    :TestThreadBase(pMutx, pConnVar, pMQ)
{
}
ProduceThread::ProduceThread()
{
}

ProduceThread::~ProduceThread()
{
}

void ProduceThread::ThreadWorkInner()
{
    std::cout << "produce thread work, begin to send notify" <<  std::endl;
    m_pThreadConVar->ThreadNotify();
    std::cout << "produce thread work, send notify succ" <<  std::endl;
    sleep(2);
}

void ProduceThread::SetReadCondOkNotify()
{
    static int iStaticNum = 0;
    std::cout << "begin to send data to que, num: " << iStaticNum << std::endl;
    m_pQueMsg->push_front(iStaticNum++);
}

/// =================== consumer pthread implement =================== /////
ConsumeThread::ConsumeThread(Def_Mutex* pMutx, ThreadCondVar<TestThreadBase>* pConnVar, std::deque<int>* pMQ)
    :TestThreadBase(pMutx, pConnVar, pMQ), m_IX(0)
{
}

ConsumeThread::ConsumeThread()
{
}

ConsumeThread::~ConsumeThread()
{
}

bool ConsumeThread::WaitCondIsOk()
{
    if (m_pQueMsg->empty())
    {
        std::cout << "thread id: " << std::this_thread::get_id() << ", queue is empty" << std::endl;
        return true;
    }

    std::cout << "thread id: " << std::this_thread::get_id() << ", queue has node " << std::endl;
    return false;
}

void ConsumeThread::ThreadGoOnWork()
{
    if (m_pQueMsg->empty())
    {
        std::cout << "queue is empty" << std::endl;
        return ;
    }
    m_IX = m_pQueMsg->back();
    m_pQueMsg->pop_back();
    std::cout << "get node from queue tail, node: " << m_IX << std::endl;
}
void ConsumeThread::ThreadWorkInner()
{
    m_pThreadConVar->ThreadWait();
    ConsumWork();
    sleep(1);
    std::cout  << " consume sleep 1 " << std::endl;

}

void  ConsumeThread::ConsumWork()
{
    std::cout << "thread id: " << GetThreadId() << ", x: " << m_IX << std::endl;
}
