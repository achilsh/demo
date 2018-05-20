#ifndef _skip_list_h_
#define _skip_list_h_
/**
 * @file: skiplist.h
 * @brief: 
 *       : 定义一个skiplist 模板.
 * @author:  wusheng Hu
 * @version: v0x0001
 * @date: 2018-05-20
 */
#include <iostream>
#include <iterator>
#include <assert.h>

using namespace std;

namespace NS_SKIPLIST
{
    class Random 
    {
     public:
      explicit Random(uint32_t seed);
      uint32_t Next();
      uint32_t Uniform(int n);
      bool OneIn(int n);
      uint32_t Skewed(int maxLog);
     private:
      uint32_t m_Seed;
    };

    template<typename K, typename V, typename Comparator>
    class SkipList
    {
     private:
      struct Node;
     public:
      explicit SkipList(Comparator cmpFunc);
      virtual ~SkipList();

      bool InsertNode(const K& inKey, const V& inVal);
      bool RemoveNode(const K& inKey);

      bool Contains(const K& inKey);
      V    GetVal(const K& inKey);
      void Print();

      class Iterator: public std::iterator<std::input_iterator_tag, K,V, Comparator>
      {
       public:
        explicit Iterator(const SkipList* sList);
        Iterator(const Iterator& iter);
        virtual ~Iterator()
        {
        }
        Iterator& operator = (const Iterator& iter);
        bool Valid() const;
        K Key() const;

        Iterator& operator ++();
        Iterator& operator ++(int);

        void Seek(const K& keyTarget);
        void SeekToFirst(); //
        void SeekToLast();  //

       private:
        const SkipList* m_pSList;
        Node* m_pNode;
      };

      Iterator begin();
      Iterator end();

     private:
      static const int CNTSTATIC_MAXLHEIGHT = 12;
      Comparator m_Compare;
      Node* m_pSListHead;
      int m_iMaxHeight;
      Random m_rnd;
      //
     private:
      void FreeList();
      int GetMaxHeight() const 
      {
          return m_iMaxHeight;
      }
      Node* NewNode(const K& inKey, const V& inVal, int height);
      int RandomHeight();
      bool Equal(const K& inKey1, const K& inKey2);
      bool KeyIsAferNode(const K& inKey, const Node* n) const;
      Node* FindGreaterOrEqual(const K& inKey, Node** preNode) const;
      Node* FindLessThan(const K& inKey) const;
      Node* FindLast() const;
    
     private:
      SkipList(const SkipList& )  {}
      void operator = (const SkipList &) {} 
    };

    //----------------------- struct Node implement -------------//
    template<typename K, typename V, typename Comparator>
    struct SkipList<K, V, Comparator>::Node
    {
        explicit Node(const K& inKey, const V& inVal): mKey(inKey), mVal(inVal)
        {
        }
        Node *Next(int n)
        {
            return pNextNode[n];            
        }
        void Setext(int n, Node* pNodeItem)
        {
            pNextNode[n] = pNodeItem;
        }
        K mKey;
        V mVal;
        struct Node* pNextNode[1];
    };

    //-------------- SkipList implement -------------------------//
    template<typename K, typename V, typename Comparator>
    SkipList<K,V, Comparator>::SkipList(Comparator cmpFunc): m_Compare(cmpFunc)
                                                             , m_pSListHead(NewNode(0, "0", CNTSTATIC_MAXLHEIGHT))
                                                             , m_iMaxHeight(1)
                                                             , m_rnd(0xdeadbeef)
    {
        for (int i = 0; i < CNTSTATIC_MAXLHEIGHT; ++i)
        {
            m_pSListHead->Setext(i, NULL);
        }
    }

    template<typename K, typename V, typename Comparator>
    SkipList<K,V, Comparator>::~SkipList() 
    {
        //FreeList();
    }

