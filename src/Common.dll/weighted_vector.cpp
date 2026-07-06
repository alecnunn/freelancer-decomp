// weighted_vector<T> -- a dynamic array of (value, weight) pairs supporting
// weighted random selection (Pick). Instantiated in this binary as
// weighted_vector<unsigned int>.
//
// Symbol-rich unit: the template members mangle to the original symbols and
// objdiff pairs them automatically -- no claim needed.
//
// Layout (size 0x10): a single std::vector<std::pair<T,float> > member at
// offset 0. VC6 std::vector is { _A allocator @0; pointer _First @4, _Last @8,
// _End @0xc }, matching the field accesses seen in every method.
//
// Implemented here: the default ctor and GetSumOfWeights (both clean), plus the
// compiler-generated copy ctor (??0?$weighted_vector@I@@QAE@ABV0@@Z) which
// inlines std::vector's copy ctor -- emitted via whole-class instantiation.
//
// Deferred (STL-heavy / distinct signature):
//   * operator=(const weighted_vector&)  -- returns a CONST ref (ABV0), so it
//     is user-defined (compiler-gen returns non-const AAV0); inlines vector's
//     4-branch operator=.
//   * ctor / operator= from std::vector<T> const&  -- build pairs, SEH, calls.
//   * Pick()  -- rand()-driven weighted selection, two summation loops.
#include "common.h"
#include <vector>
#include <utility>

template<class T>
class weighted_vector {
public:
    std::vector<std::pair<T, float> > m_items;

    weighted_vector();
    float GetSumOfWeights() const;
};

template<class T>
weighted_vector<T>::weighted_vector() {}

// NOTE: begin/end pointer loads schedule together here (mov eax; mov ecx; fld),
// whereas the original interleaves the fld 0.0 between them (mov eax; fld; mov
// ecx). That is the orthogonal register-scheduling cap -- byte-identical except
// those two adjacent instructions are swapped; /Os does not move them.
template<class T>
float weighted_vector<T>::GetSumOfWeights() const {
    float fSum = 0.0f;
    for (const std::pair<T, float> *p = m_items.begin(); p != m_items.end(); ++p)
        fSum += p->second;
    return fSum;
}

template class weighted_vector<unsigned int>;
