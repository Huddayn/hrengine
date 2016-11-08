/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_math_matrix_h
#define aw_math_matrix_h
#include <aw/math/vector.h>
namespace aw {
namespace math {
template<typename T, size_t M, size_t N>
struct matrix;

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N>& row(matrix<T,M,N>& mat);
template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N> const& row(matrix<T,M,N> const& mat);

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,M> col(matrix<T,M,N> const& mat);

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T& get(matrix<T,M,N>& mat);
template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N> const& mat);

template<class MatrixT,
         class = typename MatrixT::row_indices,
         class = typename MatrixT::column_indices
>
struct matrix_ops;

template<class T, size_t M, size_t N, size_t...Is, size_t...Js>
struct matrix_ops<matrix<T,M,N>, index_sequence<Is...>, index_sequence<Js...>>
{
	using MatrixT = matrix<T,M,N>;
	using column_type = typename MatrixT::column_type;

	static constexpr void set(MatrixT& a, MatrixT const& b)
	{
		(void(a[Is] = b[Is]), ...);
	}

	static constexpr void add(MatrixT& a, MatrixT const& b)
	{
		(void(a[Is] += b[Is]), ...);
	}

	static constexpr void sub(MatrixT& a, MatrixT const& b)
	{
		(void(a[Is] -= b[Is]), ...);
	}

	static constexpr void mul(MatrixT& a, T const v)
	{
		(void(a[Is] *= v), ...);
	}

	static constexpr void div(MatrixT& a, T const v)
	{
		(void(a[Is] /= v), ...);
	}

	static constexpr vector<T,M> mul(MatrixT const& mat, vector<T,N> const& vec)
	{
		return { dot(mat.row(Is), vec) ... };
	}

	static constexpr vector<T,N> mul(vector<T,M> const& vec, MatrixT const& mat)
	{
		return { dot(mat.col(Js), vec) ... };
	}

	template <size_t P>
	static constexpr matrix<T,M,P> mul(MatrixT const& A, matrix<T,N,P> const& B)
	{
		return { A.row(Is) * B ... };
	}

	static constexpr column_type col(MatrixT const& a, size_t j)
	{
		return { row<Is>(a)[j]... };
	}

	static constexpr MatrixT transpose(matrix<T,M,N> const& mat)
	{
		return { col<Js>(mat)... };
	}

	template<typename Func>
	static constexpr void for_each_column(matrix<T,M,N>& mat, Func func)
	{
		(void(func(mat[Js])), ...);
	}

	template<typename Func>
	static constexpr void for_each_row(matrix<T,M,N>& mat, Func func)
	{
		(void(func(mat[Is])), ...);
	}

	template<typename Func>
	static constexpr void for_each(matrix<T,M,N>& mat, Func func)
	{
		(mat[Is].for_each(func), ...);
	}
};

template<typename T, size_t M, size_t N>
struct matrix {
	constexpr static size_t num_columns = N;
	constexpr static size_t num_rows = M;

	static_assert(num_columns > 0, "Matrix must have at least one column.");
	static_assert(num_rows > 0, "Matrix must have at least one row.");

	using row_indices    = make_index_sequence<M>;
	using column_indices = make_index_sequence<N>;

	using value_type = T;
	using column_type = vector<T, M>;
	using row_type    = vector<T, N>;

	row_type rows[M];

	constexpr matrix& operator=(matrix const& other)
	{
		matrix_ops<matrix>::set(*this, other);
		return *this;
	}

	constexpr row_type const& operator[](size_t idx) const
	{
		return rows[idx];
	}

	constexpr row_type& operator[](size_t idx)
	{
		return rows[idx];
	}

	constexpr matrix& operator+=(matrix const& other)
	{
		matrix_ops<matrix>::add(*this, other);
		return *this;
	}


	constexpr matrix& operator-=(matrix const& other)
	{
		matrix_ops<matrix>::sub(*this, other);
		return *this;
	}

	constexpr matrix& operator*=(T const v)
	{
		matrix_ops<matrix>::mul(*this, v);
		return *this;
	}

	constexpr matrix& operator /= (T const v)
	{
		matrix_ops<matrix>::div(*this, v);
		return *this;
	}

