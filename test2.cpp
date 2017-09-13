
#include <iostream>

#include "type.hpp"

#include "tuple.hpp"

using Type::Int;
using namespace Tuple;

template <typename A, typename B> struct Test
{
    static const int value = A::value + B::value;
};

typedef Int<3> I;

template <typename T> using Test1 = Test<I, T>;

template <typename ...Ts> using Test2 = Test<I, Ts...>;

template <typename T, typename ...Ts> using Test3 = Test<T, Ts...>;

typedef CALLBACK(Test) _Test;

typedef CURRY2(_Test, I) P3;

//typedef APPLY2(CALLBACK(TEST), I) _P3;

int main()
{
    std::cout << P3::Call<Int<4> >::value << std::endl;
};
