#ifndef _TypeList_H
#define _TypeList_H

class NullType
{};

class EmptyType
{};

#define TYPELIST_1(T1) TypeList<T1, NullType>
#define TYPELIST_2(T1,T2) TypeList<T1, TYPELIST_1(T2) >

template < typename T, typename U >
struct TypeList
{

};
#endif;