// DALib.dll -- shared type declarations recovered from the original binary.
#ifndef DALIB_H
#define DALIB_H

// MD5 message-digest. Size ~0x60; polymorphic (virtual dtor).
class MD5Hash {
public:
    unsigned int  m_state[4];    // +0x04
    unsigned int  m_count[2];    // +0x14
    unsigned char m_buffer[64];  // +0x1c
    char          m_string[128]; // +0x5c  (hex-digest text from AsString; object ends 0xdc)

    MD5Hash();
    virtual ~MD5Hash();

    unsigned char* GetStatePtr();
    bool Compare(MD5Hash& other);
    const char* AsString();
    void FromString(const char* str);
    bool AddData(void* const input, unsigned long inputLen);
    bool CalcValue();

protected:
    void Transform(unsigned char* block);
    void Encode(unsigned char* output, unsigned long* input, unsigned long len);
    void Decode(unsigned long* output, unsigned char* input, unsigned long len);
};

// --- Win32 critical section (minimal; avoids pulling in <windows.h>) ---
struct _RTL_CRITICAL_SECTION {
    void*         DebugInfo;
    long          LockCount;
    long          RecursionCount;
    void*         OwningThread;
    void*         LockSemaphore;
    unsigned long SpinCount;
};
typedef struct _RTL_CRITICAL_SECTION CRITICAL_SECTION;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(CRITICAL_SECTION*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(CRITICAL_SECTION*);
extern "C" __declspec(dllimport) int  __stdcall SetEvent(void*);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*, unsigned long);

// IDPMsgHandler -- abstract DirectPlay message-handler callback interface.
class IDPMsgHandler {
public:
    IDPMsgHandler();
    IDPMsgHandler(const IDPMsgHandler&);
    IDPMsgHandler& operator=(const IDPMsgHandler&);
    virtual void OnReceive(unsigned char*, unsigned long);
    virtual void OnDisconnect();
};

namespace Gun2 { struct GUNQueueMessage; }

// --- DirectPlay / Gun interfaces (COM __stdcall; named slots are dispatched) ---
struct IGunHost;
struct IGunBrowser;

// DirectPlay8 client interface.
struct IDirectPlay8Client {
    virtual long __stdcall _s0() = 0;
    virtual long __stdcall _s1() = 0;
    virtual long __stdcall Release() = 0;   // slot 2 (0x08)
    virtual long __stdcall _s3() = 0;
    virtual long __stdcall _s4() = 0;
    virtual long __stdcall _s5() = 0;
    virtual long __stdcall CancelAsyncOperation(unsigned long handle, unsigned long flags) = 0;  // slot 6 (0x18)
    virtual long __stdcall _s7() = 0;
    virtual long __stdcall _s8() = 0;
    virtual long __stdcall _s9() = 0;
    virtual long __stdcall _s10() = 0;
    virtual long __stdcall _s11() = 0;
    virtual long __stdcall _s12() = 0;
    virtual long __stdcall _s13() = 0;
    virtual long __stdcall Close(unsigned long flags) = 0;   // slot 14 (0x38)
};

// DACOM file-system interface (IUnknown-derived); Release at slot 2.
struct IFileSystem {
    virtual long __stdcall _s0() = 0;
    virtual long __stdcall _s1() = 0;
    virtual long __stdcall Release() = 0;   // slot 2 (0x8)
};

// A "Gun" (GameSpy) connection; DispatchQueue is dispatched at slot 8.
struct IGunConnection {
    enum ConnectStatus { CS_NONE };
    virtual long __stdcall _s0() = 0;
    virtual long __stdcall _s1() = 0;
    virtual long __stdcall _s2() = 0;
    virtual long __stdcall _s3() = 0;
    virtual long __stdcall _s4() = 0;
    virtual long __stdcall _s5() = 0;
    virtual long __stdcall _s6() = 0;
    virtual long __stdcall _s7() = 0;
    virtual long __stdcall Dispatch(void* wrapper) = 0;   // slot 8 (0x20)
};

namespace DALib {
    extern IFileSystem* Data;   // ?Data@DALib@@3PAUIFileSystem@@A
    void CloseData();
}

// CGunWrapper -- wraps a "Gun" (GameSpy) host + browser connection.
class CGunWrapper {
public:
    unsigned char                 _pad_0[0x08];   // +0x00 (vptr@0 + 8)
    IGunConnection*               m_conn;         // +0x0c
    IGunHost*                     m_host;         // +0x10
    IGunBrowser*                  m_browser;      // +0x14
    IGunConnection::ConnectStatus m_status;       // +0x18

    IGunHost* GetHost();
    IGunBrowser* GetBrowser();
    IGunConnection::ConnectStatus GetStatus();
    void DispatchQueue();
    virtual long __stdcall Read(Gun2::GUNQueueMessage*);
};

// CDPMessage -- a received/queued DirectPlay message (data + size).
class CDPMessage {
public:
    unsigned int   m_field_4;   // +0x04
    unsigned char* m_data;      // +0x08
    unsigned long  m_size;      // +0x0c
    unsigned int   m_field_10;  // +0x10
    unsigned int   m_field_14;  // +0x14
    unsigned int   m_field_18;  // +0x18

    CDPMessage();
    virtual ~CDPMessage();

    unsigned char* const GetData();
    const unsigned long GetSize();
};

class CDPClientProxy;

// COM GUID (16 bytes).
struct _GUID {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
};

