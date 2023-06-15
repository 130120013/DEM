#include "OBJ.h"
#include "Model.h"
#include "Particle.h"
#include "IntegrableLayer.h"
#include "Environment.h"
#include <iostream>
#include <fstream>
#include <pthread.h>

#define AUTO_INTEGRATION_STEP

int main()
{
	pthread_t* workers;
	unsigned NUM_THREADS;
	pthread_mutex_t syncContext;
	pthread_mutex_init(&syncContext, NULL);

	bool checked = false;
	do
	{
		std::cout << "Temperature (K): ";
		std::cin >> T;
		t = T - CELSIUS_TO_KELVIN;
		std::cout << "Humidity (%): ";
		std::cin >> humidity;
		humidity /= 100;
		std::cout << "Pressure (Pa): ";
		std::cin >> pressure;
		partialWaterVaporPressure =
			humidity * exp((19.846 + 8.97e-03 * t + 1.248 * t * t) * t / T) * 611.26;
		rho = (DRY_AIR_MOLAR_MASS * (pressure - partialWaterVaporPressure) +
			WATER_VAPOR_MOLAR_MASS * partialWaterVaporPressure) / (UNIVERSAL_GAS_CONST * T);
		std::cout << "Initial particle speed (along X axis, m/s): ";
		std::cin >> v_0;
		std::cout << "Current conditions:"
				//<< "\n\tIntegration step: " << step
				  << "\n\tTemperature: " << T
				  << "\n\tHumidity: " << humidity
				  << "\n\tPressure: " << pressure
				  << "\n\tDensity: " << rho
				  << "\n\tInitial speed: " << v_0 << std::endl;
		std::string s;
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Continue (y/n)? ";
		std::getline(std::cin, s);
		if (s.find("y") != std::string::npos || s.find("Y") != std::string::npos)
			checked = true;
	} while (!checked);

	std::string filename;
	std::cout << "Path to OBJ file: ";
	std::getline(std::cin, filename);
	OBJ* obj = OBJ::fromFile(filename);
	Vector3 modelDir(1, 0, 0);
	if (!obj)
	{
		std::cerr << "Cannot load model. Make sure there is the file you\'re looking for." << std::endl;
		system("pause");
		return 1;
	}
	Box3d modelBox = obj->bounds();
	std::cout << "Model loaded.\n\tIts center: " << modelBox.center.x <<
		" " << modelBox.center.y << " " << modelBox.center.z <<
		"\n\tIts half dimensions: " << modelBox.halfDim.x << " " <<
		modelBox.halfDim.y << " " << modelBox.halfDim.z << std::endl;

	float outbounds;
	unsigned NUM_PARTICLES, A, B, C;
	double MASS, RADIUS;
	checked = false;
	do
	{
		std::cout << "Outbounds value (how much layer area is bigger than YZ dims, rational): ";
		std::cin >> outbounds;
		std::cout << "Number of particles in the layer: ";
		std::cin >> NUM_PARTICLES;
		double b_area = modelBox.halfDim.y * modelBox.halfDim.z * 4;
		double c_area = b_area * outbounds;
		double Y = modelBox.halfDim.y * 2 * sqrt(outbounds);
		double Z = modelBox.halfDim.z * 2 * sqrt(outbounds);
		double b_c = Y * Y / c_area;
		std::cout << "Possible variants:" << std::endl;
		std::vector<unsigned> var;
		for (unsigned i = 1; i <= NUM_PARTICLES; i++)
		{
			float ratio = (float)i * i / NUM_PARTICLES;
			if ((NUM_PARTICLES / i) * i == NUM_PARTICLES)
			{
				var.push_back(i);
				std::cout << "\t" << var.size() << "\ty = " << i << "; z = "
					<< (NUM_PARTICLES / i) << "; ratio: " << ratio << std::endl;
			}
		}
		unsigned n;
		std::cout << "Enter the right number of variant to continue or something else to restart: ";
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> n;
		if (n > 0 && n <= var.size())
		{
			B = var[n - 1];
			C = NUM_PARTICLES / B;
			std::cout << "\t" << n << "\ty = " << B << "; z = "	<< C << std::endl;
			RADIUS = std::max(Y / B / 2, Z / C / 2);
			MASS = rho * 4 / 3 * 3.14159265358979 * RADIUS * RADIUS * RADIUS;
			checked = true;
		}
	} while (!checked);

	checked = false;
	do
	{
		std::cout << "Number of layers: ";
		std::cin >> A;
		std::cout << "Number of threads to calculate thru: ";
		std::cin >> NUM_THREADS;
		std::cout << "Number of particles in simulation: " << A * B * C << std::endl
				  << "Radius of the particle: " << RADIUS << std::endl
				  << "Mass of the particle: " << MASS << std::endl
#ifdef AUTO_INTEGRATION_STEP
				  << "Integration step (auto): " << (step = 0.0001) << std::endl;
#else
				  << "Integration step: ";
		std::cin >> step;
#endif

		std::string s;
		std::cin.ignore(INT_MAX, '\n');
		std::cout << "Continue (y/n)? ";
		std::getline(std::cin, s);
		if (s.find("y") != std::string::npos || s.find("Y") != std::string::npos)
			checked = true;
	} while (!checked);

	workers = new pthread_t[NUM_THREADS];
	Model m(obj);
	IntegrableLayer layer;

	//for (int i = 0; i < rowCol.first; i++)
	//	for (int j = 0; j < rowCol.second; j++)
	//		layer.push_back(new Particle(MASS, 0.0075, 273.15,
	//			Vector3(0, -0.6325 + 0.015 * j, -0.6325 + 0.015 * i),
	//			Quaternion(), v_0 * modelDir, Vector3()));
	obj->move((v_0 * 0.1 - modelBox.center.x) * modelDir);
	modelBox = obj->bounds();
	{
		double oY = (B * RADIUS - modelBox.halfDim.y * outbounds) / 2;
		double oZ = (C * RADIUS - modelBox.halfDim.z * outbounds) / 2;
		for (unsigned x = 0; x < A; x++)
			for (unsigned y = 0; y < B; y++)
				for (unsigned z = 0; z < C; z++)
				{
					
					layer.push_back(new Particle(MASS, RADIUS, T,
						Vector3(
							-2 * RADIUS * x,
							modelBox.center.y - modelBox.halfDim.y - RADIUS + 2 * RADIUS * y,
							modelBox.center.z - modelBox.halfDim.z - RADIUS + 2 * RADIUS * z
						),
						Quaternion(), v_0 * modelDir, Vector3())
					);
				}
	}
	layer.push_back(&m);
	time_t tStart;
	std::cout << "It\'s all prepared. Starting calculations. Time: " <<
		(tStart = time(0)) << std::endl;

	std::ofstream f("results.txt");
	if (!f.is_open())
	{
		std::cerr << "Cannot open resulting file." << std::endl;
		return 2;
	}
	f << "[IDs]" << std::endl;
	unsigned count = 0;
	for (int i = 0; i < layer.size(); i++)
	{
		IIntegrable*& integrable = layer[i];
		integrable->ID = count++;
		Model* model = dynamic_cast<Model*>(integrable);
		Particle* particle = dynamic_cast<Particle*>(integrable);
		if (model)
			f << "m" << model->ID << "#" << modelBox.center.x << " " << modelBox.center.y <<
			" " << modelBox.center.z << "#" << model->filename << std::endl;
		else if (particle)
			f << "p" << particle->ID << "#" << particle->R << std::endl;
		else
			f << "!" << std::endl;
	}
	f << "&" << std::endl;
	for (double t = 0; t < 0.2 + step / 10; t += step)
	{
		int layerSize = layer.size();
		double vmax = 0, xmax = 0;
		std::cout << "Time: " << t << "\nEntities: " << layerSize << std::endl;
		//if (t >= 0.00261)
		//{
		//	int a = 5;
		//}

		int layerNum = 0;
		struct for_thread_use
		{
			int* i;
			int* size;
			double* vmax;
			double* xmax;
			IntegrableLayer* layer;
			pthread_mutex_t* syncContext;
		} I { &layerNum, &layerSize, &vmax, &xmax, &layer, &syncContext };
		for (int i = 0; i < NUM_THREADS; i++)
		{
			pthread_create(&workers[i], NULL, [](void* I) -> void*
				{
					for_thread_use* I1 = (for_thread_use*)I;
					while (*I1->i < *I1->size)
					{
						pthread_mutex_lock(I1->syncContext);
						int i = (*I1->i)++;
						pthread_mutex_unlock(I1->syncContext);
						if (i >= *I1->size)
							continue;
						ICollidable* pi = dynamic_cast<ICollidable*>((*(I1->layer))[i]);
						IMovable* mov = dynamic_cast<IMovable*>(pi);
						if (mov)
						{
							double spd = mov->linSpd.magnitude();
							if (spd > *I1->vmax)
								*I1->vmax = spd;
						}
						for (int j = i + 1; j < *I1->size; j++)
						{
							ICollidable* pj = dynamic_cast<ICollidable*>((*(I1->layer))[j]);
							ICollidable::dir_overlap dOverlap = pi->checkCollision(pj);
							if (dOverlap.overlap)
							{
								//std::cout << "    Collision [" << i << "]->[" << j << "]."
								//	" Overlap: " <<	dOverlap.overlap << std::endl;
								(*(I1->layer))[i]->F -=
									dOverlap.overlap * dOverlap.dir;
								(*(I1->layer))[j]->F +=
									dOverlap.overlap * dOverlap.dir;
							}
							if (dOverlap.overlap > *I1->xmax)
								*I1->xmax = dOverlap.overlap;
						}
					}
					return NULL;
				}, &I);
		}
		while (layerNum < layerSize);
		for (int i = 0; i < NUM_THREADS; i++)
			pthread_join(workers[i], NULL);
		double k;
		if (xmax == 0)
			k = 0;
		//else if (vmax == 0)
		//	k = MASS / step;
		//else
		//	k = MASS * vmax * vmax / (xmax * xmax);
		else
			k = 2 * MASS * vmax * (RADIUS - xmax) / (step * xmax);
			//k = (xmax / RADIUS) * MASS * vmax / (step * xmax);
		for (int i = 0; i < layerSize; i++)
			layer[i]->F *= k;
		f << "[t=" << t << "]" << std::endl;
		for (int i = 0; i < layerSize; i++)
		{
			IIntegrable*& entity = layer[i];
			f << "[id=" << entity->ID << "]" << std::endl;
			Particle* particle = dynamic_cast<Particle*>(entity);
			if (particle)
				f << particle->pos.x << " " << particle->pos.y << " " << particle->pos.z << std::endl;
			else
				f << entity->F.x << " " << entity->F.y << " " << entity->F.z << std::endl;
			if (entity->F.magnitude())
				f << "[collided]" << std::endl;
			entity->integrate(step);
		}
		
	}
	f.close();
	std::cout << "Done. Elapsed time: " << time(0) - tStart << " seconds. "
		"Have a nice day. ;-)" << std::endl;
	system("pause");
	return 0;
}
