#include "crtp_expand_derive_interface.h"
#include <iostream>

using namespace std;

int main()
{
    DeriverTest::Instance()->SetXY(100, 200);
    std::cout << DeriverTest::Instance()->SumFunc() << std::endl;
    return 0;
}
