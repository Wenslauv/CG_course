#include "model.h"


Model::Model(const std::string& name) {
    
    // do nothing now;
}

int Model::vertices_count() const {
    return vertices.size();
}

int Model::faces_count() const {
    return faces.size();
}

Vector3f Model::get_vertice(int index) const {
    if (index > vertices.size())
        return Vector3f();
    return vertices.at(index);
}

std::vector<int> Model::get_face(int index) const {
    if (index > faces.size()) {
        return std::vector<int>();
    }
    return faces.at(index);
}
