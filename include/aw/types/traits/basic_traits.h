/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_basic_traits
#define aw_traits_basic_traits
#include <string>
#include <utility>
#include <type_traits>
#include <aw/types/traits/void_t.h>
namespace aw {
template<typename T>
constexpr auto is_arithmetic = std::is_arithmetic<T>::value;

template<typename T>
constexpr auto is_polymorphic = std::is_polymorphic<T>::value;
template<typename T>
constexpr auto is_abstract = std::is_abstract<T>::value;

template<typename T>
constexpr auto is_trivially_copyable = std::is_trivially_copyable<T>::value;

template<class Base, class Derived>
constexpr auto is_base_of = std::is_base_of<Base,Derived>::value;

template<class A, class B>
constexpr auto is_same = std::is_same<A,B>::value;

namespace _impl {
template<typename T>
struct is_int : std::integral_constant<
	bool,
	std::is_integral<T>::value
> { };
template<>
struct is_int<bool> : std::false_type { };

template<typename>
struct is_string : std::false_type{ };
template<class CharT, class Traits, class Alloc>
struct is_string<std::basic_string<CharT, Traits, Alloc>> : std::true_type{ };
} // namespace impl

/* Basic type categories (yes, std::string is considered “basic”) */
template<typename T>
constexpr auto is_int       = _impl::is_int<T>::value;
template<typename T>
constexpr auto is_float     = std::is_floating_point<T>::value;
template<typename T>
constexpr auto is_string    = _impl::is_string<T>::value;
template<typename T>
constexpr auto is_bool      = std::is_same<T, bool>::value;
template<typename T>
constexpr auto is_pointer   = std::is_pointer<T>::value;
} // namespace aw
#endif//aw_traits_basic_traits
