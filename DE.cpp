//#include "./CEC2010/Header.h"


#include "Self_Define_Functions.h"


#include <cstdio>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <boost/random.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/cauchy_distribution.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>


using namespace std;
double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

// in this program the global best solution is updated after each subgroup finish iterating itself
int main(int argc, char *argv[])
{
	int funToRun[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30 };  //function set
	int funNum = 30; //total function num
	int i, j;
	double CR = 0.9;//Crossover probability
	double F = 0.8;//Scaling factor
	double *global_best = new double[dim];
	double global_fitness;
	double **trail_vector = new double*[Population_size];
	double **mutation_vector = new double*[Population_size];
	double **population = new double*[Population_size];
	for (i = 0; i < Population_size; ++i)
	{
		population[i] = new double[dim];
		trail_vector[i]= new double[dim];
		mutation_vector[i]= new double[dim];
	}
	double *results = new double[Population_size];// the fitness results for the whole population
	double MAX = 100;//Gene maximum
	double MIN = -100;//Gene minimum
	double *trail_vector_result= new double[Population_size];;
	int FV = 0;//Current fitness evaluation times
	int function_index;//functional index
	int run_index;//run time index
	int parent1, parent2;//parent1, parent2

	for (function_index = 0; function_index < funNum; function_index++)
	{
		cout << "Function " << funToRun[function_index] << " Begined!" << endl;

		boost::mt19937 generator(time(0)*rand());
		// to initialize the population
		boost::uniform_real<> uniform_real_generate_x(MIN, MAX);
		boost::variate_generator< boost::mt19937&, boost::uniform_real<> > random_real_num_x(generator, uniform_real_generate_x);
		boost::uniform_real<> uniform_real_generate_r(0, 1);
		boost::variate_generator< boost::mt19937&, boost::uniform_real<> > random_real_num_r(generator, uniform_real_generate_r);
		//select an individual from the population
		boost::uniform_int<> int_generator1(0, Population_size - 1);
		boost::variate_generator< boost::mt19937&, boost::uniform_int<> > int_number1(generator, int_generator1);

		char fun[10];
		snprintf(fun, 10, "%d", funToRun[function_index]);
		string filename_fitness = "E:/DE/DE/Results/Fitness_result_for_function_" + string(fun) + ".txt";
		ofstream out_fitness(filename_fitness.c_str());

		if (!out_fitness)
		{
			cerr << "Can not open the file " << filename_fitness << endl;
			exit(1);
		}
		for (run_index = 0; run_index < timesOfRun; run_index++)
		{
			cout << "Running the " << run_index << "th times" << endl;
			FV = 0;

			//initialize the population
			for (i = 0; i < Population_size; ++i)
			{
				for (j = 0; j < dim; ++j)
				{
					population[i][j] = random_real_num_x();
				}
			}
			for (int i = 0; i < Population_size; i++)//适应值计算
			{
				cec14_test_func(population[i], &results[i], dim, 1, funToRun[function_index]);
				results[i] = results[i] - funToRun[function_index] * 100;

			}
			FV += Population_size;
			Find_best(results, Population_size, global_best, population, global_fitness, dim);

			while (FV < MAX_FV)
			{
				for (i = 0; i < Population_size; ++i)
				{
					parent1 = int_number1();
					while (parent1 == i)
					{
						parent1 = int_number1();
					}
					parent2 = int_number1();
					while (parent2 == i || parent2 == parent1)
					{
						parent2 = int_number1();
					}
					Mutation(mutation_vector[i], population[i], population[parent1], population[parent2], global_best, MIN, MAX, F, dim);
					Crossover(trail_vector[i], population[i], mutation_vector[i], CR, dim);
					cec14_test_func(trail_vector[i], &trail_vector_result[i], dim, 1, funToRun[function_index]);
					trail_vector_result[i] = trail_vector_result[i] - funToRun[function_index] * 100;
					FV++;

					if (trail_vector_result[i] < results[i])//section
					{
						results[i] = trail_vector_result[i];
						memcpy(population[i], trail_vector[i], sizeof(double)*dim);
						if (results[i] < global_fitness)
						{
							global_fitness = results[i];
							memcpy(global_best, population[i], sizeof(double)*dim);
						}
					}
				}
				printf("%f\n", global_fitness);
			}
			out_fitness << global_fitness << endl;//output the final result to file






		}





		out_fitness.close();




		cout << "Function " << funToRun[function_index] << " Finished!" << endl;

	}


	//release the resouces
	for (i = 0; i < Population_size; ++i)
    {
        delete[]population[i];
        delete[]trail_vector[i];
        delete[]mutation_vector[i];
    }

	delete[]population;
	delete[]trail_vector;
    delete[]mutation_vector;
	delete[]results;
	delete[]global_best;


	return 0;
}



