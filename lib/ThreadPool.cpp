#include "ThreadPool.h"

ThreadPool& thread_pool(size_t const n)
{
	static ThreadPool pool = ThreadPool(n);
	return pool;
}