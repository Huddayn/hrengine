/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_common_prefix_length_h
#define aw_algorithm_common_prefix_length_h
#include <cassert>
#include <algorithm>
#include <aw/types/traits/iterator.h>
namespace aw {
/*!
 * Calculate length of common prefix for a set of containers,
 * defined by range [first, last).
 */
template <typename Iterator>
size_t common_prefix_length(Iterator first, Iterator last)
{
	static_assert(is_input_iterator<Iterator>, "");
	if (first == last)
		return 0;

	auto a_first = std::begin(*first);
	auto a_last  = std::end(*first);
	while (++first != last) {
		auto b_first = std::begin(*first);
		auto b_last  = std::end(*first);
		a_last = std::mismatch( a_first, a_last, b_first, b_last ).first;
		if (a_first == a_last)
			break;
	}

	auto dist = std::distance(a_first, a_last);
	assert(dist >= 0);
	return size_t(dist);
}

/*!
 * Same as previous overload, but allows to specify initial prefix length.
 */
template <typename Iterator>
size_t common_prefix_length(Iterator first, Iterator last, size_t start_at)
{
	static_assert(is_forward_iterator<Iterator>, "");
	if (first == last)
		return 0;

	auto a_first = std::begin(*first);
	auto a_last  = std::end(*first);

	assert(size_t(std::distance(a_first, a_last)) >= start_at);
	std::advance(a_first, start_at);

	while (++first != last) {
		auto b_first = std::begin(*first);
		auto b_last  = std::end(*first);

		assert(std::distance(b_first, b_last) >= start_at);
		std::advance(b_first, start_at);

		a_last = std::mismatch( a_first, a_last, b_first, b_last ).first;
		if (a_first == a_last)
			break;
	}

	auto dist = std::distance(a_first, a_last);
	assert(dist >= 0);
	return size_t(dist) + start_at;
}
} // namespace aw
#endif//aw_algorithm_common_prefix_length_h
