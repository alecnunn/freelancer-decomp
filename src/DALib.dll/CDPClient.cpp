// DALib.dll -- CDPClient: DirectPlay8 client-session wrapper.
#include "DALib.h"

// ?m_dwLastMsgReceivedTime@CDPClient@@1KA -- private static timestamp.
unsigned long CDPClient::m_dwLastMsgReceivedTime;

IDirectPlay8Client* CDPClient::GetClient() {
    return m_client;
}

unsigned long CDPClient::GetLastMsgTimestamp() {
    return m_dwLastMsgReceivedTime;
}
