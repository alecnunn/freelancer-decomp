// DALib.dll -- IDPMsgHandler: abstract callback interface for DirectPlay
// receive/disconnect events. The base has no data, so its methods are trivial
// (vptr-only ctors, identity operator=, empty virtual callbacks).
#include "DALib.h"

IDPMsgHandler::IDPMsgHandler() {}

IDPMsgHandler::IDPMsgHandler(const IDPMsgHandler&) {}

IDPMsgHandler& IDPMsgHandler::operator=(const IDPMsgHandler&) {
    return *this;
}

void IDPMsgHandler::OnReceive(unsigned char*, unsigned long) {}

void IDPMsgHandler::OnDisconnect() {}
