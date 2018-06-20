#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>
#include <list>
#include <set>
#include <vector>
#include <exception>

#define THRIFT_UNUSED_VARIABLE(x) ((void)(x))

namespace THREAD_POOLS
{

class TException : public std::exception 
{
public:
  TException() : message_() {}

  TException(const std::string& message) : message_(message) {}

  virtual ~TException() throw() {}

  virtual const char* what() const throw() {
    if (message_.empty()) {
      return "Default TException.";
    } else {
      return message_.c_str();
    }
  }

protected:
  std::string message_;
};


class TDelayedException {
public:
  template <class E>
  static TDelayedException* delayException(const E& e);
  virtual void throw_it() = 0;
  virtual ~TDelayedException(){};
};

template <class E>
class TExceptionWrapper : public TDelayedException {
public:
  TExceptionWrapper(const E& e) : e_(e) {}
  virtual void throw_it() {
    E temp(e_);
    delete this;
    throw temp;
  }

private:
  E e_;
};

template <class E>
TDelayedException* TDelayedException::delayException(const E& e) {
  return new TExceptionWrapper<E>(e);
}

}
#endif
