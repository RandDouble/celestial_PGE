#pragma once

#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <numeric>

#include <assert.h>


template <class T, class Y> std::vector <T> operator* (const std::vector<T>& v, const  Y& k)
{
	std::vector<T> res;
	//std::transform(v.cbegin(), v.cend(), res.begin(), [&k](T a){return a * k; });
	for (int i = 0; i < v.size(); i++) 
	{
		res.push_back(v[i] * k);
	}
	return res;
}

template <class T, class Y> std::vector <T> operator* (const Y& k, const std::vector<T>& v)
{
	return v * k;
}


template<class T> T operator* (const std::vector<T>& lhs, const std::vector<T>& rhs)
{
	T res = 0;
	assert(lhs.size() != rhs.size() && "operand doesn't match in size");
	res = std::inner_product(lhs.cbegin(), lhs.cend(), rhs.cbegin(), res);
	return res;
}

template <class T> std::vector <T> operator+ (const std::vector<T>& A, const std::vector<T>& B)
{
	std::vector<T> res;
	std::transform(A.cbegin(), A.cend(), B.cbegin(), res.begin(), std::plus<T>());
	/*for (int i = 0; i < A.size(); i++) 
	{
		res.push_back(A[i] + B[i]);
	}*/
	return res;
}

template <class T> std::vector <T> operator- (const std::vector<T>& lhs,const std::vector<T>& rhs)
{
	std::vector<T> res;
	std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), res.begin(), std::minus<T>());
	return res;
}

template <class T> std::vector<T>& operator += (std::vector<T>& lhs, const std::vector<T>& rhs)
{
	std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), lhs.begin(), std::plus<T>());
	
	return lhs;
}

template <class T, size_t _size> std::array<T, _size> operator+ (const std::array<T, _size>& lhs, const std::array<T, _size>& rhs)
{
	std::array<T, _size> res;
	std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), res.begin(), std::plus<>{});
	return res;
}

template <class T, size_t _size, typename  Y> std::array <T, _size> operator*(const std::array<T, _size>& lhs, const Y num)
{
	std::array<T, _size> res;
	std::transform(lhs.cbegin(), lhs.cend(), res.begin(), [&num ](T a) {return a * num; });
	return res;
}

template <class T, size_t _size, typename  Y> std::array <T, _size> operator*( const Y& num, const std::array<T, _size>& rhs)
{
	return rhs * num;
}


template <class T, size_t _size, typename  Y> std::array <T, _size> operator/(const std::array<T, _size>& lhs, const Y num)
{
	std::array<T, _size> res;
	std::transform(lhs.cbegin(), lhs.cend(), res.begin(), [&num](T a) {return a / num; });
	return res;
}

template <class T, size_t _size> std::array <T, _size> & operator+= (std::array<T, _size>& lhs, const std::array<T, _size>& rhs)
{
	lhs = lhs + rhs;
	return lhs;
}

template <class T, size_t _size, typename  Y> std::array <T, _size>& operator*= (std::array<T, _size>& lhs, const Y& rhs)
{
	lhs = lhs * rhs;
	return lhs;
}
