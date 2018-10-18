#include "geometry.h"

#include <cmath>


template<> template<> 
Vector3<int>::Vector3(const Vector3<float>& v) : 
    x(int(v.x + 0.5)),
    y(int(v.y + 0.5)),
    z(int(v.z + 0.5)) 
{}