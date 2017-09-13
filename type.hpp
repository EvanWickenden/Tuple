#ifndef __TYPE_HPP__
#define __TYPE_HPP__

#include <iostream>

namespace Type 
{
    /* common members */
    template <typename _Type, _Type T> struct __Type
    {
        static const _Type value = T;
        static void print(std::ostream &stream = std::cout)
        {
            stream << value;
        };
    };

    /* base struct */
    template <typename _Type, _Type T> struct Type : public __Type<_Type, T> { };

    template <int N> using Int = Type<int, N>;

    struct False { static const bool value = false; };
    struct True { static const bool value = true; };
}

#endif 
