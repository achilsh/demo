#include <iostream>
#include <stdint.h>
#include <string>
#include "skiplist.h"
#include <set>
#include <sstream>

using namespace NS_SKIPLIST;
using namespace std;

typedef uint64_t  TKey;
struct TComparator 
{
    int operator() (const TKey& key1, const TKey& key2)  const
    {
        if (key1 < key2)
        {
            return -1;
        }
        else if (key1 > key2)
        {
            return 1;
        }
        else 
        {
            return 0;
        }
    }
};

int main()
{
    TComparator cmp;
    //------------- empty test --------------------//
    SkipList<TKey,std::string, TComparator> item(cmp);
    {
        TKey exitKey = 10;
        std::cout <<  item.Contains(exitKey) << std::endl;

        SkipList<TKey,std::string, TComparator>::Iterator itBegin = item.begin();
        std::cout << itBegin.Valid() << std::endl;

        itBegin.SeekToFirst();
        std::cout << itBegin.Valid() << std::endl;

        itBegin.Seek(100);
        std::cout << itBegin.Valid() << std::endl;

        itBegin.SeekToLast();
        std::cout << itBegin.Valid() << std::endl;
    }

    //---------- one key insert and query -------------------//
    {
        TKey insertKey = 2234;
        std::string insertVal = "test1234";
        bool insertRet = item.InsertNode(insertKey, insertVal);
        std::cout << "insert  ret: " << insertRet << std::endl;
        std::cout << "insertkey exist in skiplist: " << item.Contains(insertKey) << std::endl;
        std::cout << "get insert key val: " << item.GetVal(insertKey) << std::endl;
    }

    //------------ batch insert & query test ----------------//
    {
        const int iCountOne = 2000;
        const int iCountTwo = 5000;
        Random rnd(1000);
        std::set<TKey> setKeys;
        SkipList<TKey,std::string, TComparator> batchTest(cmp);
        
        int iInsertNums = 0;
        for (int i = 0; i < iCountOne; ++i)
        {
            TKey testKey = rnd.Next() % iCountTwo;
            if (setKeys.insert(testKey).second)
            {
                std::stringstream ios;
                ios << "test" <<  testKey;
                batchTest.InsertNode(testKey, ios.str());
                iInsertNums ++;
            }
        }

        int iContainNums = 0;
        for (int i = 0; i < iCountTwo; ++i)
        {
            if (batchTest.Contains(i))
            {
                if (setKeys.count(i) <= 0)
                {
                    std::cout << "key: " << i << "err" << std::endl;
                }
                if (setKeys.count(i) == 1)
                {
                    iContainNums++;
                }
            }
        }
        std::cout << "insert key nums: " << iInsertNums << ", query nums: " << iContainNums << std::endl;
        //batchTest.Print();
    }

    //------------------ one test: insert /query/ Remove/ query -----------//
    {
        TKey insertKey = 234;
        std::string insertVal = "test4234";
        bool insertRet = item.InsertNode(insertKey, insertVal);
        std::cout << "insert  ret: " << insertRet << std::endl;
        std::cout << "insertkey exist in skiplist: " << item.Contains(insertKey) << std::endl;
        std::cout << "get insert key val: " << item.GetVal(insertKey) << std::endl;
        //
        bool retRemove = item.RemoveNode(insertKey);
        std::cout << "removenode ret: " << retRemove << std::endl;

        bool bQuery = item.Contains(insertKey);
        std::cout << "query after remove ret: " << bQuery << std::endl;
        if (bQuery == true)
        {
            std::cout << "get insert key val: " << item.GetVal(insertKey) << std::endl;
        }
    }
    return 0;
}
