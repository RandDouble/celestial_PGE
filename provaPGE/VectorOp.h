#pragma once

#include <vector>
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
	//std::transform(A.cbegin(), A.cend(), B.cbegin(), res.begin(), std::plus<>{});
	for (int i = 0; i < A.size(); i++) 
	{
		res.push_back(A[i] + B[i]);
	}
	return res;
}

template <class T> std::vector <T> operator- (const std::vector<T>& lhs,const std::vector<T>& rhs)
{
	std::vector<T> res;
	std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), res.begin(), std::minus<>{});
	return res;
}

template <class T> std::vector<T>& operator += (std::vector<T>& lhs, const std::vector<T>& rhs)
{
	std::transform(lhs.cbegin(), lhs.cend(), rhs.cbegin(), lhs.begin(), std::plus<>{});
	
	return lhs;
}

