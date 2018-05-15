#include <iostream>
#include "crtp_static_implemet_dynamic.h"

int main()
{
    Derive *pA = new Derive;
    Base bb(10);

    TempTest::TFunc(*pA);
    TempTest::TFunc(bb);
    // 
    delete pA;
    pA = NULL;
    return 0;
}
