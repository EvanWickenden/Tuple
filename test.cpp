
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

    typedef Descend<10>::Result T4;
    T4::print(); BR;

    typedef Descend<3>::Result D3;
    
    typedef Nest<Descend<3>::Result, Descend<2>::Result >::Result N1;
    N1::print(); BR;

//    typedef FlipNest<D3, D3>::Result N2;
//    N2::print(); BR;

    typedef Combine<Descend<3>::Result, Descend<3>::Result >::Result C1;
    C1::print(); BR;
};
