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

protected:
    void Transform(unsigned char* block);
    void Encode(unsigned char* output, unsigned int* input, unsigned int len);
    void Decode(unsigned int* output, unsigned char* input, unsigned int len);
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

// --- DirectPlay / Gun interfaces (opaque; only their pointer types matter) ---
struct IDirectPlay8Client;
struct IGunHost;
struct IGunBrowser;
struct IGunConnection {
    enum ConnectStatus { CS_NONE };
};

// CGunWrapper -- wraps a "Gun" (GameSpy) host + browser connection.
class CGunWrapper {
public:
    unsigned char                 _pad_0[0x10];   // +0x00
    IGunHost*                     m_host;         // +0x10
    IGunBrowser*                  m_browser;      // +0x14
    IGunConnection::ConnectStatus m_status;       // +0x18

    IGunHost* GetHost();
    IGunBrowser* GetBrowser();
    IGunConnection::ConnectStatus GetStatus();
};

// CDPMsgList -- thread-safe received-message queue (critical section @0x10).
class CDPMsgList {
public:
    unsigned char    _pad_0[0x10];   // +0x00
    CRITICAL_SECTION m_cs;           // +0x10

    void Lock();
    void Unlock();
};

// CDPClient -- DirectPlay8 client wrapper (m_client @0x04).
class CDPClient {
public:
    unsigned char        _pad_0[0x04];  // +0x00 (vptr)
    IDirectPlay8Client*  m_client;      // +0x04

    IDirectPlay8Client* GetClient();
    static unsigned long GetLastMsgTimestamp();

private:
    static unsigned long m_dwLastMsgReceivedTime;
};

#endif // DALIB_H
