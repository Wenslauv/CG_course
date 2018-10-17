#include "model.h"


Model::Model(const std::string& name) {
    
    std::ifstream in;
    in.open(name, std::ifstream::in);

    if (in.fail())
        return;

    std::string line;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());

        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;

            Vector3f v;
            for (int i=0; i<3; ++i)
            {
               iss >> v.raw[i];  
            }
            vertices.push_back(v);
        }
        else if (!line.compare(0,2, "f ")) {
            std::vector<int> f;
            int t, idx;
            
            iss >> trash;
            while(iss >> idx >> trash >> t >> trash >> t) {
                idx --;
                f.push_back(idx);
            }
            faces.push_back(f);
        }

        std::cerr << "# v# " << vertices.size() << " f# "  << faces.size() << std::endl;
    }
    
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
