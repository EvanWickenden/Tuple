#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "tuple.hpp"
#include <iostream>

namespace List
{
    using namespace Tuple;

    /***************************************************************/
    template <typename T> struct ExtractArgs
    {
        typedef typename T::Args Result;
    };
    template <> struct ExtractArgs<char>
    {
        typedef char Result;
    };
    template <> struct ExtractArgs<int>
    {
        typedef int Result;
    };
    template <> struct ExtractArgs<double>
    {
        typedef double Result;
    };
    /***************************************************************/

    /***************************************************************/
    template <typename ...Ts> struct TupleArgs {};
    template <> struct TupleArgs<>
    {
        typedef Nil Result;
    };
    template <typename T, typename ...Ts> struct TupleArgs<T, Ts...>
    {
        typedef typename Prepend<
            typename ExtractArgs<T>::Result,
            typename TupleArgs<Ts...>::Result
        >::Result Result;
    };
    /***************************************************************/

    /***************************************************************/
    template <typename _Head, typename _Tail, typename _ArgTuple> struct __List;
    template <typename _Head, typename _Tail, typename A, typename ...As> struct __List<_Head, _Tail, Tuple<A, As...> > : public Prepend<_Head, _Tail>::Result 
    {
        _Head head;
        _Tail tail;
        __List(A head, As... tail) : head(head), tail(tail...) {}
    };
    /***************************************************************/

    /***************************************************************/
    template <typename ...Ts> struct List : public Tuple<Ts...> 
    {
        typedef List<> L;
        friend std::ostream& operator << (std::ostream& stream, L& l)
        {
            stream << "[]";
            return stream;
        };
    };
    template <typename T, typename ...Ts> struct List<T, Ts...> : public __List<T, List<Ts...>, typename TupleArgs<T, Ts...>::Result>
    {
        typedef List<T, Ts...> L;
        using __List<T, List<Ts...>, typename TupleArgs<T, Ts...>::Result>::__List;

        friend std::ostream& operator << (std::ostream& stream, L& l)
        {
            stream << l.head << ":" << l.tail;
            return stream;
        };
    };
    typedef List<> Empty;
    /***************************************************************/

    /***************************************************************/
    template <typename T = Nil> struct TupleToList 
    {
        typedef Empty Result;
    };
    template <typename ...Ts> struct TupleToList<Tuple<Ts...> >
    {
        typedef List<Ts...> Result;
    };
    /***************************************************************/
};


#endif
