#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <unordered_map>
#include <vector>

#include "../Model/Mesh3D.h"

class aiMesh;

class ModelManager
{
public:
	bool ImportFile(const std::string& filename, const std::string& meshname);
	
	Mesh3D& Get(const std::string& name);
	const Mesh3D& Get(const std::string& name) const;
	
	Mesh3D& operator[](const std::string& name);
	const Mesh3D& operator[](const std::string& name) const;
private:
	using mapType = typename std::unordered_map<std::string, Mesh3D>;
	
	void InsertVertices(std::vector<VertexFormat>&, const aiMesh* mesh);
	unsigned int InsertIndices(std::vector<Mesh3D::indexType>&, const aiMesh* mesh);

	mapType meshes;
};

#endif //MODEL_MANAGER_H