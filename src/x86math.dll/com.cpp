// x86math.dll -- COM plumbing for the x86MathEngine component.
// The engine is a static singleton, so its IUnknown methods are trivial: QI
// always fails (single concrete interface reached via the factory) and the
// combined AddRef/Release returns a constant refcount of 1. `this` is the first
// stack argument (COM __stdcall ABI), so these are modelled as free functions.
#include "x86math.h"

// x86MathEngine::QueryInterface -- *ppv = 0; return E_NOINTERFACE.
extern "C" long __stdcall x86m_QueryInterface(void* /*self*/, const void* /*riid*/, void** ppv) {
    *ppv = 0;
    return -1;
}

// x86MathEngine::AddRef_Release -- static singleton, refcount is always 1.
extern "C" unsigned long __stdcall x86m_AddRef_Release(void* /*self*/) {
    return 1;
}
