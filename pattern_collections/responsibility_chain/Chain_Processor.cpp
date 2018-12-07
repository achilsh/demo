#include "Chain_Processor.h"

namespace loss
{

ChainProcessor::ChainProcessor(CHain_Type chainType)
    :m_isReady(false), m_chainType(chainType)
{
}

ChainProcessor::~ChainProcessor()
{
    m_vProcessNodes.clear();
}


Chain_Node_Proc_Ret ChainProcessor::Process( MsgProcess* msg )
{
    if (!m_isReady)
    {
        OnChainComplete();
    }

    Chain_Node_Proc_Ret  ret;
    unsigned int uiPos = 0;
    uiPos = msg->PopAddr();

    for (; (uiPos >= 0 && uiPos < m_vProcessNodes.size()); ++ uiPos)
    {
        ret = m_vProcessNodes[uiPos]->Process(msg);
        if ( ret == SKIP_ALL_CHAIN )
        {
            return  ret;
        }
        else if ( ret == SKIP_THIS_CHAIN )
        {
            return CONTINUE_GO_ON;
        }
    }

    return CONTINUE_GO_ON;
}

void ChainProcessor::AddProcessNode( std::shared_ptr<ProcessorNode> processNode )
{
    if ( m_isReady )
    {
        return ;
    }
    processNode->PushAddr(short(m_vProcessNodes.size()));
    m_vProcessNodes.push_back(processNode);
}

void ChainProcessor::OnChainComplete()
{
    short iIndex = 0;
    for ( auto &one: m_vProcessNodes )
    {
        one->CleanVecAddr();
        one->PushAddr(iIndex++);
    }
    m_isReady = true;
}
/////////////////////////////////////////////////////////////////////////////////////

}