    template<typename K, typename V, typename Comparator>
    void SkipList<K,V, Comparator>::FreeList()
    {
        Node* pNode = m_pSListHead;
        Node* pNext = NULL;
        while (pNode)
        {
            pNext = pNode->Next(0);
            delete pNode;
            pNode = pNext;
        }
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Node*
    SkipList<K,V, Comparator>::NewNode(const K& inKey, const V& inVal, int height)
    {
        char *pMem = new char [ sizeof(Node) + sizeof(Node*) * (height - 1) ];
        return new (pMem) Node(inKey, inVal);
    }

    template<typename K, typename V, typename Comparator>
    int SkipList<K,V, Comparator>::RandomHeight()
    {
        static const unsigned int kBranching = 4;
        int height = 1;
        while (height < CNTSTATIC_MAXLHEIGHT && ((m_rnd.Next() % kBranching) == 0))
        {
            height ++;
        }
        assert(height > 0);
        assert(height <= CNTSTATIC_MAXLHEIGHT);
        return height;
    }

    template<typename K, typename V, typename Comparator>
    bool SkipList<K,V, Comparator>::KeyIsAferNode(const K& inKey, const Node* n) const
    {
        return ( n != NULL ) && (m_Compare(n->mKey, inKey) < 0);
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Node* SkipList<K,V, Comparator>::FindGreaterOrEqual(const K& inKey, Node** preNode) const
    {
        Node* tmpNode = m_pSListHead;
        int iLevel = GetMaxHeight() - 1;
        Node* pNextNode = NULL;
        
        for ( int i = iLevel; i >= 0; --i )
        {
            while( (pNextNode = tmpNode->Next(i)) && KeyIsAferNode(inKey, pNextNode))
            {
                tmpNode = pNextNode;
            }
            if (preNode)
            {
                preNode[i] = tmpNode;
            }
        }
        return pNextNode;
#if 0
        while(true)
        {
            pNextNode = tmpNode->Next(iLevel);
            if ( pNextNode != NULL && KeyIsAferNode(inKey, pNextNode) )
            {
                tmpNode = pNextNode;
            }
            else 
            {
                if (preNode != NULL)
                {
                    preNode[iLevel] = tmpNode;
                }
                if (iLevel == 0)
                {
                    return pNextNode;
                }
                else 
                {
                    iLevel--;
                }
            }
        }
#endif
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Node* SkipList<K,V, Comparator>::FindLessThan(const K& inKey) const
    {
        Node* pTmpNode = m_pSListHead;
        int iLevel = GetMaxHeight() - 1;
        while( true )
        {
            assert( pTmpNode  == m_pSListHead || m_Compare(pTmpNode->mKey, inKey) < 0 );
            Node* pNextNode = pTmpNode->Next(iLevel);
            if (pNextNode == NULL || m_Compare(pNextNode->mKey, inKey) >= 0)
            {
                if (iLevel == 0)
                {
                    return pTmpNode;
                }
                else 
                {
                    pTmpNode--;
                }
            }
            else 
            {
               pTmpNode = pNextNode;
            }
        }
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Node* SkipList<K,V, Comparator>::FindLast() const
    {
        Node* pTmpNode = m_pSListHead;
        int iLevel = GetMaxHeight() - 1;
        while (true)
        {
            Node* pNextNode = pTmpNode->Next(iLevel);
            if (pNextNode == NULL)
            {
                if (iLevel == 0)
                {
                    return pTmpNode;
                }
                else 
                {
                    iLevel--;
                }
            }
            else
            {
                pTmpNode = pNextNode;
            }
        }
    }

    template<typename K, typename V, typename Comparator>
    bool SkipList<K,V, Comparator>::Equal(const K& inKey1, const K& inKey2)
    {
        return m_Compare(inKey1, inKey2) == 0;
    }

    template<typename K, typename V, typename Comparator>
    bool SkipList<K,V, Comparator>::InsertNode(const K& inKey, const V& inVal)
    {
        Node* PreNodeList[CNTSTATIC_MAXLHEIGHT];
        Node* pGreateEqNode = FindGreaterOrEqual(inKey, PreNodeList);
        
        assert( pGreateEqNode == NULL || !Equal(inKey, pGreateEqNode->mKey) );
        int iHeight = RandomHeight();
        if ( iHeight > GetMaxHeight() )
        {
            for (int i = GetMaxHeight(); i < iHeight; i++)
            {
                PreNodeList[i] = m_pSListHead;
            }
            m_iMaxHeight = iHeight;
        }

        Node* pNewNode = NewNode(inKey, inVal, iHeight);
        for (int i = 0; i < iHeight; ++i)
        {
            pNewNode->Setext(i, PreNodeList[i]->Next(i));
            PreNodeList[i]->Setext(i, pNewNode);
        }
        return true;
    }

    template<typename K, typename V, typename Comparator>
    bool SkipList<K,V, Comparator>::RemoveNode(const K& inKey)
    {
        Node* PreNodeList[CNTSTATIC_MAXLHEIGHT];
        Node* pNextNode = NULL;
        Node* tmpNode = m_pSListHead;
        for (int iLevel = GetMaxHeight() - 1; iLevel >= 0; --iLevel)
        {
            while( (pNextNode = tmpNode->Next(iLevel)) && (KeyIsAferNode(inKey, pNextNode)) )
            {
                tmpNode = pNextNode;
            }
            PreNodeList[iLevel] = tmpNode;
        }

        if (pNextNode->mKey != inKey)
        {
            std::cout << "not find key: " << inKey << ", in skip list" << std::endl;
            return false;
        }

        for (int i = 0 ; i < GetMaxHeight(); i++)
        {
            if (PreNodeList[i]->Next(i) == pNextNode)
            {
                PreNodeList[i]->Setext(i, pNextNode->Next(i));
            }
        }

        delete pNextNode;

        for (int i = GetMaxHeight() - 1; i >= 0; i-- )
        {
            if (m_pSListHead->Next(i) == NULL)
            {
                m_iMaxHeight--;
            }
        }
        return true;
    }

    template<typename K, typename V, typename Comparator>
    bool SkipList<K,V, Comparator>::Contains(const K& inKey)
    {
        Node* pNode = FindGreaterOrEqual(inKey, NULL);
        if (pNode != NULL && Equal(inKey, pNode->mKey))
        {
            return true;
        }
        return false;
    }

    template<typename K, typename V, typename Comparator>
    V  SkipList<K,V, Comparator>::GetVal(const K& inKey)
    {
        Node* PreNodeList[CNTSTATIC_MAXLHEIGHT];
        Node* pNextNode = FindGreaterOrEqual(inKey, PreNodeList);
        if (pNextNode->mKey != inKey)
        {
            return NULL;
        }
        return pNextNode->mVal;
    }
    
    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Iterator SkipList<K,V, Comparator>::begin()
    {
        SkipList<K,V, Comparator>::Iterator iter =  SkipList<K,V, Comparator>::Iterator(this);
        iter.SeekToFirst();
        return iter;
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V, Comparator>::Iterator SkipList<K,V, Comparator>::end()
    {
        SkipList<K,V, Comparator>::Iterator iter =  SkipList<K,V, Comparator>::Iterator(this);
        iter.SeekToLast();
        return iter;
    }
    
    template<typename K, typename V, typename Comparator>
    void SkipList<K,V, Comparator>::Print()
    {
        Node*  pNodeHead = NULL;
        Node*  pNodeNext = NULL;
        for (int i = GetMaxHeight() - 1; i >= 0; --i )
        {
            pNodeHead = m_pSListHead;
            while ( (pNodeNext = pNodeHead->Next(i)) )
            {
                std::cout << "val: " << pNodeHead->mVal << std::endl;
                pNodeHead = pNodeNext;
            }
        }
    }

    //----------------- Iterator implement ------------------------------//
    template<typename K, typename V, typename Comparator>
    inline SkipList<K,V, Comparator>::Iterator::Iterator(const SkipList* sList)
        : m_pSList(sList), m_pNode(NULL)
    {
    }

    template<typename K, typename V, typename Comparator>
    inline SkipList<K,V, Comparator>::Iterator::Iterator(const SkipList<K,V, Comparator>::Iterator& iter)
    {
        m_pSList = iter.m_pSList;
        m_pNode = iter.m_pNode;
    }

    template<typename K, typename V, typename Comparator>
    inline typename SkipList<K,V, Comparator>::Iterator& SkipList<K,V, Comparator>::Iterator::operator = (const SkipList<K,V, Comparator>::Iterator& iter)
    {
        if (*this != iter)
        {
            m_pSList = iter.m_pSList;
            m_pNode = iter.m_pNode;
        }
        return *this;
    }
    
    template<typename K, typename V, typename Comparator>
    inline bool SkipList<K,V, Comparator>::Iterator::Valid() const 
    {
        return m_pNode != NULL;
    }

    template<typename K, typename V, typename Comparator>
    inline K SkipList<K,V, Comparator>::Iterator::Key() const
    {
       assert(Valid()); 
       m_pNode->mKey;
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V,Comparator>::Iterator& SkipList<K,V,Comparator>::Iterator::operator ++ ()
    {
        assert(Valid());
        m_pNode = m_pNode->Next(0);
        return *this; 
    }

    template<typename K, typename V, typename Comparator>
    typename SkipList<K,V,Comparator>::Iterator& SkipList<K,V,Comparator>::Iterator::operator ++(int)
    {
        Iterator preNode( *this );
       operator ++();
       return preNode;
    }

    template<typename K, typename V, typename Comparator>
    void SkipList<K,V,Comparator>::Iterator::Seek(const K& keyTarget)
    {
        m_pNode = m_pSList->FindGreaterOrEqual(keyTarget, NULL);
    }

    template<typename K, typename V, typename Comparator>
    void SkipList<K,V,Comparator>::Iterator::SeekToFirst()
    {
        m_pNode = (m_pSList->m_pSListHead)->Next(0);
    }

    template<typename K, typename V, typename Comparator>
    void SkipList<K,V,Comparator>::Iterator::SeekToLast()
    {
        m_pNode = m_pSList->FindLast();
        if (m_pNode == m_pSList->m_pSListHead)
        {
            m_pNode = NULL;
        }
    }
    

    //------------------- Random implement -----------------------------//
    Random::Random(uint32_t seed): m_Seed(seed & 0x7fffffffu)
    {
        if ( m_Seed == 0 || m_Seed == 2147483647L )
        {
            m_Seed = 1;
        }
    }
    uint32_t Random::Next()
    {
        static const uint32_t M = 2147483647L;
        static const uint64_t A = 16807;
        uint64_t ui64Product = m_Seed * A;
        m_Seed = static_cast<uint64_t>((ui64Product >> 31) + (ui64Product & M));
        if (m_Seed > M)
        {
            m_Seed -= M;
        }
        return m_Seed;
    }

    uint32_t Random::Uniform( int n )
    {
        return Next() % n;
    }
    bool Random::OneIn(int n)
    {
        return (Next() % n)== 0;
    }
    uint32_t Random::Skewed(int maxLog)
    {
        return Uniform( 1 << Uniform(maxLog + 1) );
    }
}

#endif
