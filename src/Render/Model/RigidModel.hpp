#ifndef RENDER_RIGID_MODEL_HPP
#define RENDER_RIGID_MODEL_HPP

#include "Mesh.hpp"
#include <vector>

namespace Render {

using MaterialId = unsigned int;

class RigidModel
{
public:
	std::vector<Mesh> meshes;
	std::vector<MaterialId> materials;

	RigidModel() = default;
	RigidModel(const RigidModel&) = delete;
	RigidModel(RigidModel&&) = default;

	RigidModel& operator=(const RigidModel&) = delete;
	RigidModel& operator=(RigidModel&&) = default;
/*
	void AddPart(MeshId mesh, MaterialId material);*/
};

}

#endif //RENDER_RIGID_MODEL_HPP
