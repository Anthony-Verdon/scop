#include "Mesh/MeshData/MeshData.hpp"

MeshData::MeshData()
{

}

MeshData::MeshData(const MeshData &instance)
{
    *this = instance;
}

MeshData &MeshData::operator=(const MeshData &instance)
{
    if (this != &instance)
    {
        vertices = instance.GetVertices();
        indices = instance.GetIndices();
        initialRotation = instance.GetInitialRotation();
    }

    return (*this);
}

MeshData::~MeshData()
{
    
}