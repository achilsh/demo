#include <iostream>
#include "test_thread.hpp"
#include "cond_mutx.h"
#include "mutex_def.h"
#include <unistd.h>
#include <vector>

using namespace std;
using namespace MUTX_DEF;

int main()
{
    struct GData gData;
    
    ProduceThread* produceNode = new ProduceThread();
    produceNode->SetConVar(&gData.condVarItem);
    produceNode->SetMutx(&gData.mutexItem);
    produceNode->SetQue(&gData.dequeItem);

    std::vector<TestThreadBase*> vConSum;
    for (int i = 0; i < 3; i ++)
    {
        ConsumeThread* pConsumeNode = new ConsumeThread();

        pConsumeNode->SetConVar(&gData.condVarItem);
        pConsumeNode->SetMutx(&gData.mutexItem);
        pConsumeNode->SetQue(&gData.dequeItem);

        vConSum.push_back(pConsumeNode);
    }

    for (int i = 0; i < 3; ++i)
    {
        vConSum[i]->StartThread();
    }
    sleep(3);
    std::cout << "main(): start produce thread" <<  std::endl;
    //
    produceNode->StartThread();
    produceNode->Join();
    
    for (int i = 0; i < 3; ++i)
    {
        vConSum[i]->Join();
    }
    return 0;
}
