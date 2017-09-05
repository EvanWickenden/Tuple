
#include <iostream>

#include "tuple.hpp"
#include "type.hpp"

using namespace Tuple;
using namespace Type;

using std::cout;
using std::endl;

#define BR cout << endl

template <typename A, typename B> struct LessThan {
    static const bool value = A::value < B::value;
};
typedef CALLBACK(LessThan) _LessThan;

int main()
{
    typedef IntTuple<0,1,2,3,4,5,6,7>::Result T1;
    T1::print(); BR;

    typedef Prepend<Int<8>, T1>::Result T2;
    T2::print(); BR;

    typedef Quicksort<_LessThan, T2>::Result T3;
    T3::print(); BR;

    typedef Concat<T3, T3>::Result T32;
    T32::print(); BR;

    typedef Quicksort<_LessThan, T32>::Result T4;
    T4::print(); BR;

    BR;

    typedef Descend<2>::Result D1;
    D1::print(); BR;

    typedef Reverse<D1>::Result A1;
    A1::print(); BR; 

    BR; BR;
    typedef Combine<D1>::Result D2;
    D2::print(); BR;

    typedef Combine<D1, D2>::Result D3;
    D3::print(); BR;

    typedef Combine<D1, D1, D1, D1>::Result D4;
    D4::print(); BR;
};
