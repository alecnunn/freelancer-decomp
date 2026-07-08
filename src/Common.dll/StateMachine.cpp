// StateMachine -- abstract base for the AI state-graph state machines.
// Recovered from Common.dll; size 0x10. Polymorphic (vptr at +0x00). The
// concrete transition function is a pure virtual (vtable slot 8); process()
// and handle_state_change() are the virtual driver methods. Symbol-rich unit:
// these real definitions mangle to the original symbols and pair automatically.
//
// Layout (from the ctor / set_state / reset):
//   +0x00  vptr
//   +0x04  int   m_current_state
//   +0x08  int   m_pending_state
//   +0x0c  bool  m_state_changed
//   +0x0d  bool  m_processing
#include "common.h"

class StateMachine {
public:
    int  m_current_state;   // +0x04
    int  m_pending_state;   // +0x08
    bool m_state_changed;   // +0x0c
    bool m_processing;      // +0x0d

    StateMachine();
    virtual ~StateMachine();

    void reset();

protected:
    void set_state(int state);
};

StateMachine::StateMachine()
    : m_current_state(0), m_pending_state(0),
      m_state_changed(false), m_processing(false) {}

StateMachine::~StateMachine() {}

void StateMachine::reset() {
    m_current_state = 0;
    m_pending_state = 0;
}

void StateMachine::set_state(int state) {
    if (state != m_current_state) {
        m_pending_state = state;
        m_state_changed = true;
    }
}
