#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <initializer_list>
#include <cmath>
#include <ostream>

namespace detail
{
	template<typename V1, typename V2, typename F>
	void transform_vector1(V1 const& v1, V2& v2, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.begin(), f);
	}

	template<typename V1, typename V2, typename V3, typename F>
	void transform_vector2(V1 const& v1, V2 const& v2, V3& v3, F f)
	{
		std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), v3.begin(), f);
	}
}

auto add = [](auto const& x, auto const& y){ return x + y; };
auto sub = [](auto const& x, auto const& y){ return x - y; };

struct Idx1{};
struct Idx2{};

template<typename T>
class Matrix{
	private:
		int N = 0;
		std::vector<T> data;

	public:
		Matrix() = default;
		Matrix(const Matrix<T>& ) = default;
		Matrix( Matrix<T> && ) = default;
		Matrix(int dim){
			N = dim;
			data = std::vector<T>(N * N, (T)0);
		}
		Matrix(const std::vector<T>& newData){
			N = (int)sqrt(newData.size());
			data = newData;
		};

		//Matrix(const Matrix& other) = default;
		Matrix<T>& operator=(Matrix<T> const&) = default;
		Matrix<T>& operator=(Matrix <T>&&) = default;

		int size()const
		{
			return N;
		}

		T&       operator()(int i, int j){ return data[N * i + j]; }
		T const& operator()(int i, int j) const{ return data[N * i + j]; }
		T&       operator[]( int i )       { return data[i]; }
		T const& operator[]( int i ) const { return data[i]; }

		template<typename F>
		Matrix(Idx1, F f, int n)
		{
			N = n;
			data.resize(n * n);
			for(int i = 0; i < n * n; ++i){ data[i] = f(i); }
		}

		template<typename F>
		Matrix(Idx2, F f, int n)
		{
			N = n;
			data.resize(n * n);
			for(int i = 0; i < n; ++i){ 
				for(int j = 0; i < n; i++){
					data(i, j) = f(i, j); 
				}
			}
		}



		auto begin()
		{
			return data.begin();
		}

		auto cbegin() const
		{
			return data.cbegin();
		}

		auto end()
		{
			return data.end();
		}

		auto cend() const
		{
			return data.cend();
		}
};

template<typename T>
Matrix<T> operator+( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	Matrix<T> result(v1.size()); 
	detail::transform_vector2(v1, v2, result, add);
	return result;
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	detail::transform_vector2(v1, v2, v1, add );
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T> const& v1, Matrix<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v2, add );
	return std::move(v2);
}

template<typename T>
Matrix<T>&& operator+( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v1, add );
	return std::move(v1);
}

template<typename T>
Matrix<T> operator-( Matrix<T> const& v1, Matrix<T> const& v2 )
{
	Matrix<T> result(v1.size()); 
	detail::transform_vector2(v1, v2, result, sub);
	return result;
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T> const& v2 )
{
	detail::transform_vector2(v1, v2, v1, sub);
	return std::move(v1);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T> const& v1, Matrix<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v2, sub);
	return std::move(v2);
}

template<typename T>
Matrix<T>&& operator-( Matrix<T>&& v1, Matrix<T>&& v2 )
{
	detail::transform_vector2(v1, v2, v1, sub);
	return std::move(v1);
}

//-------------

template<typename T>
Matrix<T> operator*(Matrix<T> const& v, T const& scl)
{
	Matrix<T> result(v.size()); 
	detail::transform_vector1(v, result, [=](T const& x){ return x * scl; });
	return result;
}

template<typename T>
Matrix<T>&& operator*(Matrix<T>&& v, T const& scl)
{
	detail::transform_vector1(v, v, [=](T const& x){ return x * scl; });
	return std::move(v);
}

template<typename T>
Matrix<T> operator*(T const& scl, Matrix<T> const& v)
{
	Matrix<T> result(v.size()); 
	detail::transform_vector1(v, result, [=](T const& x){ return scl * x; });
	return result;
}

template<typename T>
Matrix<T> operator*(Matrix<T> const& v1, Matrix<T> const& v2)
{
	Matrix<T> result(v1.size()); 

	for(int i = 0; i < v1.size(); i++){
		for(int j = 0; j < v1.size(); j++){
			    for (int k = 0; k < v1.size(); k++) {
                	result(i, j)  += v1(i, k)  * v2(k, j) ;
            }
		}
	}

	return result;
}

// template<typename T>
// Matrix<T>&& operator*(Matrix<T>&& v1, Matrix<T> const& v2)
// {
// 	Matrix<T> v3(v1); 

// 	for(int i = 0; i < v1.size(); i++){
// 		for(int j = 0; j < v1.size(); j++){
// 			v1(i, j) = 0;
// 			    for (int k = 0; k < v1.size(); k++) {
//                 	v1(i, j)  += v3(i, k) * v2(k, j) ;
//             }
// 		}
// 	}
// 	return std::move(v1)
// }

template<typename T>
Matrix<T>&& operator*(T const& scl, Matrix<T>&& v)
{
	detail::transform_vector1(v, v, [=](T const& x){ return scl * x; });
	return std::move(v);
}

template<typename T>
Matrix<T> operator/(Matrix<T> const& v, T const& scl)
{
	Matrix<T> result(v.size()); 
	detail::transform_vector1(v, result, [=](T const& x){ return x / scl; });
	return result;
}

template<typename T>
Matrix<T>&& operator/(Matrix<T>&& v, T const& scl)
{
	detail::transform_vector1(v, v, [=](T const& x){ return x / scl; });
	return std::move(v);
}