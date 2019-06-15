#include "GPUAllocator.hpp"

GPUAllocator::GPUAllocator(GLuint _max) :
	max(_max)
{
	holesByOffset.emplace(0, max);
	holesByLength.emplace(0, max);
}

GPUAllocator::~GPUAllocator()
{
}

GL::Range GPUAllocator::Allocate(GLuint size, GLuint alignment)
{
	GLuint alignOffset;
	auto iter = holesByLength.lower_bound(size);
	while( iter != holesByLength.end())
	{
		alignOffset = (alignment - iter->offset % alignment) % alignment;
		if(alignOffset + size <= iter->size)
			break;
		++iter;
	}
	if(iter == holesByLength.end())
		throw BufferOutOfMemoryException();

	if(alignOffset > 0)
		AddHole(iter->offset, alignOffset);
	if(alignOffset + size < iter->size)
		AddHole(iter->offset + alignOffset + size, iter->size - alignOffset - size);

	holesByOffset.erase(GL::Range(iter->offset, iter->size));
	holesByLength.erase(iter);

	return GL::Range(iter->offset + alignOffset, size);
};

void GPUAllocator::AddHole(GLuint offset, GLuint size)
{
	holesByLength.emplace(offset, size);
	holesByOffset.emplace(offset, size);
}

void GPUAllocator::DeAllocate(GL::Range allocation)
{
	GLuint newOffset = allocation.offset, newSize = allocation.size;

	auto before = holesByOffset.lower_bound(allocation);
	--before;
	if(before != holesByOffset.end() && before->offset + before->size >= allocation.offset)
	{
		newOffset = before->offset;
		newSize += before->size;

		holesByLength.erase(GL::Range(before->offset, before->size));
		holesByOffset.erase(before);
	}

	auto after = holesByOffset.upper_bound(allocation);
	if(after != holesByOffset.end() && allocation.offset + allocation.size >= after->offset)
	{
		newSize += after->size;

		holesByLength.erase(GL::Range(after->offset, after->size));
		holesByOffset.erase(after);
	}

	AddHole(newOffset, newSize);
}
