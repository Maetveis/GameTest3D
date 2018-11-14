#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <GL/glew.h>

#include <vector>

class ShaderProgram;

class UniformBuffer
{
public:
	~UniformBuffer()
	{
		Destroy();
	}

	void Init();

	void Destroy();

	void BufferData(const GLuint bytes, const void* data, const GLenum usage);

	template<typename T>
	void BufferData(const T& data, const GLenum usage);

	template<typename T>
	void BufferData(const std::vector<T>& data, const GLenum usage);

	void Bind(const ShaderProgram& program, const GLuint index) const;

	GLuint GetBlockBinding() const
	{
		return binding;
	}

	GLuint GetBufferID() const
	{
		return uniformBufferID;
	}
private:
	static unsigned initCount;
	GLuint binding;
	GLuint uniformBufferID;
};

template<typename T>
void UniformBuffer::BufferData(const T& data, const GLenum usage)
{
	BufferData(sizeof(T), reinterpret_cast<const void*>(&data), usage);
}

template<typename T>
void UniformBuffer::BufferData(const std::vector<T>& data, const GLenum usage)
{
	BufferData(sizeof(T) * data.size(), reinterpret_cast<const void*>(data.data()), usage);
}

#endif //UNIFORM_BUFFER_H
