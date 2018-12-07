#include "Processor_Node.h"

namespace loss
{

MsgProcess::MsgProcess(const ProcessorNode& processor)
{
    m_retAddr   = processor.GetAddr();
    m_origAddr  = m_retAddr;
    m_enChainType = processor.GetChainType();
}

MsgProcess::~MsgProcess()
{
}

short MsgProcess::PopAddr()
{
    if (m_retAddr.empty())
    {
        return 0;
    }

    short index = m_retAddr.back();
    m_retAddr.pop_back();
    return index;
}

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
ProcessorNode::ProcessorNode( const std::string& nodeName, CHain_Type type )
    :m_sProcNodeName(nodeName), m_enChainType(type)
{
}

ProcessorNode::~ProcessorNode()
{
}

const std::vector<short>& ProcessorNode::GetAddr() const
{
    return this->m_uiAddr;
}

CHain_Type  ProcessorNode::GetChainType()
{
    return this->m_enChainType;
}

void ProcessorNode::PushAddr(short iIndex) 
{
    m_uiAddr.push_back(iIndex);
}

void ProcessorNode::CleanVecAddr()
{
    m_uiAddr.clear();
}

}
