#pragma once

#include <lib/ThreadPool.h>

template <class OutputType, typename Map, class Input>
inline auto parallel(Map map, std::vector<Input> const& input)
			-> std::vector<std::future<OutputType>>
{
	size_t const n = input.size();

	// using OutputType = decltype(Map(input.first()));
	using FutureType = std::future<OutputType>;
	std::vector<FutureType> results;
	results.reserve(n);

	for (auto& in : input) {
		results.emplace_back( thread_pool().enqueue(
			[&map](Input const& arg) -> OutputType
			{
				return map(arg);
			}, in));
	}

	return results;
}