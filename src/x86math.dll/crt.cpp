// x86math.dll -- CRT helpers reproduced from the MSVC 6.0 runtime source.
// These carry their canonical CRT symbol names, so they pair without a claim.
#include "x86math.h"

typedef void (__cdecl* _PVFV)(void);

extern "C" _PVFV __cdecl _onexit(_PVFV fn);

// The CRT was built favouring size (/Os): argument passed via `push [mem]` and
// the stack cleaned with `pop ecx` rather than `add esp,4`.
#pragma optimize("s", on)

// atexit: register fn via _onexit; map its result to 0 (ok) / -1 (failure).
// 75%: correct + both /Os idioms; residual is the cdecl cleanup `pop ecx`
// placement -- the precompiled CRT was built without /G6, so its P6 scheduler
// orders the cleanup pop differently from this /G6 unit (flag-mismatch cap).
extern "C" int __cdecl atexit(_PVFV fn) {
    return (_onexit(fn) == 0) ? -1 : 0;
}

#pragma optimize("", on)
