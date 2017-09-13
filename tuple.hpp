#ifndef __TUPLE_HPP__
#define __TUPLE_HPP__

#include <iostream>

#include "type.hpp"
#include "if.hpp"



#define CALLBACK(type) \
    struct { template <typename ...__As__> using Call = type<__As__...>; }

#define COMPOSE(t1, t2) \
    struct { template <typename ...__As__> using Call = typename t1::template Call<typename t2::template Call<__As__...>::Result >; }

#define FLIP(type) \
    struct { template <typename __A__, typename __B__, typename ...__Cs__> using Call = typename ::Tuple::ApplyTuple<type, ::Tuple::Tuple<__B__, __A__, __Cs__...> >::Result; }


#define CURRY(type, arg) \
    struct { template <typename ...__As__> using Call = typename ::Tuple::ApplyTuple<type, ::Tuple::Tuple<arg, __As__...> >::Result; }

#define CURRY2(type, arg) \
    struct { template <typename __A__, typename ...__Bs__> using Call = typename ::Tuple::ApplyTuple<type, ::Tuple::Tuple<__A__, arg, __Bs__...> >::Result; }

#define CURRY3(type, arg) \
    struct { template <typename __A__, typename __B__, typename ...__Cs__> using Call = typename ::Tuple::ApplyTuple<type, ::Tuple::Tuple<__A__, __B__, arg, __Cs__...> >::Result; }


namespace Tuple
{

    using namespace Type;

    /* forward declaration */
    template <typename ...Ts> struct Tuple;

    /***************************************************************/
    /* common member functions */
    template <typename ...Ts> struct __Tuple {};
    template <> struct __Tuple<>
    {
        static void print(std::ostream &stream = std::cout)
        {
            stream << "()";
        };
    };
    template <typename T, typename ...Ts> struct __Tuple<T, Ts...>
    {
        typedef T First;
        typedef Tuple<Ts...> Next;

        static void print(std::ostream &stream = std::cout)
        {
            T::print(stream);
            stream << ":";
            __Tuple<Ts...>::print(stream);
        }
    };
    /***************************************************************/

    /***************************************************************/
    /* partial specializations */
    template <typename ...Ts> struct Tuple 
        : public __Tuple<Ts...>
    {};
    typedef Tuple<> Nil;
    template <typename T1> struct Tuple<T1> 
        : public __Tuple<T1>
    {
        typedef T1 First;
        static void print(std::ostream &stream = std::cout)
        {
            stream << "(";
            First::print(stream);
            stream << ")";
        };
    };
    template <typename T1> using OneTuple = Tuple<T1>;

    template <typename T1, typename T2> struct Tuple<T1, T2> 
        : public __Tuple<T1, T2>
    {
        typedef T1 First;
        typedef T2 Second;
        static void print(std::ostream &stream = std::cout)
        {
            stream << "(";
            T1::print(stream);
            stream << ",";
            T2::print(stream);
            stream << ")";
        };
    };
    template <typename T1, typename T2> using TwoTuple = Tuple<T1, T2>;

    template <typename T1, typename T2, typename T3> struct Tuple<T1, T2, T3>
        : public __Tuple<T1, T2, T3>
    {
        typedef T1 First;
        typedef T2 Second;
        typedef T3 Third;
        static void print(std::ostream &stream = std::cout)
        {
            stream << "(";
            T1::print(stream);
            stream << ",";
            T2::print(stream);
            stream << ",";
            T3::print(stream);
            stream << ")";
        };
    };
    template <typename T1, typename T2, typename T3> using ThreeTuple = Tuple<T1, T2, T3>;

    template <typename T1, typename T2, typename T3, typename T4> struct Tuple<T1, T2, T3, T4>
        : public __Tuple<T1, T2, T3, T4>
    {
        typedef T1 First;
        typedef T2 Second;
        typedef T3 Third;
        typedef T4 Fourth;
    };
    template <typename T1, typename T2, typename T3, typename T4> using FourTuple = Tuple<T1, T2, T3, T4>;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename _Tuple> struct ApplyTuple {};
    template <typename _Callback, typename ...Ts> struct ApplyTuple<_Callback, Tuple<Ts...> >
    {
        typedef typename _Callback::template Call<Ts...> Result;
    };
    /***************************************************************/

    /***************************************************************/
    template <typename T, typename _Tuple = Nil> struct Prepend 
    {
        typedef Tuple<T> Result;
    };
    template <typename T, typename ...Ts> struct Prepend<T, Tuple<Ts...> >
    {
        typedef Tuple<T, Ts...> Result;
    };
    typedef CALLBACK(Prepend) prepend;
    /***************************************************************/

