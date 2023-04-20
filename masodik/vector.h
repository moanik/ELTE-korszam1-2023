#include <iostream>
#include <cmath>

template<typename T>
struct Vector{
    T x, y;

    Vector<T>& operator+=( Vector<T> const& v )
    {
        x += v.x; y += v.y;
        return *this;
    }

    Vector<T>& operator-=( Vector<T> const& v )
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    Vector<T>& operator*=( T const& a)
    {
        x *= a; y *= a;
        return *this;
    }

    Vector<T>& operator/=( T const& a)
    {
        x /= a; y /= a;
        return *this;
    }

};

template<typename T>
Vector<T> operator+( Vector<T> const& a, Vector<T> const& b)
{
    return Vector<T>{ a.x + b.x, a.y + b.y };
}

template<typename T>
Vector<T> operator-( Vector<T> const& a, Vector<T> const& b)
{
    return Vector<T>{ a.x - b.x, a.y - b.y };
}

template<typename T>
Vector<T> operator*( Vector<T> const& a, T const& b)
{
    return Vector<T>{ a.x * b, a.y * b};
}

template<typename T>
Vector<T> operator*( T const& b, Vector<T> const& a)
{
    return Vector<T>{ a.x * b, a.y * b};
}

template<typename T>
Vector<T> operator/( Vector<T> const& a, T const& b)
{
    return Vector<T>{ a.x / b, a.y / b};
}

template<typename T>
std::ostream& operator<<( std::ostream& o, Vector<T> const& v )
{
    o << "x: " << v.x << ", y: " << v.y;
    return o;
}

template<typename T>
std::istream& operator>>( std::istream& i, Vector<T>& v )
{
    i >> v.x;
    i >> v.y;
    return i;
}

template<typename T>
T dot(Vector<T> const& v1, Vector<T> const& v2){
    return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
double length(Vector<T> const& v){
    return v.x + v.y;
}

template<typename T>
double sqlength(Vector<T> const& v){
    return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

template<typename T>
Vector<T> normalize(Vector<T> const& v){
    double l = sqlength(v);
    return Vector<T>{v.x / l, v.y / l};
}
