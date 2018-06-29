#pragma once

#include <cmath>


template <typename T>
struct Vector2
{
    union {
        struct { T x, y; };
        struct { T u, v; };
        T raw[2];
    };
    
    Vector2() : x(0), y(0) {}
    Vector2(const T& x, const T& y) : x(x), y(y) {}
    
    inline Vector2<T> operator + (const Vector2<T> &V) const {
        return Vector2<T>(x + V.x, y + V.y); }
    
    inline Vector2<T> operator - (const Vector2<T> &V) const {
        return Vector2<T>(x - V.x, y - V.y); }
    
    inline Vector2<T> operator * (float f) const {
        return Vector2<T>(x * f, y * f);
    }
    
    template<typename> friend std::ostream& operator << (std::ostream& s, Vector2<T>& V) {
        s << "( " << V.x << ", " << V.y << " )" << "\n";
        return s;
    }
};



template <typename T>
struct Vector3
{
    union {
        struct { T x, y, z; };
        struct { T i_vert, i_uv, i_norm; };
        T raw[3];
    };
    
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
    
    inline Vector3<T> operator + (const Vector3<T>& V) const {
        return Vector3<T>(x + V.x, y + V.y, z + V.z);
    }
    
    inline Vector3<T> operator - (const Vector3<T>& V) const {
        return Vector3<T>(x - V.x, y - V.y, z - V.z);
    }
    
    inline Vector3<T> operator * (float f) const {
        return Vector3<T>(x*f, y*f, z*f);
    }
    
    inline T operator * (const Vector3<T>& V) const {
        return x * V.x + y * V.y + z * V.z;
    }
    
    float length() const {
        return std::sqrt(x*x + y*y + z*z);
    }
    
    template<typename> friend std::ostream& operator << (std::ostream& s, Vector3<T>& V) {
        s << "( " << V.x << ", " << V.y << ", " << V.z << " )" << "\n";
        return s;
    }
};


typedef Vector2<float>  Vector2f;
typedef Vector2<int>    Vector2i;
typedef Vector3<float>  Vector3f;
typedef Vector3<int>    Vector3i;


