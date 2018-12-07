#ifndef _PROCESSOR_NODE_H_
#define _PROCESSOR_NODE_H_

/**
 * @file: Processor_Node.h
 * @brief:  文件定义责任链上节点信息,包括节点和节点处理的msg
 * @author:  wusheng Hu
 * @version: v0x0001
 * @date: 2018-12-07
 */

#include <string>
#include <vector>
namespace loss
{

typedef enum 
{
    NO_TYPE         = 0, //init status 
    CHAIN_TYPE_ONE  = 1, //eg: first type of chain type
    CHAIN_TYPE_TWO  = 2, //eg: second type of chain type
    //... other type
} CHain_Type;

typedef enum 
{
    CONTINUE_GO_ON  = 0, //move onto next chain node 
    SKIP_THIS_CHAIN = 1, //skip all nodes on this chain 
    SKIP_ALL_CHAIN  = 2, //skip all nodes on all  chains

    //...other node process ret
} Chain_Node_Proc_Ret;

//定义责任链上节点 处理信息

class ProcessorNode;
class MsgProcess
{
 public:
  MsgProcess(const ProcessorNode& processor);
  virtual ~MsgProcess();
  virtual bool doMsg() = 0; 

  /**
   * @brief: PopAddr, 用于保存链节点的上下文，方便跳转执行链上源节点
   *
   * @return: 上下文切换前的链上节点索引 
   */
  short PopAddr();
  //other method ....

 private:
  std::vector<short> m_retAddr;
  std::vector<short> m_origAddr;
  CHain_Type m_enChainType;
};

/**
 * @brief: 定义chain上节点
 */

class ProcessorNode 
{
 public:
  ProcessorNode( const std::string& nodeName, CHain_Type type = NO_TYPE );
  virtual ~ProcessorNode();

  virtual Chain_Node_Proc_Ret Process(MsgProcess* msg) = 0;

  inline const std::vector<short>& GetAddr() const;

  inline CHain_Type  GetChainType();
  void PushAddr(short iIndex); 
  std::string GetProcessNodeName() { return m_sProcNodeName; }

  void CleanVecAddr();

 private:
  std::string   m_sProcNodeName;    //定义责任链上节点名字
  CHain_Type    m_enChainType;      //定义责任链节点的类型
  std::vector<short>  m_uiAddr;     //定义责任链上节点存放的位置
};

// 
}
#endif
