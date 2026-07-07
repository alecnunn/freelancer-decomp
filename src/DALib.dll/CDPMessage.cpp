// DALib.dll -- CDPMessage: a DirectPlay message buffer (data ptr + size).
#include "DALib.h"

CDPMessage::CDPMessage() {
    m_field_10 = 0;
    m_data = 0;
    m_size = 0;
    m_field_14 = 0;
    m_field_18 = 0;
    m_field_4 = 0;
}

CDPMessage::~CDPMessage() {}

unsigned char* const CDPMessage::GetData() {
    return m_data;
}

const unsigned long CDPMessage::GetSize() {
    return m_size;
}
