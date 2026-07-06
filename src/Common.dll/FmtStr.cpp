// FmtStr -- a format string built from a singly-linked list of typed values
// (FmtStr::Val nodes). Used to marshal localized/parameterized message text.
// Recovered from Common.dll; FmtStr size 0x18, FmtStr::Val size 0x0c.
// Symbol-rich unit: real member functions mangle to the original symbols and
// pair automatically.
#include "common.h"

struct FmtStr {
    // A single value node in the format string's linked list.
    struct Val {
        Val*           m_next;   // +0x00  next node
        void*          m_data;   // +0x04  payload (id, pointer, or nested list)
        unsigned short m_type;   // +0x08  type tag ('d','s','!','N', ...)
        unsigned char  m_flag;   // +0x0a  ordinal / sub-index
        unsigned char  _pad_b;   // +0x0b

        // Construct a leaf value: type tag, raw payload, ordinal flag.
        Val(unsigned short type, void* data, unsigned char flag);
        // Deserialize a value from a flat buffer.
        Val(void const* p);
        // Deserialize a value, reporting the number of bytes consumed.
        Val(void const* p, int& consumed);

    private:
        // Parse a value out of a flat buffer; returns bytes consumed.
        int InitFromVoid(void const* p);
    };

    Val*          m_head;        // +0x00  head of the value list
    unsigned int  m_base;        // +0x04  base string id
    unsigned char m_counts[14];  // +0x08  per-type ordinal counters
    unsigned char _pad_16[2];    // +0x16  (sizeof rounds to 0x18)
};

// mov [this+4],data; mov dword [this],0; mov [this+8],type; mov [this+0xa],flag
FmtStr::Val::Val(unsigned short type, void* data, unsigned char flag) {
    m_data = data;
    m_next = 0;
    m_type = type;
    m_flag = flag;
}

FmtStr::Val::Val(void const* p) {
    m_next = 0;
    InitFromVoid(p);
}

FmtStr::Val::Val(void const* p, int& consumed) {
    m_next = 0;
    consumed = InitFromVoid(p);
}
