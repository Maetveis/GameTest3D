#ifndef RENDER_MESH_HPP
#define RENDER_MESH_HPP

#include "VertexBatch.hpp"

#include <utility>

namespace Render
{

class Mesh
{
private:
	VertexBatch batch;
	size_t materialID;
public:
	Mesh(VertexBatch _batch, size_t _materialID) :
		batch(std::move(_batch)),
		materialID(_materialID)
	{

	}

	/*
		Draw the vertices of the Mesh assuming the correct buffer is bound and
		material data is also bound
	*/
	void Draw() const
	{
		batch.Draw();
	}

	size_t GetMaterialID() const
	{
		return materialID;
	}
};

}

#endif //RENDER_MESH_HPP
