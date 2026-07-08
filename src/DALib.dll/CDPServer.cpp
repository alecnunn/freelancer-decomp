// DALib.dll -- CDPServer: DirectPlay8 host-session wrapper.
#include "DALib.h"
#include <string.h>   // memcpy

extern "C" __declspec(dllimport) unsigned short* __cdecl wcscpy(unsigned short* dst, const unsigned short* src);

unsigned long CDPServer::m_dwLastMsgReceivedTime;
CDPServer*    CDPServer::m_pServer;

void CDPServer::SetGUID(_GUID& guid) {
    m_appDesc.guidApplication = guid;
}

void CDPServer::SetSessionName(const unsigned short* name) {
    wcscpy(m_sessionNameBuf, name);
    if (m_host)
        m_host->SetApplicationDesc(&m_appDesc, 0);
}

void CDPServer::SetPassword(const unsigned short* password) {
    unsigned long flags;
    if (*password == 0) {
        m_appDesc.pwszPassword = 0;
        flags = m_appDesc.dwFlags & ~0x80;
    } else {
        wcscpy(m_passwordBuf, password);
        m_appDesc.pwszPassword = m_passwordBuf;
        flags = m_appDesc.dwFlags | 0x80;
    }
    m_appDesc.dwFlags = flags;
    if (m_host)
        m_host->SetApplicationDesc(&m_appDesc, 0);
}

void CDPServer::StopHosting() {
    if (m_host)
        m_host->Close(0);
}

void CDPServer::UpdateDescription() {
    if (m_host)
        m_host->SetApplicationDesc(&m_appDesc, 0);
}

// ReleaseHostAddresses: release and clear each cached host address.
void CDPServer::ReleaseHostAddresses() {
    unsigned int i = 0;
    if (m_addressCount > 0) {
        for (; i < m_addressCount; i++) {
            m_hostAddresses[i]->Release();
            m_hostAddresses[i] = 0;
        }
    }
    m_addressCount = 0;
}

void CDPServer::SetMaxPlayers(int max) {
    m_appDesc.dwMaxPlayers = max + 1;
    if (m_host)
        m_host->SetApplicationDesc(&m_appDesc, 0);
}

// SetEnumResponse: stash the host's enum-reply payload (rejects > 1KB).
bool CDPServer::SetEnumResponse(void* data, unsigned long len) {
    if (len > 0x400)
        return false;
    if (data != 0) {
        memcpy(m_enumResponse, data, len);
        m_enumResponseSize = len;
    } else {
        m_enumResponseSize = 0;
    }
    return true;
}

void CDPServer::DisconnectClient(unsigned long id) {
    if (m_host)
        m_host->DestroyClient(id, 0, 0, 0);
}

void CDPServer::CrashCleanup() {
    if (m_pServer && m_pServer->m_host)
        m_pServer->m_host->Close(0);
}

unsigned long CDPServer::GetLastMsgTimestamp() {
    return m_dwLastMsgReceivedTime;
}
