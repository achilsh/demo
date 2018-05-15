#ifndef _EXPAND_DERVIE_INTERFACE_H_
#define _EXPAND_DERVIE_INTERFACE_H_
/**
 * @file: crtp_expand_derive_interface.h
 * @brief: 添加子类接口，其中子类是基类的模板参数. 完成模板参数具有模板的接口.
 *         实现方式就是: 模板参数的实例继承模板
 *
 * @author:  wusheng Hu
 * @version: v0x0001
 * @date: 2018-05-15
 */

#ifdef __cplusplus 
    extern "C" {
#endif 

    #include <pthread.h>
    #include <stdlib.h>

#ifdef __cplusplus 
    }
#endif

template<typename T>
class CSingleton
{
 public:
  static T* Instance()  //concrete deriver want to reuse this interface.
  {
      if (!m_pInstance) 
      {
          pthread_mutex_lock(&m_mutex);
          if (!m_pInstance)
          {
              if (m_Destoryed)
              {
                  onDeadReference();
              } 
              else 
              {
                  CreateInstance();
              }
          }
          pthread_mutex_unlock(&m_mutex);
      }
      return m_pInstance;
  }

 private:
  static T* volatile m_pInstance; 
  static pthread_mutex_t m_mutex;
  static bool m_Destoryed;

 private:
  CSingleton() {}
  CSingleton(const CSingleton&) 
  {
  }
  CSingleton& operator =(const  CSingleton&)
  {
    return *this;
  }
  ~CSingleton() 
  {
      m_pInstance = NULL;
      m_Destoryed = true;
  }

  friend T;
  
  static void CreateInstance() 
  {
      static T sInstance;
      m_pInstance = &sInstance;
  }

  static void onDeadReference() 
  {
      CreateInstance();
      new (m_pInstance) T;
      atexit(ExitInstance);
      m_Destoryed = false;
  }
  static void ExitInstance() 
  {
      m_pInstance->~T();
  }
  //
};


/*** implement of interface ******/
template<typename T>
T* volatile CSingleton<T>::m_pInstance = NULL;

template<typename T>
pthread_mutex_t CSingleton<T>::m_mutex = PTHREAD_MUTEX_INITIALIZER;

template<typename T>
bool CSingleton<T>::m_Destoryed = false;

//define active single class 
#include "deriver_interface.h"

#endif
