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


    Vector<T> operator+(Vector<T> const & v);
    Vector<T> operator-(Vector<T> const & v);


    void operator+=(T n);
    void operator-=(T n);
    void operator*=(T n);
    void operator/=(T n);

    double length();

    Vector<T> & normalize();

    T dot(Vector<T> const & v);
    Vector<T> cross(Vector<T> const & v);
};


typedef Vector<int> Vectori;
typedef Vector<float> Vectorf;
typedef Vector<double> Vectord;

#endif //SHADOW_VECTOR_H
