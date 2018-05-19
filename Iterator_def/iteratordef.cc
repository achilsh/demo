#include "iteratordef.h"
#include <iostream>
#include <algorithm>

using namespace std;
struct Show 
{
    void operator( ) (int x)
    {
        std::cout << x << std::endl;
    }
};

int main(  )
{
    TestVector<int> aa(10);
    int i = 0;
    for ( TestVector<int>::TestIterator it = aa.begin(); it != aa.end(); ++it, i++)
    {
        *it = i;
    }

   for_each( aa.begin(), aa.end(), Show());
    
    return 0;
}
