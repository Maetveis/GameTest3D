#ifndef STATIC_FALSE_HPP
#define STATIC_FALSE_HPP


template <typename T>
struct StaticFalse
{
	static constexpr bool value = false;
};


#endif