    /***************************************************************/
    template <typename V, typename _Tuple = Nil> struct Append
    {
        typedef Tuple<V> Result;
    };
    template <typename V, typename T, typename ...Ts> struct Append<V, Tuple<T, Ts...> >
    {
        typedef typename Prepend<T, typename Append<V, Tuple<Ts...> >::Result>::Result Result;
    };
    typedef CALLBACK(Append) append;
    /***************************************************************/


    /***************************************************************/
    template <typename T1, typename T2> struct Concat 
    {
        typedef typename Prepend<
            typename T1::First, 
            typename Concat<typename T1::Next, T2>::Result
        >::Result Result;
    };
    template <typename T2> struct Concat<Nil, T2>
    {
        typedef T2 Result;
    };
    typedef CALLBACK(Concat) concat;
    /***************************************************************/


    /***************************************************************/
    template <typename _Type, _Type ...Ts> struct TypeTuple
    {
        typedef Nil Result;
    };
    template <typename _Type, _Type T, _Type ...Ts> struct TypeTuple<_Type, T, Ts...>
    {
        typedef typename Prepend<Type<_Type, T>, typename TypeTuple<_Type, Ts...>::Result>::Result Result;
    };
    template <int... Ns> using IntTuple = TypeTuple<int, Ns...>;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename Acc, typename Tuple = Nil> struct Foldr
    {
        typedef Acc Result;
    };
    template <typename _Callback, typename Acc, typename T, typename ...Ts>
        struct Foldr<_Callback, Acc, Tuple<T, Ts...> >
    {
        typedef typename _Callback::template Call<
            T,
            typename Foldr<_Callback, Acc, Tuple<Ts...> >::Result
        >::Result Result;
    };
    typedef CALLBACK(Foldr) foldr;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename Acc, typename _Tuple = Nil> struct Foldl
    {
        typedef Acc Result;
    };
    template <typename _Callback, typename Acc, typename T, typename ...Ts> 
        struct Foldl<_Callback, Acc, Tuple<T, Ts...> >
    {
        typedef typename Foldl<
            _Callback,
            typename _Callback::template Call<Acc, T>::Result,
            Tuple<Ts...> 
        >::Result Result;
    };
    typedef CALLBACK(Foldl) foldl;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename Tuple = Nil> struct FMap
    {
        typedef Nil Result;
    };
    template <typename _Callback, typename T, typename ...Ts> struct FMap<_Callback, Tuple<T, Ts...> >
    {
        typedef typename Prepend<
            typename _Callback::template Call<T>::Result, 
            typename FMap<_Callback, Tuple<Ts...> >::Result
        >::Result Result;
    };
    typedef CALLBACK(FMap) fmap;
    /***************************************************************/

    /***************************************************************/
    template <typename _Tuple = Nil> struct Reverse
    {
        typedef CALLBACK(Prepend) _Prepend;
        typedef FLIP(_Prepend) _FP;
        typedef typename Foldl<_FP, Nil, _Tuple>::Result Result;
    };
    typedef CALLBACK(Reverse) reverse;
    /***************************************************************/


    /***************************************************************/
    template <typename _Callback, typename _Tuple = Nil> struct Split
    {
        typedef struct {
            template <typename T, typename Acc> struct Call {
                typedef typename Acc::First Tr;
                typedef typename Acc::Second Fa;
                typedef typename If<_Callback::template Call<T>::value,
                    TwoTuple<typename Prepend<T, Tr>::Result, Fa>,
                    TwoTuple<Tr, typename Prepend<T, Fa>::Result> 
                >::Result Result;
            };
        } CB;
        typedef typename Foldr<CB, TwoTuple<Nil, Nil>, _Tuple>::Result Result;
    };
    typedef CALLBACK(Split) split;
    /***************************************************************/

    /***************************************************************/
    template <typename _LessThan, typename _Tuple = Nil> struct Quicksort
    {
        typedef Nil Result;
    };
    template <typename _LessThan, typename T, typename ...Ts> struct Quicksort<_LessThan, Tuple<T, Ts...> >
    {
        typedef CURRY2(_LessThan, T) _LessThanHead;
        typedef typename Split<_LessThanHead, Tuple<Ts...> >::Result S;
        typedef typename Concat<
            typename Quicksort<_LessThan, typename S::First>::Result,
            typename Prepend<
                T, 
                typename Quicksort<_LessThan, typename S::Second>::Result
            >::Result
        >::Result Result;
    };
    typedef CALLBACK(Quicksort) quicksort;
    /***************************************************************/

    /* integer list operations */
     
