#pragma once

#include <type_traits>
#include <lib/ThreadPool.h>

template <typename Map, class Input>
inline auto parallel(Map map, std::vector<Input> const& input)
			-> std::vector<std::future<typename std::invoke_result<Map,Input>::type>>
{
	size_t const n = input.size();

	using OutputType = typename std::invoke_result<Map,Input>::type;
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