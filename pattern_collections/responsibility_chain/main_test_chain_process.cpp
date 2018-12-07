#include "Chain_Processor.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace loss;

class Msg:public MsgProcess
{
 public:
  Msg( const ProcessorNode& processor, const std::string& msgVal,int x )
      :MsgProcess(processor), m_sMsg(msgVal),m_ix(x)
  {  }
  virtual ~Msg() {  }
  virtual bool doMsg()
  {
      if ( m_ix == 0 )
      {
          std::cout << m_ix << __LINE__ << ", con'd" << std::endl;
          m_ix ++;
      }
      else if ( m_ix == 1 )
      {
          std::cout << m_ix << __LINE__ << ", con'd" << std::endl;
          m_ix++;
      }
      else 
      {
          return false;
      }
      return true;
  }

 private:
  std::string m_sMsg;
  int m_ix;
};

class TestProcess: public ProcessorNode
{
 public:
  TestProcess(const std::string& nodeName, int x):ProcessorNode(nodeName), m_xval(x)
  {  }
  TestProcess::~TestProcess()
  {  }

  virtual Chain_Node_Proc_Ret 
  TestProcess::Process(MsgProcess* msg)
  {
      std::cout << "process node: " << this->GetProcessNodeName() << std::endl; 
      if ((dynamic_cast<Msg*>(msg))->doMsg() )
      {
          return CONTINUE_GO_ON;
      }
      else
      {
          return SKIP_THIS_CHAIN;
      }
  }
 private:
  int m_xval;
};

class TestYProcess: public ProcessorNode
{
 public:
  TestYProcess(const std::string& nodeName, float x):ProcessorNode(nodeName), m_xval(x)
  {  }
  TestYProcess::~TestYProcess()
  {  }

  virtual Chain_Node_Proc_Ret 
  TestYProcess::Process(MsgProcess* msg)
  {
      if ((dynamic_cast<Msg*>(msg))->doMsg() )
      {
          return CONTINUE_GO_ON;
      }
      else
      {
          return SKIP_THIS_CHAIN;
      }
  }
 private:
  float m_xval;
};


int main()
{
    std:shared_ptr<ChainProcessor> chain_process = std::make_shared<ChainProcessor>(CHAIN_TYPE_ONE);
        
    std::shared_ptr<ProcessorNode> proces_node_x = std::make_shared<TestProcess>("TestProcess", 100);
    std::shared_ptr<ProcessorNode> proces_node_y = std::make_shared<TestYProcess>("TestYProcess", 100);
    
    chain_process->AddProcessNode(proces_node_x);
    chain_process->AddProcessNode(proces_node_y);

    Msg msg_val(*proces_node_x.get(), "msy_val", 0);

    while ( true )
    {
       Chain_Node_Proc_Ret ret =  chain_process->Process(&msg_val);
       if ( ret != CONTINUE_GO_ON )
       {
            break;
       }

       std::cout << "go on continue" << std::endl;
       sleep(1);
    }

    return 0;
}
