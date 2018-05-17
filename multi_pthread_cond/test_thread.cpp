#include <iostream>
#include <unistd.h>
#include "test_thread.hpp"

//======================= produce thread;
ProduceThread::ProduceThread()
{
}

ProduceThread::~ProduceThread()
{
}

bool ProduceThread::StartThread()
{
    std::cout << "PP: start thread addr: " << this << std::endl;
    m_Thread = std::thread(&ProduceThread::ThreadWork, this);
    return true;
}

void ProduceThread::ThreadWork()
{
    std::cout << "thread id: " << std::this_thread::get_id()
        << ", thread func proc obj addr: " << this << std::endl;
    while(1)
    {
        ThreadWorkInner();
    }
}

void ProduceThread::Join()
{
    m_Thread.join();
}

void ProduceThread::SetMutx(Def_Mutex* pMutx)
{
    ThreadCondVar<ProduceThread>::SetMutx(pMutx);
}

void ProduceThread::SetCondVar(ConVar *pConnVar)
{
    ThreadCondVar<ProduceThread>::SetCondVar(pConnVar);
}

void ProduceThread::SetQue(std::deque<int>* pMQ)
{
    m_pQueMsg = pMQ;
}

bool ProduceThread::WaitCondIsOk()
{
    return true;
}
void ProduceThread::ThreadGoOnWork()
{
    return ;
}
void ProduceThread::ThreadWorkInner()
{
    std::cout << "produce thread work, begin to send notify" <<  std::endl;
    //ThreadCondVar<TestThreadBase*>::ThreadNotify();
    ThreadCondVar<ProduceThread>::ThreadNotify();
    std::cout << "produce thread work, send notify succ" <<  std::endl;
    sleep(1);
    return ;
}

void ProduceThread::SetReadCondOkNotify()
{
    static int iStaticNum = 0;
    std::cout << "begin to send data to que, num: " << iStaticNum << std::endl;
    m_pQueMsg->push_front(iStaticNum++);
}

/// =================== consumer pthread implement =================== /////
ConsumeThread::ConsumeThread()
{
}

ConsumeThread::~ConsumeThread()
{

}

bool ConsumeThread::StartThread()
{
    std::cout << "CC: start thread addr: " << this << std::endl;
    m_Thread = std::thread(&ConsumeThread::ThreadWork, this);
    return true;
}

void ConsumeThread::ThreadWork()
{
    std::cout << "thread id: " << std::this_thread::get_id()
        << ", thread func proc obj addr: " << this << std::endl;
    while(1)
    {
        ThreadWorkInner();
    }
}
void ConsumeThread::Join()
{
    m_Thread.join();
}

void ConsumeThread::SetMutx(Def_Mutex* pMutx)
{
    ThreadCondVar<ConsumeThread>::SetMutx(pMutx);
}

void ConsumeThread::SetCondVar(ConVar *pConnVar)
{
    ThreadCondVar<ConsumeThread>::SetCondVar(pConnVar);
}

void ConsumeThread::SetQue(std::deque<int>* pMQ)
{
    m_pQueMsg = pMQ;
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
    int sz = m_pQueMsg->size();
    m_pQueMsg->pop_back();
    std::cout << "queue size: " << sz << ", get node from queue tail, node: " << m_IX << std::endl;
}
void ConsumeThread::ThreadWorkInner()
{
    ThreadWait();
    ConsumWork();
    sleep(10);
    std::cout  << " consume sleep 10 " << std::endl;

}

void  ConsumeThread::ConsumWork()
{
    std::cout << "thread id: " << GetThreadId() << ", x: " << m_IX << std::endl;
}
