// IAction -- base "action" interface (vtable + one field). Symbol-rich unit:
// real member functions mangle to the original symbols and pair automatically.
// Recovered from Common.dll; size 0x08 (vtable ptr + one int field).
#include "common.h"

struct IAction {
    virtual ~IAction();
    virtual const char* get_id() const;

    int m_field;   // +0x04  zeroed by the default constructor

    IAction();
};

IAction::IAction() {
    m_field = 0;
}

IAction::~IAction() {
}

const char* IAction::get_id() const {
    return "";
}
