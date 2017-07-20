//          Copyright Tom Westerhout 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_STATIC_VIEWS_DETAIL_CONFIG_HPP
#define BOOST_STATIC_VIEWS_DETAIL_CONFIG_HPP

#include <exception>
#include <iostream>

#define BOOST_STATIC_VIEWS_FORCEINLINE

#define BOOST_STATIC_VIEWS_NORETURN

#define BOOST_STATIC_VIEWS_LIKELY(expr) expr

#define BOOST_STATIC_VIEWS_CONSTEXPR constexpr
/* Ooops debugging */


#define NEGLECT_STD_TUPLE


#if __cplusplus > 201402L
#define BOOST_CONSTEXPR_AFTER_CXX14 BOOST_STATIC_VIEWS_CONSTEXPR
#else
#define BOOST_CONSTEXPR_AFTER_CXX14
#endif


#if defined(BOOST_CLANG)
#define BOOST_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif


#define BOOST_STATIC_VIEWS_NAMESPACE boost::static_views

#define BOOST_STATIC_VIEWS_BEGIN_NAMESPACE                                                                                                                                                                                                                                                                                     \
  namespace boost                                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    namespace static_views                                                                                                                                                                                                                                                                                                     \
    {

#define BOOST_STATIC_VIEWS_END_NAMESPACE                                                                                                                                                                                                                                                                                       \
  } /* static_views */                                                                                                                                                                                                                                                                                                         \
  } /* boost */


#if defined(DOXYGEN_IN_HOUSE)
#define BOOST_STATIC_VIEWS_NOEXCEPT_IF(...) noexcept(whenever possible) /**/
#else
#define BOOST_STATIC_VIEWS_NOEXCEPT_IF(...) noexcept(__VA_ARGS__) /**/
#endif

#if defined(DOXYGEN_IN_HOUSE)
#define BOOST_STATIC_VIEWS_DECLTYPE_AUTO auto /**/
#else
#define BOOST_STATIC_VIEWS_DECLTYPE_AUTO decltype(auto) /**/
#endif


#if defined(DOXYGEN_IN_HOUSE)
#define BOOST_STATIC_VIEWS_AUTO_RETURN_NOEXCEPT(...)                                                                                                                                                                                                                                                                           \
  noexcept(whenever possible)                                                                                                                                                                                                                                                                                                  \
  {                                                                                                                                                                                                                                                                                                                            \
    return (__VA_ARGS__);                                                                                                                                                                                                                                                                                                      \
  }  \
/**/
#else
// If a function body is just a return-statement, we can deduce the
// noexcept-ness automatically. This idea taken from range-v3.
#define BOOST_STATIC_VIEWS_AUTO_RETURN_NOEXCEPT(...)                                                                                                                                                                                                                                                                           \
  noexcept(noexcept(__VA_ARGS__))                                                                                                                                                                                                                                                                                              \
  {                                                                                                                                                                                                                                                                                                                            \
    return (__VA_ARGS__);                                                                                                                                                                                                                                                                                                      \
  }  \
/**/

#endif


BOOST_STATIC_VIEWS_BEGIN_NAMESPACE

/// \cond
// See http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4381.html
template <class T> constexpr T _static_const{};
/// \endcond


BOOST_STATIC_VIEWS_END_NAMESPACE

#if defined(DOXYGEN_IN_HOUSE)
#define BOOST_STATIC_VIEWS_INLINE_VARIABLE(type, name)                                                                                                                                                                                                                                                                         \
  inline namespace                                                                                                                                                                                                                                                                                                             \
  {                                                                                                                                                                                                                                                                                                                            \
    constexpr auto const &name = ::BOOST_STATIC_VIEWS_NAMESPACE::_static_const<type>;                                                                                                                                                                                                                                          \
  }  \
/**/
#else
#define BOOST_STATIC_VIEWS_INLINE_VARIABLE(type, name)                                                                                                                                                                                                                                                                         \
  constexpr auto name = type{};  \
/**/
#endif


#endif  // BOOST_STATIC_VIEWS_DETAIL_CONFIG_HPP
