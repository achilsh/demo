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

  Def_Mutex mutexItem;
  std::deque<int> dequeItem;
  ConVar *m_pConVar;
};

#include <thread>

///// =========== produce thread define ======================//
class ProduceThread: public ThreadCondVar<ProduceThread>
{
 public:
  ProduceThread();
  virtual ~ProduceThread();
  void ThreadWorkInner();

  bool StartThread();
  void Join();
  std::thread::id GetThreadId()
  {
    return m_Thread.get_id();
  }

  void SetMutx(Def_Mutex* pMutx);
  void SetCondVar(ConVar *pConnVar);
  void SetQue(std::deque<int>* pMQ);

  bool WaitCondIsOk();

  void ThreadGoOnWork();
  void SetReadCondOkNotify() ;
 public:
 private:
  void ThreadWork();
  std::deque<int>* m_pQueMsg;
  std::thread m_Thread;
};

//// ================ comsume thrad define =========================//
class ConsumeThread: public ThreadCondVar<ConsumeThread>
{
 public:
  ConsumeThread();
  virtual  ~ConsumeThread();

  bool WaitCondIsOk();
  void ThreadGoOnWork();
  void ThreadWorkInner();
  void ConsumWork();

  bool StartThread();
  void Join();
  std::thread::id GetThreadId()
  {
    return m_Thread.get_id();
  }

  void SetMutx(Def_Mutex* pMutx);
  void SetCondVar(ConVar *pConnVar);
  void SetQue(std::deque<int>* pMQ);

  void SetReadCondOkNotify();
 public:

 private:
  int m_IX;
 private:
  void ThreadWork();
  std::deque<int>* m_pQueMsg;
  std::thread m_Thread;
};

#endif
