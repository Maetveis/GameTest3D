#ifndef RENDER_POSNORMUV_DESCRIPTOR_HPP
#define RENDER_POSNORMUV_DESCRIPTOR_HPP

#include "PosNormUVFormat.hpp"

#include <Library/GL/VertexDescriptor.hpp>
#include <Library/GL/TypeEnum.hpp>

#include <cstddef>

namespace GL
{
	class Buffer;
}

namespace Render
{

class PosNormUVDescriptor:
	public GL::VertexDescriptor
{
public:
	PosNormUVDescriptor()
	{
		//First attrribute
		AddAttrib(
			0,
			sizeof(PosNormUVFormat::pos),
		 	GL::TypeEnum<float>::value,
			false,
			offsetof(PosNormUVFormat, pos)
		);

		//Set Second attribute
		AddAttrib(
			1,
			sizeof(PosNormUVFormat::norm),
			GL::TypeEnum<float>::value,
			false,
			offsetof(PosNormUVFormat, norm)
		);

		//Set Third attribute
		AddAttrib(
			2,
			sizeof(PosNormUVFormat::uv),
			GL::TypeEnum<float>::value,
			false,
			offsetof(PosNormUVFormat, uv)
		);
	}

	inline void BindVertexBuffer(const GL::Buffer& buffer)
	{
		GL::VertexDescriptor::BindVertexBuffer(buffer, 0, sizeof(PosNormUVFormat));
	}
};

}

#endif //RENDER_POSNORMUV_DESCRIPTOR_HPP
