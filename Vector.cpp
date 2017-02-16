#include "Vector.h"

template <class T>
Vector<T>::Vector(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector<T> Vector<T>::operator+(T n) {
    return Vector<T>(
            x + n,
            y + n,
            z + n
    );
}

template <class T>
Vector<T> Vector<T>::operator-(T n) {
    return Vector<T>(
            x - n,
            y - n,
            z - n
    );
}

template <class T>
Vector<T> Vector<T>::operator*(T n) {
    return Vector<T>(
            x * n,
            y * n,
            z * n
    );
}

template <class T>
Vector<T> Vector<T>::operator/(T n) {
    return Vector<T>(
            x / n,
            y / n,
            z / n
    );
}

template <class T>
Vector<T> Vector<T>::operator+(Vector const & v) {
    return Vector<T>(
            x + v.x,
            y + v.y,
            z + v.z
    );
}

template <class T>
Vector<T> Vector<T>::operator-(Vector const & v) {
    return Vector<T>(
            x - v.x,
            y - v.y,
            z - v.z
    );
}

template <class T>
void Vector<T>::operator+=(T n) {
    x += n;
    y += n;
    z += n;
}

template <class T>
void Vector<T>::operator-=(T n) {
    x -= n;
    y -= n;
    z -= n;
}

template <class T>
void Vector<T>::operator*=(T n) {
    x *= n;
    y *= n;
    z *= n;
}

template <class T>
void Vector<T>::operator/=(T n) {
    x /= n;
    y /= n;
    z /= n;
}

template <class T>
double Vector<T>::length() {
    return sqrt(
            x * x +
            y * y +
            z * z
    );
}

template <class T>
Vector<T> & Vector<T>::normalize() {
    double l = length();

    if( l != 0.0 ) {
        x /= l;
        y /= l;
        z /= l;
    }

    return *this;
}

template <class T>
T Vector<T>::dot(Vector const & v) {
    return
            x * v.x +
            y * v.y +
            z * v.z ;
}

template <class T>
Vector<T> Vector<T>::cross(Vector<T> const & v) {
    return Vector<T>(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
    );
}

template class Vector<float>;