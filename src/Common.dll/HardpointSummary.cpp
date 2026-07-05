// HardpointSummary -- parallel arrays summarizing a model's hardpoints
// (names, HardpointInfo records, and per-hardpoint instance ids). Size 0x20;
// polymorphic (virtual dtor) so the vptr occupies +0x00. Symbol-rich unit:
// real member functions mangle to the original symbols and pair automatically.
#include "common.h"

struct HardpointSummary {
    // vptr at +0x00 (implied by the virtual destructor)
    int             m_count;        // +0x04  number of hardpoints
    char**          m_names;        // +0x08  array of name strings
    HardpointInfo*  m_infos;        // +0x0c  array of HardpointInfo (0x48 each)
    long*           m_instances;    // +0x10  array of instance ids
    int             m_field14;      // +0x14  cached index (init -1)
    int             m_field18;      // +0x18  cached index (init -1)
    int             m_field1c;      // +0x1c  (init 0)

    HardpointSummary();
    virtual ~HardpointSummary();

    void clear();
    const char* get_name(int index) const;
    const HardpointInfo& get_info(int index) const;
    long get_instance(int index) const;
};

HardpointSummary::HardpointSummary() {
    m_count = 0;
    m_names = 0;
    m_infos = 0;
    m_instances = 0;
    m_field14 = -1;
    m_field18 = -1;
    m_field1c = 0;
}

void HardpointSummary::clear() {
    m_count = 0;
    m_names = 0;
    m_infos = 0;
    m_instances = 0;
    m_field14 = -1;
    m_field18 = -1;
    m_field1c = 0;
}

const char* HardpointSummary::get_name(int index) const {
    return m_names[index];
}

const HardpointInfo& HardpointSummary::get_info(int index) const {
    return m_infos[index];
}

long HardpointSummary::get_instance(int index) const {
    return m_instances[index];
}
