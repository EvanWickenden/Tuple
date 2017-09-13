#ifndef __LIST_HPP__
#define __LIST_HPP__

#include "tuple.hpp"
#include <iostream>

namespace List
{
    using namespace Tuple;

    /* helper fns */
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
    template <> struct ExtractArgs<long>
    {
        typedef long Result;
    };
    template <> struct ExtractArgs<float>
    {
        typedef float Result;
    };
    template <> struct ExtractArgs<double>
    {
        typedef double Result;
    };
    template <typename T> struct ExtractArgs<T *>
    {
        typedef T * Result;
    };
    template <typename T> struct ExtractArgs<T&>
    {
        typedef T & Result;
    };
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

    /* forward declaration */
    template <typename ...Ts> struct List;

    /* base class manufacturer */
    /***************************************************************/
    template <typename _Head, typename _Tail, typename _ArgTuple> struct __BaseList;
    template <typename _Head, typename _Tail, typename A, typename ...As> struct __BaseList<_Head, _Tail, Tuple<A, As...> > : public Prepend<_Head, _Tail>::Result 
    {
        _Head head;
        _Tail tail;
        __BaseList(A head, As... tail) : head(head), tail(tail...) {}
    };
    /***************************************************************/


    /* base class */
    /***************************************************************/
    template <typename ...Ts> struct BaseList : public Tuple<Ts...> 
    {
        typedef BaseList<> BL;
        static const int size = 0;
        friend std::ostream& operator << (std::ostream& stream, BL& l)
        {
            stream << "[]";
            return stream;
        };
    };
    template <typename T, typename ...Ts> struct BaseList<T, Ts...> : public __BaseList<T, List<Ts...>, typename TupleArgs<T, Ts...>::Result>
    {
        static const int size = 1 + BaseList<Ts...>::size;
        typedef BaseList<T, Ts...> BL;
        using __BaseList<T, List<Ts...>, typename TupleArgs<T, Ts...>::Result>::__BaseList;

        friend std::ostream& operator << (std::ostream& stream, BL& l)
        {
            BaseList<Ts...>& tail = l.tail;
            stream << l.head << ":" << tail;
            return stream;
        };
    };
    /***************************************************************/

    /* main class; partial specializations */
    /***************************************************************/

#define ARGS(type)  typename ExtractArgs<type>::Result 

    /* polymorphic declaration */
    template <typename ...Ts> struct List : public BaseList<Ts...> 
    {
        using BaseList<Ts...>::BaseList;
    };

    /* fixed-size specializations & typedefs */
    typedef List<> Empty;

    template <typename A> struct List<A> : public BaseList<A>
    { 
        typedef List<A> L;
        typedef BaseList<A> BL;
        A& one;
        List(ARGS(A) one) : BL(one), one(BL::head) {}
    };
    template <typename T> using OneList = List<T>;
    
    template <typename A, typename B> struct List<A, B> : public BaseList<A, B>
    {
        typedef List<A, B> L;
        typedef BaseList<A, B> BL;
        A& one; B& two;
        List(ARGS(A) one, ARGS(B) two) : BL(one, two), one(BL::head), two(BL::tail.head) {}
        friend std::ostream& operator << (std::ostream& stream, L& l)
        {
            stream << "[" << l.one << ", " << l.two << "]";
            return stream;
        };
    };
    template <typename A, typename B> using TwoList = List<A, B>;

    template <typename A, typename B, typename C> struct List<A, B, C> : public BaseList<A, B, C>
    {
        typedef List<A, B, C> L;
        typedef BaseList<A, B, C> BL;
        A& one; B& two; C& three;
        List(ARGS(A) one, ARGS(B) two, ARGS(C) three) : BL(one, two, three), one(BL::head), two(BL::tail.head), three(BL::tail.tail.head) {}
        friend std::ostream& operator << (std::ostream& stream, L& l)
        {
            stream << "[" << l.one << ", " << l.two << ", " << l.three << "]";
            return stream;
        };
    };
    template <typename A, typename B> using TwoList = List<A, B>;
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
