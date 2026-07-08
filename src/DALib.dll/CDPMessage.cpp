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

CDPMessage& CDPMessage::operator=(const CDPMessage& o) {
    m_field_4 = o.m_field_4;
    m_data = o.m_data;
    m_size = o.m_size;
    m_field_10 = o.m_field_10;
    m_field_14 = o.m_field_14;
    m_field_18 = o.m_field_18;
    m_field_1c = o.m_field_1c;
    return *this;
}

unsigned char* const CDPMessage::GetData() {
    return m_data;
}

const unsigned long CDPMessage::GetSize() {
    return m_size;
}
