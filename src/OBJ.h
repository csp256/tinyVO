#pragma once

#include "types.h"
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

Shared<OBJ> model_library(std::string const& name);

void initialize_model_library(JSON const& config);
