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

void ProduceThread::ThreadWorkInner()
{
    std::cout << "produce thread work, begin to send notify" <<  std::endl;
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
