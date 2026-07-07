// DALib.dll -- CDPClient: DirectPlay8 client-session wrapper.
#include "DALib.h"

extern "C" __declspec(dllimport) void __stdcall CoUninitialize();

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

// Cleanup: cancel/close/release the DP8 client, then undo CoInitialize.
void CDPClient::Cleanup() {
    if (m_client) {
        m_client->CancelAsyncOperation(0, 0x8000);
        m_client->Close(0);
        m_client->Release();
        m_client = 0;
    }
    if (m_coInitialized) {
        CoUninitialize();
        m_coInitialized = false;
    }
}

// Close: cancel pending ops and close the client (without releasing it).
void CDPClient::Close() {
    if (m_client) {
        m_client->CancelAsyncOperation(0, 0x8000);
        m_client->Close(0);
    }
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

void CDPClient::CancelEnums() {
    if (m_client)
        m_client->CancelAsyncOperation(0, 2);
}
