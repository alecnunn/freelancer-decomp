// BaseWatcher -- base of the Watcher<T> intrusive-observer template. Holds a
// pointer to the Watchable it observes (offset 0) and the next watcher link
// (offset 4) threading the watchable's singly-linked list of watchers.
// Recovered from Common.dll; symbol-rich unit: real member functions mangle to
// the original symbols and pair automatically.
#include "common.h"

struct Watchable;

struct BaseWatcher {
    const Watchable* m_watched;  // +0x00  object being observed (list head lives at its +0x00)
    BaseWatcher*     m_next;     // +0x04  next watcher in m_watched's list

    ~BaseWatcher();
    void set(const Watchable* w);

protected:
    void set_pointer(const Watchable* w);
};

BaseWatcher::~BaseWatcher() {
    if (m_watched != 0)
        set_pointer(0);
}

void BaseWatcher::set(const Watchable* w) {
    if (w != m_watched)
        set_pointer(w);
}
