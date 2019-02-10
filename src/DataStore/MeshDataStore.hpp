#ifndef MESH_DATA_STORE_HPP

#include "../Model/Mesh/Mesh3D.h"
#include "../Model/Mesh/BasicVertexDescriptor.hpp"
#include "../Helper/Buffer.hpp"

class MeshDataStore
{
private:

BasicVertexDescriptor descriptor;
Buffer buffer;

std::vector<Mesh3D> meshes;

public:

void Push(Mesh3D&& mesh)
{

}

};

IDEA: Custom allocat array on gpu

#endif //MESH_DATA_STORE_HPP
