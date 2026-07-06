// std::vector<unsigned short> -- explicit instantiation so its member functions
// (operator[], comparisons, etc.) emit and pair with the original. Uses the
// period-correct MSVC6 Dinkumware <vector>.
#include "common.h"
#include <vector>

template class std::vector<unsigned short>;