	template<typename Func>
	constexpr void for_each_column(Func func)
	{
		matrix_ops<matrix>::for_each_column(*this, func);
	}

	template<typename Func>
	constexpr void for_each_row(Func func)
	{
		matrix_ops<matrix>::for_each_row(*this, func);
	}

	template<typename Func>
	constexpr void for_each(Func func)
	{
		matrix_ops<matrix>::for_each(*this, func);
	}

	constexpr T& get(size_t i, size_t j)
	{
		return rows[i][j];
	}

	constexpr T get(size_t i, size_t j) const
	{
		assert(i < M);
		assert(j < N);

		return rows[i][j];
	}

	constexpr row_type& row(size_t i)
	{
		assert(i < M);
		return rows[i];
	}

	constexpr row_type const& row(size_t i) const
	{
		assert(i < M);
		return rows[i];
	}

	constexpr column_type col(size_t j) const
	{
		return matrix_ops<matrix>::col(*this, j);
	}
};

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T get(matrix<T,M,N> const& mat)
{
	return mat.rows[I][J];
}

template<size_t I, size_t J, typename T, size_t M, size_t N>
constexpr T& get(matrix<T,M,N>& mat)
{
	return mat.rows[I][J];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N>& row(matrix<T,M,N>& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,N> const& row(matrix<T,M,N> const& mat)
{
	return mat.rows[Index];
}

template<size_t Index, typename T, size_t M, size_t N>
constexpr vector<T,M> col(matrix<T,M,N> const& mat)
{
	using MatrixT = matrix<T,M,N>;
	return matrix_ops<MatrixT>::row(mat, Index);
}

namespace _impl {
template<size_t Col, size_t... Rows, typename T, size_t M, size_t N>
constexpr matrix<T,N-1,M-1> make_sub(matrix<T,M,N> const& mat, index_sequence<Rows...>)
{
	return { sub<Col>(row<Rows>(mat))... };
}
} // namespace _impl

template<size_t Row, size_t Col, typename T, size_t M, size_t N>
constexpr matrix<T,N-1,M-1> sub_matrix(matrix<T,M,N> const& mat)
{
	auto range = index_cat<
	        make_index_range<0,Row>,
	        make_index_range<Row+1,N>
	>{};

	return _impl::make_sub<Col>(mat,range);
}

//! Transpose a matrix
template<typename T, size_t M, size_t N>
constexpr matrix<T,N,M> transpose(matrix<T,M,N> const& mat)
{
	using MatrixT = matrix<T,M,N>;
	return matrix_ops<MatrixT>::transpose(mat);
}

template<typename T, size_t M, size_t N>
constexpr vector<T,M> operator*(matrix<T,M,N> const& A, vector<T,N> const& B)
{
	using MatrixT = matrix<T,M,N>;
	return matrix_ops<MatrixT>::mul(A, B);
}

template<typename T, size_t M, size_t N>
constexpr vector<T,N> operator*(vector<T,M> const& vec, matrix<T,M,N> const& mat)
{
	using MatrixT = matrix<T,M,N>;
	return matrix_ops<MatrixT>::mul(vec, mat);
}

template<typename T, size_t M, size_t N, size_t P>
constexpr matrix<T,M,P> operator*(matrix<T,M,N> const& A, matrix<T,N,P> const& B)
{
	using MatrixT = matrix<T,M,N>;
	return matrix_ops<MatrixT>::mul(A, B);
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator*(matrix<T,N,M> mat, T const v)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator*(T const v, matrix<T,N,M> mat)
{
	mat *= v;
	return mat;
}

template<typename T, size_t M, size_t N>
constexpr matrix<T,M,N> operator/(matrix<T,N,M> mat, T const v)
{
	mat /= v;
	return mat;
}

template<typename T, size_t M, size_t N>
void fill(matrix<T,M,N>& mat, T const value)
{
	vector<T,N> row = {};
	fill(row, value);
	std::fill(std::begin(mat.rows), std::end(mat.rows), row);
}
} // namespace math
} // namespace aw

#include "bits/square_matrix.h"
#endif//aw_math_matrix_h
