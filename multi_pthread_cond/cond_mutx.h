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

    //--------------------------------------------//
    // T must implement interface: WaitCondIsOk(),
    // ThreadGoOnWork();
    // SetReadCondOkNotify();
    //--------------------------------------------//
    template<typename T>
    class ThreadCondVar
    {
     public:
      ThreadCondVar(const T* pThread = NULL, const Def_Mutex* pMutex = NULL);
      virtual ~ThreadCondVar();
      void SetThread(T* pThread);
      void SetMutx(Def_Mutex* pMutex);

      void ThreadWait();
      void ThreadNotify();
     protected:
      Def_Mutex* m_pMutx;
      ConVar *m_pConVar;
      T* m_pThread;
    };

    //------------ implement ----------------//
    template<typename T>
    ThreadCondVar<T>::ThreadCondVar(const T* pThread, const Def_Mutex *pMutx) 
    {
        //m_ConVar(m_pMutx);
    }
    
    template<typename T>
    ThreadCondVar<T>::~ThreadCondVar()
    {
        m_pThread = NULL;
        m_pMutx = NULL;
        if (m_pConVar)
        {
            delete m_pConVar;
            m_pConVar = NULL;
        }
    }
   
    template<typename T>
    void ThreadCondVar<T>::SetThread(T* pThread)
    {
        m_pThread = pThread;
    }

    template<typename T>
    void ThreadCondVar<T>::SetMutx(Def_Mutex* pMutex)
    {
        m_pMutx = pMutex;
        if (m_pConVar == NULL)
        {
            m_pConVar = new ConVar(m_pMutx);
        }
    }

    template<typename T>
    void ThreadCondVar<T>::ThreadWait()
    {
        m_pMutx->Lock();
        while( m_pThread->WaitCondIsOk() )
        {
            std::cout << "thread id: " << std::this_thread::get_id() << ", enter to wait status" << std::endl;
            m_pConVar->Wait();
            std::cout << "thread id: " << std::this_thread::get_id() << ", thread is awake now " << std::endl;
        }
        m_pThread->ThreadGoOnWork();
        m_pMutx->UnLock();
    }

    template<typename T>
    void ThreadCondVar<T>::ThreadNotify() 
    {
        m_pMutx->Lock();
        std::cout << "thread id: " << std::this_thread::get_id() << ", begin send notify: ====> " << std::endl;
        m_pThread->SetReadCondOkNotify();
        m_pConVar->Signal();
        //m_pConVar->SignalAll();
        std::cout << "thread id: " << std::this_thread::get_id() << ", end send notify: ====> " << std::endl;
        m_pMutx->UnLock();
    }
}
#endif
