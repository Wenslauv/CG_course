#pragma once


#include <vector>
#include <string>



class Model
{
public:
    Model(const std::string& filename);
    
    
    
    
private:
    std::vector<std::vector<int> > faces;
    std::vector<int> vertices;
};
