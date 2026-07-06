// Reputation::Vibe -- NOT a class. `Vibe` is a namespace nested in `Reputation`;
// every method mangles `YA` (a __cdecl free function, no `this`). There is no
// per-instance struct to recover.
//
// All functions operate on one anonymous, zero-initialized global container
// object spanning 0x64018b4..0x64018d8 (base 0x6200000):
//   0x64018b8 / 0x64018bc : begin / end pointers of a 56-byte-element (0x38)
//                           dynamic array  -> (end-begin)/0x38 == dynamic count
//   0x64018c4             : an associative container (map/list) head
//   0x64018c8             : container sentinel/head node
//   0x64018d4             : base (static-entry) count, added to the dynamic count
//   0x64018d8             : last-lookup cache pointer
//
// None of these globals carry a symbol name in the delinked binary (they render
// as [__delink_ida_data_start+0x...] anonymous data), so there is no C++ symbol
// to bind an `extern` to and no way to reproduce their relocations from source.
// Consequently NOTHING in this namespace is matchable in the simple pass:
//
//   * Count() is pure arithmetic but reads three anonymous data globals with no
//     nameable symbol -> its data relocations cannot be reproduced.
//   * Every other function additionally uses loops, SEH, and external template
//     helpers (std::map/list/vector, FmtStr, CacheString containers) -> deferred
//     per the codegen rules (calls other functions / loops / >10 insns).
//
// This file is intentionally an empty translation unit until the global vibe
// container type and its symbol are modeled (a common.h-level effort shared by
// the whole namespace), at which point these can be implemented together.
#include "common.h"
