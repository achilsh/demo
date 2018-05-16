#include "cond_mutx.h"
#include <assert.h>

namespace MUTX_DEF
{
    ConVar::ConVar(Def_Mutex* mu)
        :m_pMu(mu)
    {
        assert(m_pMu != NULL);
    }

    ConVar::~ConVar()
    {
        m_pMu = NULL;
    }
    void ConVar::Wait()
    {
        std::unique_lock<std::mutex> lock( m_pMu->m_Mutex, std::adopt_lock );
        //std::unique_lock<std::mutex> lock( m_pMu->m_Mutex );
        m_cV.wait(lock);
        lock.release();
    }
    void ConVar::Signal()
    {
        m_cV.notify_one();
    }
    void ConVar::SignalAll()
    {
        m_cV.notify_all();
    }
}
