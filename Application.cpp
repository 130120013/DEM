#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "environment.h"
#include "OBJ.h"
#include "boxCollider.h"
#include "parallel.h"

int main()
{
	pthread_mutex_init(&DEM::parallel::syncContext, NULL);
	//DEM::parallel::num_threads = 8;
	DEM::parallel::workers = new pthread_t[DEM::parallel::num_threads];
	for (int i = 0; i < 100000; i++)
		DEM::parallel::tasks.push(std::make_pair([](void* a)
			{
				long long t;
				time(&t);
				std::cout << ctime(&t) << (int)a << std::endl;
			}, (void*)(i + 1)));
	for (int i = 0; i < DEM::parallel::num_threads; i++)
		pthread_create(&DEM::parallel::workers[i], NULL, DEM::parallel::doTasks, NULL);
	//DEM::utils::OBJ* OBJ = DEM::utils::OBJ::fromFile("D:\\Project\\F228\\DEM\\For test\\Cart.obj");
	//DEM::collision::boxCollider c;
	DEM::parallel::completed = true;
	for (int i = 0; i < DEM::parallel::num_threads; i++)
		pthread_join(DEM::parallel::workers[i], NULL);
	delete[] DEM::parallel::workers;
	return 0;
}
