#ifndef BASIC_VERTEX_DESCRIPTOR_HPP
#define BASIC_VERTEX_DESCRIPTOR_HPP

#include "../../Helper/VertexArrayDescriptor.hpp"
#include "../../Helper/StaticCounter.hpp"
#include "../../Helper/Buffer.hpp"
#include "BasicVertexFormat.h"
#include "../ModelCounterTraits.hpp"

#include "../../Log/Logger.h"

#include <cstddef>

class BasicVertexDescriptor
{
private:
	VertexArrayDescriptor descriptor;

	StaticCounter<GLint, VertexBufferBindingPointTrait> counter[3];
public:
	BasicVertexDescriptor()
	{
		//First attrribute
		glEnableVertexArrayAttrib(descriptor.Get(), 0);
		glVertexArrayAttribFormat(descriptor.Get(), 0, 3, GL_FLOAT, GL_FALSE, 0 );

		//Set Second attribute
		glEnableVertexArrayAttrib(descriptor.Get(), 1);
		glVertexArrayAttribFormat(descriptor.Get(), 1, 3, GL_FLOAT, GL_FALSE, 12);

		//Set Third attribute
		glEnableVertexArrayAttrib(descriptor.Get(), 2);
		glVertexArrayAttribFormat(descriptor.Get(), 2, 2, GL_FLOAT, GL_FALSE, 24);

		glVertexArrayAttribBinding(descriptor.Get(), 0, 0);//counter[0]);
		glVertexArrayAttribBinding(descriptor.Get(), 1, 0);//counter[1]);
		glVertexArrayAttribBinding(descriptor.Get(), 2, 0);//counter[2]);*/
	}

	BasicVertexDescriptor(Buffer& vertexBuffer, Buffer& indexBuffer)
	{
		Bind();
		vertexBuffer.Bind(GL_ARRAY_BUFFER);
		indexBuffer.Bind(GL_ELEMENT_ARRAY_BUFFER);

		//Set first attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), (void*)offsetof(BasicVertexFormat, pos));

		//Set Second attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), (void*)offsetof(BasicVertexFormat, norm));

		//Set Third attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BasicVertexFormat), (void*)offsetof(BasicVertexFormat, uv));
	}

	void Attach(const Buffer& buffer)
	{
		Logger::Debug << "offsetof(BasicVertexFormat, pos): " << offsetof(BasicVertexFormat, pos) << '\n';
		Logger::Debug << "offsetof(BasicVertexFormat, norm): " << offsetof(BasicVertexFormat, norm) << '\n';
		Logger::Debug << "offsetof(BasicVertexFormat, uv): " << offsetof(BasicVertexFormat, uv) << '\n';

		Logger::Debug << "counter[0] " << counter[0] << '\n';
		Logger::Debug << "counter[1] " << counter[1] << '\n';
		Logger::Debug << "counter[2] " << counter[2] << '\n';

		Logger::Debug << "buffer.GetId(): " << buffer.GetId() << '\n';

		glVertexArrayVertexBuffer(descriptor.Get(), 0, buffer.GetId(), 0, 32);
	}

	void Bind() const
	{
		descriptor.Bind();
	}

	GLint Get() const
	{
		return descriptor.Get();
	}
};

#endif //BASIC_VERTEX_DESCRIPTOR_HPP
