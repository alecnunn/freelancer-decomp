// DALib.dll -- CDPServer: DirectPlay8 host-session wrapper.
#include "DALib.h"

unsigned long CDPServer::m_dwLastMsgReceivedTime;

void CDPServer::SetGUID(_GUID& guid) {
    m_guid = guid;
}

unsigned long CDPServer::GetLastMsgTimestamp() {
    return m_dwLastMsgReceivedTime;
}
