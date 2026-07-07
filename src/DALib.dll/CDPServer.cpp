// DALib.dll -- CDPServer: DirectPlay8 host-session wrapper.
#include "DALib.h"

extern "C" __declspec(dllimport) unsigned short* __cdecl wcscpy(unsigned short* dst, const unsigned short* src);

unsigned long CDPServer::m_dwLastMsgReceivedTime;
CDPServer*    CDPServer::m_pServer;

void CDPServer::SetGUID(_GUID& guid) {
    m_guid = guid;
}

void CDPServer::SetSessionName(const unsigned short* name) {
    wcscpy(m_sessionNameBuf, name);
    if (m_host)
        m_host->SetApplicationDesc(m_appDesc, 0);
}

void CDPServer::StopHosting() {
    if (m_host)
        m_host->Close(0);
}

void CDPServer::UpdateDescription() {
    if (m_host)
        m_host->SetApplicationDesc(m_appDesc, 0);
}

void CDPServer::SetMaxPlayers(int max) {
    m_maxPlayers = max + 1;
    if (m_host)
        m_host->SetApplicationDesc(m_appDesc, 0);
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
