#ifndef IO_BINARY_FILE_READER_HPP
#define IO_BINARY_FILE_READER_HPP

#include "FileHeader.hpp"

#include <fstream>

namespace IO
{

class BinaryFileReader
{
private:
	std::ifstream file;
	FileHeader header;

	void ReadHeader()
	{
		ReadBitWise(&header);
	}

public:
	BinaryFileReader(const std::string& fileName) :
		file(fileName.c_str(), std::ios::binary | std::ios::in)
	{
		ReadHeader();
	}

	template <typename T>
	void ReadBitWise(T* output)
	{
		file.read(reinterpret_cast<char*>(output), sizeof(*output));
	}

	void ReadBytes(char* output, uint64_t num)
	{
		file.read(output, num);
	}

	template <typename T>
	void ReadBuffer(T* buffer, uint64_t num)
	{
		ReadBytes(reinterpret_cast<char*>(buffer), num * sizeof(*buffer));
	}

	operator bool ()
	{
		return file.operator bool();
	}

	bool operator ! ()
	{
		return file.operator !();
	}

	void Close()
	{
		file.close();
	}

	const FileHeader& GetHeader() const
	{
		return header;
	}
};

} //namespace IO

#endif //IO_BINARY_FILE_READER_HPP
