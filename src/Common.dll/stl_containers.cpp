// STL container instantiations over POINTER element types. Copying a pointer
// is a trivial mov, so these sidestep the Dinkumware _Construct element-copy
// outlining cap that limits value-element containers -- the period-correct
// headers emit byte-matching code for the full method set.
#include "common.h"
#include <vector>
#include <list>

// Pointer elements: only a forward declaration is needed (the element is never
// dereferenced by the container). Must be `struct` to mangle as PAU...@@.
struct IObjInspect;

template class std::vector<IObjInspect*>;
