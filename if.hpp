#ifndef __IF_HPP__
#define __IF_HPP__

template <bool Cond, typename Tr, typename Fa> struct If
{};
template <typename Tr, typename Fa> struct If<true, Tr, Fa>
{
    typedef Tr Result;
};
template <typename Tr, typename Fa> struct If<false, Tr, Fa>
{
    typedef Fa Result;
};

#endif
