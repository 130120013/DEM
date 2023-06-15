#pragma once
#include <pthread.h>
#include "clamp.h"
#include <queue>

namespace DEM
{
	namespace parallel
	{
		pthread_t* workers;
		utils::clampMin<unsigned char, 1> num_threads;
		pthread_mutex_t syncContext;
		std::queue<std::pair<void(*)(void*), void*>> tasks;
		bool completed = false;

		void* doTasks(void* __)
		{
			while (!completed || !tasks.empty())
				if (!tasks.empty() && !pthread_mutex_trylock(&syncContext))
				{
					std::pair<void(*)(void*), void*> pair = tasks.front();
					tasks.pop();
					pthread_mutex_unlock(&syncContext);
					pair.first(pair.second);
				}
			return NULL;
		}
	}
}
