// DALib.dll -- CDPMsgList: a thread-safe queue of received DirectPlay messages.
// Lock/Unlock guard the list with a Win32 critical section at +0x10.
#include "DALib.h"

void CDPMsgList::Lock() {
    EnterCriticalSection(&m_cs);
}

void CDPMsgList::Unlock() {
    LeaveCriticalSection(&m_cs);
}

void CDPMsgList::SetEmptyEvent() {
    SetEvent(m_hEmptyEvent);
}

void CDPMsgList::WaitForMsg(unsigned long timeout) {
    WaitForSingleObject(m_hEmptyEvent, timeout);
}

CDPMessage* CDPMsgList::PeekNextMsg() {
    CDPMessage* result = 0;
    EnterCriticalSection(&m_cs);
    if (m_count != 0)
        result = m_head->next->value;
    LeaveCriticalSection(&m_cs);
    return result;
}