// IDirectPlay8Server -- DirectPlay8 host interface (COM __stdcall; only the
// dispatched slots are named, the rest are vtable placeholders).
struct IDirectPlay8Server {
    virtual long __stdcall _s0() = 0;
    virtual long __stdcall _s1() = 0;
    virtual long __stdcall _s2() = 0;
    virtual long __stdcall _s3() = 0;
    virtual long __stdcall _s4() = 0;
    virtual long __stdcall _s5() = 0;
    virtual long __stdcall _s6() = 0;
    virtual long __stdcall _s7() = 0;
    virtual long __stdcall _s8() = 0;
    virtual long __stdcall _s9() = 0;
    virtual long __stdcall _s10() = 0;
    virtual long __stdcall _s11() = 0;
    virtual long __stdcall SetApplicationDesc(void* desc, unsigned long flags) = 0;   // slot 12 (0x30)
    virtual long __stdcall _s13() = 0;
    virtual long __stdcall _s14() = 0;
    virtual long __stdcall _s15() = 0;
    virtual long __stdcall _s16() = 0;
    virtual long __stdcall _s17() = 0;
    virtual long __stdcall _s18() = 0;
    virtual long __stdcall _s19() = 0;
    virtual long __stdcall _s20() = 0;
    virtual long __stdcall _s21() = 0;
    virtual long __stdcall _s22() = 0;
    virtual long __stdcall Close(unsigned long flags) = 0;   // slot 23 (0x5c)
    virtual long __stdcall DestroyClient(unsigned long id, void* ctx, unsigned long a, unsigned long b) = 0;   // slot 24 (0x60)
};

// CDPServer -- DirectPlay8 host-session wrapper. The DPN_APPLICATION_DESC lives
// inline at +0x08 (its guidApplication is m_guid@0x20, dwMaxPlayers is @0x30).
class CDPServer {
public:
    unsigned char        _pad_0[0x04];   // +0x00 (vptr)
    IDirectPlay8Server*  m_host;         // +0x04
    unsigned char        m_appDesc[0x18];// +0x08 (app desc region, guid at +0x20)
    _GUID                m_guid;         // +0x20  guidApplication
    unsigned int         m_maxPlayers;   // +0x30  dwMaxPlayers
    unsigned char        _pad_34[0x50 - 0x34];
    unsigned short       m_sessionNameBuf[0x104]; // +0x50  wchar[260]

    unsigned int GetSendQSize(CDPClientProxy*);
    unsigned int GetSendQBytes(CDPClientProxy*);
    void SetGUID(_GUID& guid);
    void SetMaxPlayers(int max);
    void SetSessionName(const unsigned short* name);
    void DisconnectClient(unsigned long id);
    void StopHosting();
    static void CrashCleanup();
    static unsigned long GetLastMsgTimestamp();

protected:
    void UpdateDescription();

private:
    static unsigned long m_dwLastMsgReceivedTime;
    static CDPServer*    m_pServer;
};

// CDPClientProxy -- server-side view of a connected client.
class CDPClientProxy {
public:
    unsigned char _pad_0[0x04];         // +0x00 (vptr)
    CDPServer*    m_server;             // +0x04
    unsigned long m_clientId;           // +0x08
    unsigned char _pad_0c[0x3c - 0x0c]; // +0x0c .. +0x3c
    unsigned int  m_localQBytes;        // +0x3c
    unsigned int  m_localQSize;         // +0x40
    unsigned char _pad_44[0x58 - 0x44]; // +0x44 .. +0x58
    double        m_linkSaturation;     // +0x58

    unsigned int GetSendQSize();
    unsigned int GetSendQBytes();
    void OnMsgSent(unsigned long);
    double GetLinkSaturation();
    bool Disconnect();
};

// A node in CDPMsgList's std::list<CDPMessage*> (next, prev, value).
struct MsgNode {
    MsgNode*    next;   // +0x00
    MsgNode*    prev;   // +0x04
    CDPMessage* value;  // +0x08
};

// CDPMsgList -- thread-safe received-message queue: a std::list<CDPMessage*>
// (sentinel node @0x8, size @0xc) guarded by a critical section @0x10.
class CDPMsgList {
public:
    void*            vtable;          // +0x00
    void*            m_proxy;         // +0x04 (std::list allocator proxy)
    MsgNode*         m_head;          // +0x08 (list sentinel node)
    unsigned int     m_count;         // +0x0c
    CRITICAL_SECTION m_cs;            // +0x10
    void*            m_hEmptyEvent;   // +0x28

    void Lock();
    void Unlock();
    void SetEmptyEvent();
    void WaitForMsg(unsigned long timeout);
    CDPMessage* PeekNextMsg();
};

// CDPClient -- DirectPlay8 client wrapper (m_client @0x04).
class CDPClient {
public:
    unsigned char        _pad_0[0x04];         // +0x00 (vptr)
    IDirectPlay8Client*  m_client;             // +0x04
    unsigned char        _pad_08[0x68 - 0x08]; // +0x08 .. +0x68
    _GUID                m_guid;               // +0x68
    unsigned char        _pad_78[0x7c - 0x78]; // +0x78 .. +0x7c
    long                 m_connectResult;      // +0x7c
    unsigned char        _pad_80[0x8c - 0x80]; // +0x80 .. +0x8c
    bool                 m_coInitialized;      // +0x8c

    IDirectPlay8Client* GetClient();
    long GetConnectResult();
    void SetGUID(_GUID& guid);
    static unsigned long GetLastMsgTimestamp();
    static unsigned long GetLinkQuality();
    static void SetSourcePort(unsigned long port);
    static bool IsPingOutstanding();
    void CancelEnums();
    void Cleanup();
    void Close();

private:
    static unsigned long m_dwLastMsgReceivedTime;
    static unsigned long m_dwLinkQuality;
    static unsigned long m_dwSourcePort;
    static unsigned long m_dwPingReceiveCount;
    static unsigned long m_dwPingSendCount;
};

#endif // DALIB_H
