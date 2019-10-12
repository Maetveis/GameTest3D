#ifndef RENDER_RESOURCE_MANAGER_HPP
#define RENDER_RESOURCE_MANAGER_HPP

#include <map>
#include <memory>
#include <vector>
#include <utility>

template <typename T>
class ResourceManager
{
private:
	std::map< std::string, size_t > handles;
	std::vector< T > resources;
public:
	std::optional<size_t> GetHandle(const std::string& name) const
	{
		auto it = handles.find(name);
		std::optional<size_t> object;
		if(it != handles.end())
		{
			object.value() = it->second;
		}
		return object;
	}

 	size_t Add(const std::string& name, T value )
	{
		size_t handle = resources.size();
		resources.emplace_back(std::move(value));
		handles[name] = handle;

		return handle;
	}

	T& Get(size_t handle)
	{
		return resources[handle];
	}
};

#endif //RENDER_RESOURCE_MANAGER_HPP
