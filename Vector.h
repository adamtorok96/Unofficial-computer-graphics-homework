#ifndef SHADOW_VECTOR_H
#define SHADOW_VECTOR_H

#include <cmath>

template <class T>
class Vector {

public:
    T x, y, z;

    Vector(T x = 0.0f, T y = 0.0f, T z = 0.0f);

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

typedef Vector<char> Vector3c;
typedef Vector<unsigned char> Vector3uc;
typedef Vector<int> Vector3i;
typedef Vector<unsigned int> Vector3ui;
typedef Vector<float> Vector3f;
typedef Vector<double> Vector3d;

#endif //SHADOW_VECTOR_H
