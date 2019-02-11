#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <unordered_map>
#include <vector>
#include <utility>

#include "../Helper/Buffer.hpp"
#include "../Model/RigidModel.hpp"
#include "../Model/Mesh/BasicVertexFormat.h"
#include "../Model/Mesh/BasicVertexDescriptor.hpp"
#include "../DataStore/GPUAllocator.hpp"

class aiMesh;

class ModelManager
{
public:
	ModelManager();

	void Draw(const std::string& name) const;

	bool ImportFile(const std::string& filename, const std::string& name);

	const RigidModel& Get(const std::string& name) const;

	const RigidModel& operator[](const std::string& name) const;

	void Delete(const std::string& modelName);
private:
	GPUAllocator vertexAllocator = GPUAllocator(100000000);
	GPUAllocator indexAllocator  = GPUAllocator(100000000);

	Buffer vertexBuffer;
	Buffer indexBuffer;

	BasicVertexDescriptor desc;

	std::unordered_map<std::string, RigidModel> models;
	std::pair<GLuint, GLuint> InsertVertices(const aiMesh& mesh);
	std::pair<GLuint, GLuint> InsertIndices (const aiMesh& mesh);
};

#endif //MODEL_MANAGER_H
