/**
 * @file: cond_mutx.h
 * @brief: 
 *
 * @author:  wusheng Hu
 * @version: v0x01
 * @date: 2018-05-14
 */

#ifndef _COND_VAR_DEF_H_
#define _COND_VAR_DEF_H_

namespace MUTX_DEF
{
    class Def_Mutex;
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
      ConVar& operator (const ConVar& cond)
      {
          return *this;
      }

     private:
      std::condition_variable  m_cV;
      Def_Mutex* const m_pMu;
    };

    //--------------------------------------------//
    //--------------------------------------------//
    template<typename T>
    class ThreadCondVar
    {
     public:
      ThreadCondVar(const T* pThread);
      virtual ~ThreadCondVar();

      void ThreadWait();

     protected:
      Def_Mutex m_Mutx;
      ConVar m_ConVar;
      T* m_pThread;
    };

    //------------ implement ----------------//
    template<typename T>
    ThreadCondVar<T>::ThreadCondVar(const T* pThread) :m_pThread(pThread)
    {
        assert(pThread != NULL);
        m_ConVar(&m_Mutx);
    }
    
    template<typename T>
    ThreadCondVar<T>::ThreadCondVar()
    {
        pThread = NULL;
    }
    
    template<typename T>
    void ThreadCondVar<T>::ThreadWait()
    {
        m_Mutx.Lock();
        while( !m_pThread->WaitCondIsOk() )
        {
            m_ConVar.Wait();
        }
        m_Mutx.UnLock();
    }

    template<typename T>
    void ThreadNotify() 
    {
        m_Mutx.Lock();
        m_pThread->SetReadCondOkNotify();
        m_ConVar.Signal();
        m_Mutx.UnLock();
    }

}
#endif
