// StateMachineMessage -- base class for messages routed to state machines.
// Recovered from Common.dll; size 0x1c. Polymorphic root class (vptr at +0x00,
// virtual destructor + virtual clone). Symbol-rich unit: these real member
// definitions mangle to the original symbols and objdiff pairs them
// automatically (no claim needed).
//
// Layout (from the ctors / set_delivery_options / clone):
//   +0x00  vptr
//   +0x04  unsigned int  m_message_type
//   +0x08  unsigned int  m_source
//   +0x0c  unsigned int  m_dest
//   +0x10  int           m_scope         (default -1)
//   +0x14  float         m_delivery_time
//   +0x18  bool          m_immediate     (set to false by delivery-option paths)
#include "common.h"
#include <stdlib.h>     // malloc

// Placement new comes from <new> (included via common.h).

class StateMachineMessage {
public:
    unsigned int  m_message_type;   // +0x04
    unsigned int  m_source;         // +0x08
    unsigned int  m_dest;           // +0x0c
    int           m_scope;          // +0x10
    float         m_delivery_time;  // +0x14
    bool          m_immediate;      // +0x18  (class aligns to 0x1c)

    StateMachineMessage();
    StateMachineMessage(unsigned int message_type);
    StateMachineMessage(float delivery_time, unsigned int message_type,
                        unsigned int source, unsigned int dest, int scope);
    StateMachineMessage(const StateMachineMessage& o);
    virtual ~StateMachineMessage();

    virtual StateMachineMessage* clone() const;

    float get_delivery_time() const;
    void set_delivery_options(float delivery_time, unsigned int source,
                              unsigned int dest, int scope);
    bool is_delivered() const;
    void set_sender(unsigned int source);
    void set_receiver(unsigned int dest);

    static unsigned int GenerateUniqueMessageType();

private:
    static unsigned int s_unique_message_type_generator;
};

// ?s_unique_message_type_generator@StateMachineMessage@@0IA  (private static uint)
unsigned int StateMachineMessage::s_unique_message_type_generator;

StateMachineMessage::StateMachineMessage()
    : m_message_type(0), m_source(0), m_dest(0), m_scope(-1),
      m_delivery_time(0.0f), m_immediate(false) {}

StateMachineMessage::StateMachineMessage(unsigned int message_type)
    : m_message_type(message_type), m_source(0), m_dest(0), m_scope(-1),
      m_delivery_time(0.0f), m_immediate(false) {}

StateMachineMessage::StateMachineMessage(float delivery_time, unsigned int message_type,
                                         unsigned int source, unsigned int dest, int scope) {
    m_message_type = message_type;
    m_delivery_time = delivery_time;
    m_source = source;
    m_dest = dest;
    m_scope = scope;
    m_immediate = false;
}

StateMachineMessage::StateMachineMessage(const StateMachineMessage& o)
    : m_message_type(o.m_message_type), m_source(o.m_source), m_dest(o.m_dest),
      m_scope(o.m_scope), m_delivery_time(o.m_delivery_time), m_immediate(o.m_immediate) {}

StateMachineMessage::~StateMachineMessage() {}

StateMachineMessage* StateMachineMessage::clone() const {
    void* p = malloc(sizeof(StateMachineMessage));
    if (p)
        return new (p) StateMachineMessage(*this);
    return 0;
}

float StateMachineMessage::get_delivery_time() const {
    return m_delivery_time;
}

void StateMachineMessage::set_delivery_options(float delivery_time, unsigned int source,
                                               unsigned int dest, int scope) {
    m_delivery_time = delivery_time;
    m_source = source;
    m_dest = dest;
    m_scope = scope;
    m_immediate = false;
}

unsigned int StateMachineMessage::GenerateUniqueMessageType() {
    return ++s_unique_message_type_generator;
}

bool StateMachineMessage::is_delivered() const {
    return m_immediate;
}

void StateMachineMessage::set_sender(unsigned int source) {
    m_source = source;
}

void StateMachineMessage::set_receiver(unsigned int dest) {
    m_dest = dest;
}
