/**
 * @file: mutex_def.h
 * @brief: 
 *    wrap c++11 std::mutex 
 * @author:  wusheng Hu
 * @version: v0x01
 * @date: 2018-05-14
 */

#ifndef _MUTEX_DEF_H_
#define _MUTEX_DEF_H_

namespace  MUTX_DEF 
{
    class ConVar;
    class Def_Mutex
    {
     public:
      Def_Mutex()
      {
      }
      virtual ~Def_Mutex()
      {
      }
      
      void Lock()
      {
          m_Mutex.lock();
      }
      void UnLock()
      {
          m_Mutex.unlock();
      }
     private:
      Def_Mutex(const Def_Mutex& mutx)
      {
      }
      Def_Mutex& operator = (const Def_Mutex& mutx)
      {
          return *this;
      }
     private:
      friend class ConVar;
      std::mutex m_Mutex; //using std::mutex as member.
    };

    /**
     * @brief: 
     *      Helper class that locks a mutex on construction and unlocks the mutex
     *      when the destructor of the MutexLock object is invoked. 
     */
    class MutexLock 
    {
     public:
      explicit MutexLock(Def_Mutex* pMutex): m_pCntMutex( pMutex ) 
      {
          this->m_pCntMutex->Lock();
      }
      virtual ~MutexLock()
      {
          this->m_pCntMutex->UnLock();
      }

     private:
      MutexLock(const MutexLock& mtxLock)
      {
      }
      
      MutexLock& operator = ( const MutexLock& mtxLock )
      {
      }
      
      Def_Mutex* const m_pCntMutex;
    };
}
#endif
