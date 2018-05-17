#ifndef _COND_VAR_DEF_H_
#define _COND_VAR_DEF_H_

/**
 * @file: cond_mutx.h
 * @brief: 
 *      wrap self-def condtion var with std::condition_variable.
 *
 * @author:  wusheng Hu
 * @version: v0x01
 * @date: 2018-05-14
 */

#include "mutex_def.h"
#include <condition_variable>
#include <thread>
#include <deque>

namespace MUTX_DEF
{
    class ConVar
    {
     public:
      explicit ConVar(Def_Mutex* mu);
      virtual ~ConVar();

      void Wait();
      void Signal();
      void SignalAll();

     private:
      ConVar(const ConVar& cond)
      {
      }
      ConVar& operator = (const ConVar& cond)
      {
          return *this;
      }

     private:
      std::condition_variable  m_cV;
      Def_Mutex* m_pMu;
    };

    class BaseThread
    {
     public:
      BaseThread();
      virtual ~BaseThread();

      bool StartThread();
      void Join();
      std::thread::id GetThreadId()
      {
          return m_Thread.get_id();
      }
      void ThreadWork();
      virtual void ThreadWorkInner() = 0;

      void SetQue(std::deque<int>* pMQ)
      {
          m_pQueMsg = pMQ;
      }
     protected:
      bool WaitCondIsOk() { return false; }  
      void ThreadGoOnWork() {} 
      void SetReadCondOkNotify() {}
     protected:
      std::thread m_Thread;
      std::deque<int>* m_pQueMsg;
    };

    //--------------------------------------------//
    // T must implement interface: WaitCondIsOk(),
    // ThreadGoOnWork();
    // SetReadCondOkNotify();
    //--------------------------------------------//
    template<typename T>
    class ThreadCondVar: public BaseThread
    {
     public:
      virtual ~ThreadCondVar();
      void SetMutx(Def_Mutex* pMutex);
      void SetCondVar(ConVar *pConnVar);

      void ThreadWait();
      void ThreadNotify();
      T& Cast() 
      {
          return static_cast<T&>(*this); 
      }
      bool WaitCondIsOk()
      {
          return false;
      }
      bool ThreadGoOnWork()
      {
          return false;
      }
     protected:
      Def_Mutex* m_pMutx;
      ConVar *m_pConVar;
      friend T;
      ThreadCondVar(): m_pMutx(NULL), m_pConVar(NULL) {}
    };
    

    
    //------------ implement ----------------//
    template<typename T>
    ThreadCondVar<T>::~ThreadCondVar()
    {
        m_pMutx = NULL;
        m_pConVar = NULL;
    }

    template<typename T>
    void ThreadCondVar<T>::SetMutx(Def_Mutex* pMutex)
    {
        m_pMutx = pMutex;
    }

    template<typename T>
    void ThreadCondVar<T>::SetCondVar(ConVar *pConnVar)
    {
        m_pConVar = pConnVar;
    }

    template<typename T>
    void ThreadCondVar<T>::ThreadWait()
    {
        m_pMutx->Lock();
        while( Cast().WaitCondIsOk() )
        {
            std::cout << "thread id: " << std::this_thread::get_id() << ", enter to wait status" << std::endl;
            m_pConVar->Wait();
            std::cout << "thread id: " << std::this_thread::get_id() << ", thread is awake now " << std::endl;
        }
        Cast().ThreadGoOnWork();
        m_pMutx->UnLock();
    }

    template<typename T>
    void ThreadCondVar<T>::ThreadNotify() 
    {
        m_pMutx->Lock();
        std::cout << "thread id: " << std::this_thread::get_id() 
            << ", notify obj addr: " << this << ", begin send notify: ====> " << std::endl;
        //
        Cast().SetReadCondOkNotify();
        //
        m_pConVar->Signal();
        std::cout << "thread id: " << std::this_thread::get_id() << ", end send notify: ====> " << std::endl;
        m_pMutx->UnLock();
    }
}
#endif
