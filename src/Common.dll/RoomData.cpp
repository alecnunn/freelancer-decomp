// RoomData -- a single room within a base (INI-backed, lazily loaded).
// Recovered from Common.dll; symbol-rich unit, so real member functions
// mangle to the original symbols and objdiff pairs them automatically.
//
// Only the trivial, self-contained members are modeled here (init / load /
// get_camera_info). The full class is large (list members, camera/setpoint
// tables through +0x1c8); its ctor/dtor, copy members, INI readers and fixup
// logic are deferred. The struct below therefore models only the leading
// fields touched by these functions -- it is intentionally not the full size.
#include "common.h"

// Embedded camera record returned by get_camera_info(); only its address is
// needed here, so a forward declaration is enough for the pointer return type.
struct RoomCameraInfo;

// Common.dll helper: strdup-into-slot. Frees *dst, copies src, stores it.
const char* malloc_strcpy(char** dst, const char* src);

struct RoomData {
    unsigned int  m_id;         // +0x00
    unsigned int  m_system;     // +0x04
    bool          m_loaded;     // +0x08
    unsigned char _pad9[3];     // +0x09
    char*         m_name;       // +0x0c
    char*         m_ini_path;   // +0x10

    void init(unsigned int id, unsigned int system,
              const char* name, const char* ini_path);
    void load();
    const RoomCameraInfo* get_camera_info() const;

private:
    void read_from_ini(const char* path);
};

void RoomData::init(unsigned int id, unsigned int system,
                    const char* name, const char* ini_path) {
    m_id = id;
    m_system = system;
    malloc_strcpy(&m_name, name);
    malloc_strcpy(&m_ini_path, ini_path);
    m_loaded = 0;
}

void RoomData::load() {
    if (!m_loaded) {
        read_from_ini(m_ini_path);
        m_loaded = 1;
    }
}

const RoomCameraInfo* RoomData::get_camera_info() const {
    return reinterpret_cast<const RoomCameraInfo*>(
        reinterpret_cast<const char*>(this) + 0x1c8);
}
