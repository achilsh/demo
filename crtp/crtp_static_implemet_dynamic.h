#ifndef _crtp_h_
#define _crtp_h_

/**
 * @file: crtp_test.h
 * @brief:  使用模板实现静态多态化.
 *          相对于虚函数表的运行多态，避免了每个类中的虚函数表，
 *          避免了运行时每次都去虚函数表中查找实际调用接口地址，
 *          提升了一定的优化空间.
 *          同时解决不能将基类的虚函数定义为模板的缺陷.
 * @author:  wusheng Hu
 * @version: v0x001
 * @date: 2018-05-15
 */

#include <iostream>
using namespace std;

// 静态多态的实现
//
template<typename T>
class  CrtpBase
{
    public:
     virtual ~CrtpBase()
     {
     }

     void func()
     {
        Cast().Call();
     }
    private:
     void Call()
     {
         std::cout << "base::Call() " << std::endl;
     }
     const T& Cast() const 
     {
         return static_cast<T&>(*this);
     }
     T& Cast() 
     {
         return static_cast<T&>(*this);
     }
    private:
     CrtpBase() {  }
    private:
     friend T;
};

class Base : public CrtpBase<Base> 
{
 public:
  Base(int x) {}
  virtual ~Base() {}

};

class Derive: public CrtpBase<Derive>
{
 public:
  Derive() { }
  virtual ~Derive() {  }
 public: 
  void Call()
  {
      std::cout << "dervie Call() " <<  std::endl;
  }
};


class TempTest 
{
 public:
  TempTest() {} 
  virtual ~TempTest() {}
  
  template<typename T>
  static void TFunc(CrtpBase<T>& op) 
  {
      //实现了静态多态.
       op.func(); 
  }
};
#endif
