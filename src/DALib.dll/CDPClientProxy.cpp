// DALib.dll -- CDPClientProxy: the server's per-client send-queue accounting.
// The queue-size getters delegate to the owning CDPServer and add the proxy's
// own locally-buffered counts.
#include "DALib.h"

unsigned int CDPClientProxy::GetSendQSize() {
    return m_server->GetSendQSize(this) + m_localQSize;
}

unsigned int CDPClientProxy::GetSendQBytes() {
    return m_server->GetSendQBytes(this) + m_localQBytes;
}

void CDPClientProxy::OnMsgSent(unsigned long) {}

double CDPClientProxy::GetLinkSaturation() {
    return m_linkSaturation;
}

bool CDPClientProxy::Disconnect() {
    m_server->DisconnectClient(m_clientId);
    return true;
}
