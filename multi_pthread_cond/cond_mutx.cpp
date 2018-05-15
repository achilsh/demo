#include "cond_mutx.h"
#include "mutex_def.h"

namespace MUTX_DEF
{
    ConVar::ConVar(Def_Mutex* mu)
        :m_pMu(mu)
    {
        assert(m_pMu != NULL);
    }

    ConVar::~ConVar()
    {
    }
    void ConVar::Wait()
    {
        std::unique_lock<std::mutex> lock( m_pMu->m_Mutex, std::adopt_lock );
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
