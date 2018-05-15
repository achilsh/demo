#ifndef _deriver_interface_h_
#define _deriver_interface_h_

class DeriverTest: public CSingleton<DeriverTest>
{
 public:
  DeriverTest(): m_XVal(0), m_YVal(0) 
  {
  }
  virtual ~DeriverTest() 
  {
  }
  void SetXY(int x, int y)
  {
      SetX(x);
      SetY(y);
  }
  void SetX(int x) 
  {
      m_XVal = x;
  }
  void SetY(int y)
  {
      m_YVal = y;
  }
  int SumFunc()
  {
      return m_XVal + m_YVal;
  }
 private:
  int m_XVal;
  int m_YVal;
};

#endif
