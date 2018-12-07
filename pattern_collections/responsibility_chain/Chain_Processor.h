#ifndef _CHAIN_PROCESSOR_H_
#define _CHAIN_PROCESSOR_H_
/**
 * @file: Chain_Processor.h
 * @brief: 定义责任链信息  
 * @author:  wusheng Hu
 * @version: v0x0001
 * @date: 2018-12-07
 */

#include <memory>
#include <vector>
#include "Processor_Node.h"

namespace loss
{

class ChainProcessor
{
 public:
  ChainProcessor(CHain_Type chainType);
  virtual ~ChainProcessor();

  Chain_Node_Proc_Ret Process( MsgProcess* msg );
  void  AddProcessNode( std::shared_ptr<ProcessorNode> processNode );
 private:
  void OnChainComplete();

 private:
  std::vector< std::shared_ptr<ProcessorNode> >  m_vProcessNodes;
  bool          m_isReady;
  CHain_Type    m_chainType;
};

}
#endif
