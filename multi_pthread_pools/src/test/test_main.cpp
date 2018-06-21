#include <iostream>
#include <atomic>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include "ThreadManager.h"
#include <sys/time.h>
#include "PosixThreadFactory.h"


using namespace std;
using namespace THREAD_POOLS;

static std::atomic<int> m_atomicIndex(0);

static int64_t GetTimeCurMs()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec/1000);
}

class TestTask: public Runnable 
{
 public:
  TestTask(int iIndex): m_iIndex(iIndex) {}
  virtual void run();
  int GetIndex() const { return m_iIndex; }
  void SetThreadManager(ThreadManager* threadManager) 
  {
      m_pthreadManager = threadManager;
  }
 private:
  int m_iIndex;
  ThreadManager* m_pthreadManager;

};

class Test
{
 public:
  Test(int iThreadums = 10);
  virtual ~Test() {}

  void DispatchTask();
  int GetTotalTaskCount() 
  {
      return m_pThreadManager->pendingTaskCount();
  }
  void StopAllTask()
  {
      m_pThreadManager->stop();
  }
 private:
  void StartThreads();
  
  shared_ptr<ThreadManager> m_pThreadManager;
  int m_iThreadNums;
};

Test::Test(int iThreadums): m_iThreadNums(iThreadums)
{
    if (!m_pThreadManager)
    {
        StartThreads();
    }
}

void Test::StartThreads()
{
    try
    {
        m_pThreadManager = ThreadManager::newSimpleThreadManager(m_iThreadNums);
        std::shared_ptr<PosixThreadFactory> oneThreadFactory = std::shared_ptr<PosixThreadFactory>(
            new PosixThreadFactory());
        if (!oneThreadFactory)
        {
            return ;
        }
        m_pThreadManager->threadFactory(oneThreadFactory);
        m_pThreadManager->start();
    } 
    catch (std::exception& ex)
    {
        std::cout << "catch err, msg: " << ex.what() << std::endl;
        exit(1);
    }

    std::cout << __FUNCTION__<< "()" << std::endl;
    std::cout << "thread nums: " << m_iThreadNums << ", all threads started " << std::endl;
    sleep(1);
}

void Test::DispatchTask()
{
    std::cout << "call func: " << __FUNCTION__ << std::endl;
    int iTotalNums = 30;
    for (int iTaskNums = 0; iTaskNums < iTotalNums; ++iTaskNums)
    {
        std::shared_ptr<TestTask> task = std::shared_ptr<TestTask>(new TestTask( iTaskNums ));
        m_pThreadManager->add(task, 0LL, 0LL);
        task->SetThreadManager(m_pThreadManager.get());
    }
    std::cout << "task nums: " << iTotalNums << " , add all task, cur time: " << GetTimeCurMs() << std::endl;
}

//
void TestTask::run()
{
    m_atomicIndex ++;
    std::cout << "index nums: " << m_atomicIndex 
              << ", cur content: " << GetIndex()
              << ", cur thread id: " << thread()->get_current() 
              << ", has surplus task nums: " << m_pthreadManager->pendingTaskCount()
              << ", cur time: " << GetTimeCurMs() << std::endl;
    sleep(1);
}

///////////////////////////////////////////////////////////////////////
int main()
{
    setbuf(stdout,NULL);
    Test test;
    test.DispatchTask();
    usleep(100);
    std::cout << "begin to stop all stop" << std::endl;
    test.StopAllTask();

    sleep(3);
    std::cout << "at last task nums: " << test.GetTotalTaskCount() << std::endl;
    return 0;
}