    /***************************************************************/
    template <typename _ITuple = Nil> struct IntQuicksort
    {
        typedef Nil Result;
    };
    template <typename T, typename ...Ts> struct IntQuicksort<Tuple<T, Ts...> >
    {
        struct CB {
            template <typename V> struct Call {
                static const bool value = V::value < T::value;
            };
        };
        typedef typename Split<CB, Tuple<Ts...> >::Result S;
        typedef typename Concat<
            typename IntQuicksort<typename S::First>::Result, 
            typename Prepend<T, typename IntQuicksort<typename S::Second>::Result >::Result 
        >::Result Result;
    };
    typedef CALLBACK(IntQuicksort) intquicksort;
    /***************************************************************/


    /***************************************************************/
    template <int N> struct Descend
    {
        typedef typename Prepend<Int<N-1>, typename Descend<N-1>::Result>::Result Result;
    };
    template <> struct Descend<0>
    {
        typedef Nil Result;
    };
    /***************************************************************/

    /* List-foo */

    /***************************************************************/
    template <typename Outer, typename Inner> struct Nestl
    { 
//        typedef typename Prepend< Tuple<Tuple<typename Outer::First>, Inner>,
//                typename Nest<typename Outer::Next, Inner>::Result >::Result Result;
        typedef CALLBACK(Prepend) _Prepend;
        typedef CURRY2(_Prepend, Tuple<Inner>) CB;
        typedef typename FMap<CB, Outer>::Result Result;
    };
    typedef CALLBACK(Nestl) nestl;
    /***************************************************************/

    /***************************************************************/
    template <typename Inner, typename Outer> struct Nestr
    {
        typedef CALLBACK(Append) _Append;
        typedef CURRY2(_Append, Tuple<Inner>) CB;
        typedef typename FMap<CB, Outer>::Result Result;
    };
    typedef CALLBACK(Nestr) nestr;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename Outer, typename Inner> struct NestlWith
    {
        typedef CURRY2(_Callback, Inner) CB;
        typedef typename FMap<CB, Outer>::Result Result;
    };
    typedef CALLBACK(NestlWith) nestlwith;
    /***************************************************************/

    /***************************************************************/
    template <typename _Callback, typename Inner, typename Outer> struct NestrWith
    {
        typedef CURRY(_Callback, Inner) CB;
        typedef typename FMap<CB, Outer>::Result Result;
    };
    typedef CALLBACK(NestrWith) nestrwith;
    /***************************************************************/

    /***************************************************************/
    template <typename T1 = Nil, typename T2 = Nil> struct Splice
    {
        typedef Nil Result;
    };
    template <typename T, typename ...Ts, typename S, typename ...Ss> struct Splice<Tuple<T, Ts...>, Tuple<S, Ss...> >
    {
        typedef typename Prepend< Tuple<T,S>, typename Splice<Tuple<Ts...>, Tuple<Ss...> >::Result >::Result Result;
    };
    typedef CALLBACK(Splice) splice;
    /***************************************************************/


    /***************************************************************/
    template <typename _Tuple = Nil> struct Flatten
    {
        typedef Nil Result;
    };
    template <typename T, typename ...Ts> struct Flatten<Tuple<T, Ts...> >
    {
        typedef typename Concat<T, typename Flatten<Tuple<Ts...> >::Result>::Result Result;
    };
    typedef CALLBACK(Flatten) flatten;
    /***************************************************************/


    /***************************************************************/
    template <typename T> struct IsTuple
    {
        static const bool value = false;
    };
    template <typename ...Ts> struct IsTuple<Tuple<Ts...> >
    {
        static const bool value = true;
    };
    typedef CALLBACK(IsTuple) istuple;
    /***************************************************************/


//    /***************************************************************/
    template <typename ...Ts> struct Combine {};
    template <typename ...Ts> struct Combine<Tuple<Ts...> >
    {
        typedef Tuple<Ts...> Result;
    };
    template <typename ...Ss, typename _Tuple, typename ...Ts> struct Combine<Tuple<Ss...>, _Tuple, Ts...>
    {
        typedef CURRY(nestrwith, prepend) nestrwithprepend;
        typedef typename Flatten<
            typename NestlWith<
                nestrwithprepend, 
                Tuple<Ss...>, 
                typename Combine<_Tuple, Ts...>::Result 
            >::Result 
        >::Result Result;
    };
    /***************************************************************/

    /***************************************************************/
    template <typename callback, typename ...Ts> struct CombineWith {};
    template <typename callback, typename ...Ts> struct CombineWith<callback, Tuple<Ts...> >
    {
        typedef Tuple<Ts...> Result;
    };
    template <typename callback, typename ...Ss, typename _Tuple, typename ...Ts> struct CombineWith<callback, Tuple<Ss...>, _Tuple, Ts...>
    {
        typedef CURRY(nestrwith, callback) nestrwithcallback;
        typedef typename Flatten<typename NestlWith<nestrwithcallback, Tuple<Ss...>, typename CombineWith<callback, _Tuple, Ts...>::Result >::Result >::Result Result;
    };
    /***************************************************************/
};



#endif
