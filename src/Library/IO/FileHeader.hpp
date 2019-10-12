#ifndef IO__FILEHEADER_HPP
#define IO__FILEHEADER_HPP

#include <cstdint>

namespace IO
{

struct FileHeader
{
	uint64_t magic;
	uint32_t major;
	uint32_t minor;
};

} //Namespace IO

#endif //IO__FILEHEADER_HPP
