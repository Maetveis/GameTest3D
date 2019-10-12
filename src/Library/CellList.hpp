#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <variant>
#include <vector>

template <typename T>
class CellList
{
private:
	using CellValue = std::variant<T, size_t>;

	std::vector<CellValue> cells;
	std::size_t capacity;

	CellList(std::size_t _capacity) :
		cells(_capacity),
		capacity(_capacity)
	{

	}
};

#endif
