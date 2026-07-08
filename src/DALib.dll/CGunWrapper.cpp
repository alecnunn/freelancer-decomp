// DALib.dll -- CGunWrapper: wraps a GameSpy/"Gun" connection (host + browser).
// Symbol-rich; the accessors pair automatically.
#include "DALib.h"

IGunHost* CGunWrapper::GetHost() {
    return m_host;
}

IGunBrowser* CGunWrapper::GetBrowser() {
    return m_browser;
}

IGunConnection::ConnectStatus CGunWrapper::GetStatus() {
    return m_status;
}

long __stdcall CGunWrapper::Read(Gun2::GUNQueueMessage*) {
    return 0;
}

void CGunWrapper::DispatchQueue() {
    if (m_conn)
        m_conn->Dispatch(this);
}
