#ifndef IO_BINARY_FILE_WRITER_HPP
#define IO_BINARY_FILE_WRITER_HPP

#include "FileHeader.hpp"

#include <fstream>

namespace IO
{

class BinaryFileWriter
{
private:
	std::ofstream file;

public:
	BinaryFileWriter(const std::string& fileName) :
		file(fileName.c_str(), std::ios::binary | std::ios::out)
	{
	}

	template <typename T>
	void WriteBitWise(const T& input)
	{
		file.write(reinterpret_cast<const char*>(&input), sizeof(input));
	}

	void WriteBytes(const char* input, uint64_t num)
	{
		file.write(input, num);
	}

	template <typename T>
	void WriteBuffer(T* buffer, uint64_t num)
	{
		WriteBytes(reinterpret_cast<const char*>(buffer), num * sizeof(*buffer));
	}

	operator bool ()
	{
		return file.operator bool();
	}

	bool operator ! ()
	{
		return file.operator !();
	}

	void WriteHeader(const FileHeader& header)
	{
		WriteBitWise(header);
	}
};

} //namespace IO

#endif //IO_BINARY_FILE_WRITER_HPP
