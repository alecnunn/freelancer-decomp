// TextFile32 -- reads an in-memory text buffer line by line into LineParser32.
// Recovered from Common.dll; size 0x28. Layout: an embedded std::string at
// +0x00 (0x10 bytes, holds the source text), a data window (buffer ptr +0x18,
// end +0x1c, cursor +0x20) and a running line counter at +0x24. Symbol-rich
// unit: real member functions mangle to the original symbols and pair
// automatically.
#include "common.h"

struct TextFile32 {
    unsigned char pad_0x00[0x24];  // +0x00  std::string source + data window
    unsigned int  m_line_num;      // +0x24  running line counter

    unsigned int get_line_num() const;
};

unsigned int TextFile32::get_line_num() const { return m_line_num; }
