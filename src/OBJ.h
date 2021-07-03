#pragma once

#include <lib/tiny_obj_loader.h>

#include <iostream>

// Courtesy of: https://github.com/TheCherno/Hazel
template <typename T>
using Shared = std::shared_ptr<T>;

template <typename T, typename ... Args>
constexpr Shared<T> CreateShared(Args && ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

using OBJ = tinyobj::ObjReader;

// *************************

inline Shared<OBJ> load_OBJ(std::string const& filename)
{
	auto obj = CreateShared<OBJ>();
	auto valid = obj->ParseFromFile(filename);
	if (not valid) {
		throw std::runtime_error("Failed to load OBJ");
	}
	return obj;
}