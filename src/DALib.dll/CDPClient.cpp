// DALib.dll -- CDPClient: DirectPlay8 client-session wrapper.
#include "DALib.h"

// Private static state (?m_dwXxx@CDPClient@@1KA).
unsigned long CDPClient::m_dwLastMsgReceivedTime;
unsigned long CDPClient::m_dwLinkQuality;
unsigned long CDPClient::m_dwSourcePort;
unsigned long CDPClient::m_dwPingReceiveCount;
unsigned long CDPClient::m_dwPingSendCount;

IDirectPlay8Client* CDPClient::GetClient() {
    return m_client;
}

long CDPClient::GetConnectResult() {
    return m_connectResult;
}

void CDPClient::SetGUID(_GUID& guid) {
    m_guid = guid;
}

unsigned long CDPClient::GetLastMsgTimestamp() {
    return m_dwLastMsgReceivedTime;
}

unsigned long CDPClient::GetLinkQuality() {
    return m_dwLinkQuality;
}

void CDPClient::SetSourcePort(unsigned long port) {
    m_dwSourcePort = port;
}

bool CDPClient::IsPingOutstanding() {
    return m_dwPingReceiveCount < m_dwPingSendCount;
}
