#ifndef _test_thread_hpp_
#define _test_thread_hpp_

/**
 * @file: test_thread.hpp
 * @brief: 
 * @author:  wusheng Hu
 * @version: v0x0001
 * @date: 2018-05-16
 */

#include "mutex_def.h"
#include "cond_mutx.h"
#include <deque>
#include <assert.h>

using namespace  MUTX_DEF;

class TestThreadBase;
struct GData
{
 public:
  GData() {  }
  virtual ~GData() {} 

  ThreadCondVar<TestThreadBase> condVarItem;
  Def_Mutex mutexItem;
  std::deque<int> dequeItem;
};

#include <thread>

class TestThreadBase
{
 public:
  TestThreadBase();
  TestThreadBase( Def_Mutex* pMutx, ThreadCondVar<TestThreadBase>* pConnVar, std::deque<int>* pMQ);
  virtual ~TestThreadBase();
  bool StartThread();
  void Join();
  std::thread::id GetThreadId()
  {
    return m_Thread.get_id();
  }

  void SetMutx(Def_Mutex* pMutx);
  void SetConVar(ThreadCondVar<TestThreadBase>* pConVar);
  void SetQue(std::deque<int>* pMQ);

  virtual bool WaitCondIsOk()
  {
      return true;
  }

  virtual void ThreadGoOnWork()
  {
      return ;
  }

  virtual void SetReadCondOkNotify() = 0;

  virtual void ThreadWorkInner()
  {
      return ;
  }
 protected:
  void ThreadWork();
  Def_Mutex* m_pMutx;
  ThreadCondVar<TestThreadBase>* m_pThreadConVar;
  std::deque<int>* m_pQueMsg;
  std::thread m_Thread;
};

///// =========== produce thread define ======================//
class ProduceThread: public TestThreadBase
{
 public:
  ProduceThread();
  ProduceThread(Def_Mutex* pMutx , ThreadCondVar<TestThreadBase>* pConnVar, std::deque<int>* pMQ );
  virtual ~ProduceThread();
  virtual void ThreadWorkInner();

 public:
  virtual void SetReadCondOkNotify();
};

//// ================ comsume thrad define =========================//
class ConsumeThread: public TestThreadBase
{
 public:
  ConsumeThread();
  ConsumeThread(Def_Mutex* pMutx , ThreadCondVar<TestThreadBase>* pConnVar , std::deque<int>* pMQ );
  virtual  ~ConsumeThread();

  virtual bool WaitCondIsOk();
  virtual void ThreadGoOnWork();
  virtual void ThreadWorkInner();
  virtual void SetReadCondOkNotify() 
  {
  }
  void ConsumWork();
 private:
  int m_IX;
};

#endif
