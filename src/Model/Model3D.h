#ifndef MODEL_H
#define MODEL_H

class Model
{
public:
	void Draw(ShaderProgram* program);
private:
	std::vector<MaterialFormat> materials;
	UniformBuffer materialsBuffer;
	Mesh mesh;
};

#endif //MODEL_H