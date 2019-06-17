#ifndef MATERIAL_HPP

#include "../../Library/GL/Range.hpp"

#include <GL/glew.h>

class Material
{
private:
	GL::Range location;
public:
	Material(GL::Range _location) :
		location(_location)
	{
	}

	GL::Range GetLocation() const
	{
		return location;
	}
};

#endif //MATERIAL_HPP
