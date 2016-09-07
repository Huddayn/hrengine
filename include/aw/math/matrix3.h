/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix3_h
#define aw_math_matrix3_h
#include <aw/math/vector3d.h>
#include <aw/math/Quaternion.h>
#include <aw/math/matrix.h>
namespace aw {
namespace math {
template<typename T>
using matrix3 = matrix<T,3,3>;

//! Extract scale from matrix
template<typename T>
vector3d<T> scale(matrix3<T> const& mat)
{
	auto const row1 = row<0>(mat);
	auto const row2 = row<1>(mat);
	auto const row3 = row<2>(mat);

	T const det = determinant(mat);

	T const scaleX = det > 0 ? row1[0].length() : -row1[0].length();
	T const scaleY = row2[1].length();
	T const scaleZ = row3[2].length();

	return {scaleX, scaleY, scaleZ};
}

//! Extract scale, assuming it is positive
template<typename T>
vector3d<T> scale_positive(matrix3<T> const& mat)
{
	auto const row1 = row<0>(mat);
	auto const row2 = row<1>(mat);
	auto const row3 = row<2>(mat);

	T const scaleX = row1[0].length();
	T const scaleY = row2[1].length();
	T const scaleZ = row3[2].length();

	return { scaleX, scaleY, scaleZ };
}

//! Convert rotation matrix to quaternion
template<typename T>
Quaternion<T> as_quaternion(matrix3<T> const& mat)
{
	Quaternion<T> quat = {};

	quat.w = sqrt(max(0, 1 + get<0,0>(mat) + get<1,1>(mat) + get<2,2>(mat))) / 2;
	quat.x = sqrt(max(0, 1 + get<0,0>(mat) - get<1,1>(mat) - get<2,2>(mat))) / 2;
	quat.y = sqrt(max(0, 1 - get<0,0>(mat) + get<1,1>(mat) - get<2,2>(mat))) / 2;
	quat.z = sqrt(max(0, 1 - get<0,0>(mat) - get<1,1>(mat) + get<2,2>(mat))) / 2;

	quat.x = std::copysign(quat.x, get<2,1> - get<1,2>(mat));
	quat.y = std::copysign(quat.y, get<0,2> - get<2,0>(mat));
	quat.z = std::copysign(quat.z, get<1,0> - get<0,1>(mat));

	return quat;
}

//! Convert matrix to quaternion
template<typename T>
Quaternion<T> as_quaternion_scaled(matrix3<T> const& mat)
{
	Quaternion<T> quat;

	T const det = pow(determinant(mat), 1/3);

	quat.w = sqrt(max(0, det + get<0,0>(mat) + get<1,1>(mat) + get<2,2>(mat)))/2;
	quat.x = sqrt(max(0, det + get<0,0>(mat) - get<1,1>(mat) - get<2,2>(mat)))/2;
	quat.y = sqrt(max(0, det - get<0,0>(mat) + get<1,1>(mat) - get<2,2>(mat)))/2;
	quat.z = sqrt(max(0, det - get<0,0>(mat) - get<1,1>(mat) + get<2,2>(mat)))/2;

	quat.x = std::copysign(quat.x, get<2,1>(mat) - get<1,2>(mat));
	quat.y = std::copysign(quat.y, get<0,2>(mat) - get<2,0>(mat));
	quat.z = std::copysign(quat.z, get<1,0>(mat) - get<0,1>(mat));

	return quat;
}
} // namespace math
} // namespace aw
#endif //aw_math_matrix3_h