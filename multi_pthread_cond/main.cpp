#include <iostream>
#include "test_thread.hpp"
#include "cond_mutx.h"
#include "mutex_def.h"
#include <unistd.h>
#include <vector>
#include "LibStdCout.h"

using namespace std;
using namespace MUTX_DEF;

int main()
{
    struct GData gData;
    gData.m_pConVar = new ConVar(&gData.mutexItem);
    
    ProduceThread* produceNode = new ProduceThread();
    std::cout << "produce obj addr: " <<  produceNode << std::endl;
    produceNode->SetMutx(&gData.mutexItem);
    produceNode->SetCondVar(gData.m_pConVar);
    produceNode->SetQue(&gData.dequeItem);

    std::vector<ConsumeThread*> vConSum;
    int n = 3;
    for (int i = 0; i < n; i++)
    {
        ConsumeThread* pConsumeNode = new ConsumeThread();
        std::cout << "consumer obj addr: " << pConsumeNode << std::endl;
        pConsumeNode->SetMutx(&gData.mutexItem);
        pConsumeNode->SetCondVar(gData.m_pConVar);
        pConsumeNode->SetQue(&gData.dequeItem);

        vConSum.push_back(pConsumeNode);
    }

    for (int i = 0; i < n; ++i)
    {
        vConSum[i]->StartThread();
    }
    sleep(3);
    DEBUG_LOG("start produce thread");
    //
    produceNode->StartThread();
    
    produceNode->Join();
    for (int i = 0; i < 3; ++i)
    {
        vConSum[i]->Join();
    }
    return 0;
}
