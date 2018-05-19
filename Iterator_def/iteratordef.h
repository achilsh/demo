#ifndef _ITERATOR_DEF_H_
#define _ITERATOR_DEF_H_
#include <iterator>

template<typename T>
class TestVector 
{
 public:
  TestVector();
  TestVector(int n);
  virtual ~TestVector();
  int Size() const;
  T& operator[] (int i)
  {
      return m_pElement[i];
  }

  class TestIterator: public std::iterator<std::input_iterator_tag, T>
  {
     public:
      TestIterator(T* item): m_pItem(item)
      {
      }
      TestIterator(const TestIterator& iter)
      {
          m_pItem = iter.m_pItem;
      }
      virtual ~TestIterator()
      {
          m_pItem = NULL;
      }

      TestIterator& operator = (const TestIterator& iter);
      bool operator != (const TestIterator& iter);
      bool operator == (const TestIterator& iter);

      TestIterator& operator++ ( ); 
      TestIterator& operator++ (int);

      T& operator*();
     private:
      T* m_pItem;
  };

  TestIterator begin( );
  TestIterator end( );

 private:
  T* m_pElement;
  int m_iSize;
};

///////////////////////////////////////////////
template<typename T>
TestVector<T>::TestVector() :m_pElement(NULL), m_iSize(0)
{
}

template<typename T>
TestVector<T>::TestVector(int n): m_pElement(NULL), m_iSize( n )
{
    m_pElement = new T[m_iSize];
}

template<typename T>
TestVector<T>::~TestVector( )
{
    if (m_pElement)
    {
        delete [] m_pElement;
        m_pElement = NULL;
    }
    m_iSize = 0;
}

template<typename T>
int TestVector<T>::Size() const
{
    return m_iSize;
}

template<typename T>
typename TestVector<T>::TestIterator TestVector<T>::begin()
{
    return TestVector<T>::TestIterator(m_pElement);
}

template<typename T>
typename TestVector<T>::TestIterator TestVector<T>::end( )
{
    return TestVector<T>::TestIterator(m_pElement + m_iSize);
}
////////////////////////////////////////////////////
//-------------------------------------------------/
template<typename T>
typename TestVector<T>::TestIterator&  TestVector<T>::TestIterator::operator = (const TestVector<T>::TestIterator& iter)
{
    if (*this != iter)
    {
        m_pItem = iter.m_pItem;
    }
    return *this;
}

template<typename T>
inline bool TestVector<T>::TestIterator::operator != (const TestVector<T>::TestIterator& iter)
{
    if (m_pItem != iter.m_pItem)
    {
        return true;
    }
    return false;
}

template<typename T>
inline bool TestVector<T>::TestIterator::operator == (const TestVector<T>::TestIterator& iter)
{
    if (iter.m_pItem == m_pItem)
    {
        return true;
    }
    return false;
}

template<typename T>
typename TestVector<T>::TestIterator& TestVector<T>::TestIterator::operator ++ ( )
{
    ++m_pItem;
    return *this;
}

template<typename T>
typename TestVector<T>::TestIterator& TestVector<T>::TestIterator::operator ++ (int)
{
    TestIterator preNode(*this);
    operator++();
    return preNode;
}

template<typename T>
T& TestVector<T>::TestIterator::operator*( )
{
    return *m_pItem;
}

#endif
