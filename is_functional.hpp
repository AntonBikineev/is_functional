//  Copyright (c) 2014 Anton Bikineev
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef IS_FUNCTIONAL_HPP
#define IS_FUNCTIONAL_HPP

#include <boost/type_traits/is_class.hpp>
#include <boost/utility/enable_if.hpp>

namespace detail
{

struct is_functional_second_base
{
   void operator()();
};

template <class T>
struct is_functional_composed: T, is_functional_second_base
{
};

template <void (is_functional_second_base::*)()>
struct is_functional_member_func_type
{
};

template <class T, class Func = detail::is_functional_member_func_type<&detail::is_functional_second_base::operator()> >
struct is_functional_trait: boost::true_type
{
};

// &is_functional_composed<T>::operator() is ambiguous when T has T::operator()
// and this partial specialization doesn't take place
template <class T>
struct is_functional_trait<T, detail::is_functional_member_func_type<&detail::is_functional_composed<T>::operator()> >
   : boost::false_type
{
};

template <class T>
struct is_functional_impl
{
   enum { value = detail::is_functional_trait<T>::value };
};

} // namespace detail

template <class T, class T1 = void>
struct is_functional: boost::false_type
{
};

template <class T>
struct is_functional<T, typename boost::enable_if<boost::is_class<T> >::type >
   : public detail::is_functional_impl<T>
{
};

#endif // IS_FUNCTIONAL_HPP
