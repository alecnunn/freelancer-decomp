// x86math.dll -- the IComponentFactory::CreateInstance for the x86MathEngine.
// A DACOM class-object request carries {len, iid, name}; the factory validates
// the requested IID (I3DMathEngine) and optional implementation name, then hands
// back the singleton engine (AddRef'd). `this` is the factory subobject embedded
// at +4 in the engine, so the engine base is `this - 4`.
#include "x86math.h"
#include <string.h>   // memcmp (intrinsic under /Oi)

// DACOM class-object request descriptor.
struct DACOMRequest {
    int         len;    // +0x00  IID length (0xc for a GUID)
    const char* iid;    // +0x04  requested interface id
    const char* name;   // +0x08  optional implementation name
};

extern "C" char IID_I3DMathEngine[];      // the 13-byte interface id
extern "C" char implementation_name[];    // this component's implementation name
extern "C" __declspec(dllimport) int __cdecl stricmp(const char*, const char*);

// 69%: logic fully recovered and correct -- the memcmp(...,13) intrinsic matches
// as `repe cmpsb`, the vtable AddRef dispatch, error codes (-2/-3), and struct all
// pair. Residual is compiler codegen we can't steer from source: the memcmp
// intrinsic's esi/ecx setup order, minor test-eax scheduling, and the multi-exit
// block layout (MSVC places one -3 return inline vs the original's out-of-line).
extern "C" long __stdcall x86m_CreateInstance(void* self, const DACOMRequest* req, void** ppv) {
    *ppv = 0;
    if (req == 0 || req->iid == 0)
        return -2;
    if (req->len != 0xc || memcmp(IID_I3DMathEngine, req->iid, 13) != 0)
        return -3;
    if (req->name != 0 && stricmp(implementation_name, req->name) != 0)
        return -3;
    // Return the engine singleton (this factory is embedded at engine+4), AddRef'd.
    void** engine = (void**)((char*)self - 4);
    void** vtbl = (void**)*engine;
    ((void(__stdcall*)(void*))vtbl[1])(engine);
    *ppv = engine;
    return 0;
}
