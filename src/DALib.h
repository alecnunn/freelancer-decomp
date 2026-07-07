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

#endif // DALIB_H
