#include <iostream>
#include <string.h>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include "TimerManager.h"
#include "PlatformThreadFactory.h"
using namespace std;
using namespace THREAD_POOLS;

class TimerTask: public Runnable
{
 public:
  TimerTask(std::shared_ptr<TimerManager> tmrmgr, int64_t iTmout);
  virtual ~TimerTask() {}
  virtual void run();

 private:
  std::shared_ptr<TimerManager> p_tmrManager;
  int64_t m_i64Tmout;
  char m_sBuf[10240];
};

TimerTask::TimerTask(std::shared_ptr<TimerManager> tmrmgr, int64_t iTmout)
    :p_tmrManager(tmrmgr), m_i64Tmout(iTmout)
{
    memset(m_sBuf,'\0', sizeof(m_sBuf));
}

void TimerTask::run()
{
    std::cout << "cur thread id: " << thread()->get_current() 
        << ",cur obj addr: " <<hex << this << dec
        << ", timer run time: " << time(NULL) <<  std::endl;
    if (p_tmrManager)
    {
        //do busi logic....
        //
        //if want to timer again, add new timer again.
        std::shared_ptr<Runnable> oneTimerTask = std::shared_ptr<TimerTask>(
            new TimerTask(p_tmrManager, m_i64Tmout));
        std::cout << "new timer addr : " << hex << oneTimerTask.get() << dec << std::endl;
        p_tmrManager->add(oneTimerTask, m_i64Tmout);
    }
}

class TimerTest
{
 public:
  TimerTest(); 
  virtual ~TimerTest() {}

  void TestRun();
 private:
  void StartTimer();

 private:
  std::shared_ptr<TimerManager> m_pTmrManager;
};

TimerTest::TimerTest()
{
    if (!m_pTmrManager)
    {
        StartTimer();
    }
}

void TimerTest::StartTimer()
{
    m_pTmrManager = std::shared_ptr<TimerManager>(new TimerManager());
    m_pTmrManager->threadFactory( 
        std::shared_ptr<PlatformThreadFactory>(new PlatformThreadFactory()) );

    m_pTmrManager->start();
    std::cout << "Now Tm: " << time(NULL) << ", start timer ....." << std::endl;
    
    if (m_pTmrManager->state() == TimerManager::STARTED)
    {
        std::cout << "timer mgr state is started" << std::endl;
    }
}

void TimerTest::TestRun()
{
    if (!m_pTmrManager)
    {
        return ;
    }
    int64_t i64TmoutMs = 1000LL;

    std::shared_ptr<Runnable> oneTimerTask = std::shared_ptr<TimerTask>(
                            new TimerTask(m_pTmrManager, i64TmoutMs));
    std::cout << "cur thread id: " << pthread_self() 
        << ", first timer addr: " << hex << oneTimerTask.get() << dec
        << ", add timer task tm: " << time(NULL) << std::endl;
    m_pTmrManager->add(oneTimerTask, i64TmoutMs);
}

///
int main()
{
    TimerTest oneTimerMgr;
    oneTimerMgr.TestRun();
    
    std::cout << __FUNCTION__ << std::endl;
    sleep(-1);
    return 0;
}
