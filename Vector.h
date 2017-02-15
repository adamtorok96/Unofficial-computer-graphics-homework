#ifndef SHADOW_VECTOR_H
#define SHADOW_VECTOR_H

#include <cmath>

template <class T>
class Vector {

public:
    T x, y, z;

    Vector(T x = 0, T y = 0, T z = 0);

    Vector<T> operator+(T n);
    Vector<T> operator-(T n);
    Vector<T> operator*(T n);
    Vector<T> operator/(T n);

/*
    Vector<T> operator+(Vector<T> const & a, Vector<T> const & b);
    Vector<T> operator-(Vector<T> const & a, Vector<T> const & b);
*/

    void operator+=(T n);
    void operator-=(T n);
    void operator*=(T n);
    void operator/=(T n);

    double length();

    Vector<T> & normalize();

    T dot(Vector<T> const & v);
    Vector<T> cross(Vector<T> const & v);
};

#endif //SHADOW_VECTOR_H
