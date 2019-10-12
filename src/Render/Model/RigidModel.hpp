#ifndef RENDER_RIGID_MODEL_HPP
#define RENDER_RIGID_MODEL_HPP

#include "Mesh.hpp"
#include <vector>

namespace Render {

class RigidModel
{
private:
	size_t bufferID;
	std::vector<Mesh> meshes;
public:
	RigidModel(size_t _bufferID, std::vector<Mesh> _meshes = std::vector<Mesh>()) :
 		bufferID(_bufferID),
 		meshes(_meshes)
 	{
		
 	}

	RigidModel(const RigidModel&) = delete;

	RigidModel(RigidModel&&) = default;

	RigidModel& operator=(const RigidModel&) = delete;

	RigidModel& operator=(RigidModel&&) = default;

	void AddMesh(Mesh mesh)
	{
		meshes.emplace_back(std::move(mesh));
	}

	const std::vector<Mesh>& GetMeshes() const
	{
		return meshes;
	}

	size_t GetBufferID() const
	{
		return bufferID;
	}

};

}

#endif //RENDER_RIGID_MODEL_HPP
