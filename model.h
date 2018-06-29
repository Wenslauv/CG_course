#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "geometry.h"


class Model
{
public:
    Model(const std::string& filename);
    
    int vertices_count() const;
    int faces_count() const;
    
    Vector3f get_vertice(int index) const;
    std::vector<int> get_face(int index) const;
    
private:
    std::vector<Vector3f> vertices;
    std::vector<std::vector<int>> faces;
};
