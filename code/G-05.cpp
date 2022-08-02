/*
*	Project: Enhanced Multiverse Optimixer
*	Authors : Rizwan Habib 19I-0657 , Talha Rizwan 19-652 , Noor Ul Eman 19I-0653 , Syed Iftikhar Mehdi 19I-0657
*	File : main.h
*	Date : 20-6-2021
*/

#include <math.h>
#include "universe.h"
#include "QuickSort.h"
#include "RouletteWheelSelection.h"
#include <chrono>
using namespace std::chrono;
auto start = high_resolution_clock::now();
int main()
{
	{
		srand(time(NULL));
		int numMachines;
		Universe best_so_far;
		best_so_far.MakespanTime = 1000;
		cout << "Number of Machines : ";
		cin >> numMachines;

		int numTasks;
		cout << "Number of Tasks :";
		cin >> numTasks;

		cout << "* MIPS of each Machine * " << endl;
		//double* MIPS = new double[numMachines];
		double backup = 10000;
		VM *vms = new VM[numMachines];
		
		for (size_t i = 0; i < numMachines; i++)
		{
			// cout << "MIPS of Machine" << i + 1 << " : ";
			// cin >> vms[i].MIPS;
			vms[i].MIPS = rand() % 10 + 1;
			vms[i].id = i;
			cout<<"machine power of machine: "<<i+1<<vms[i].MIPS<<endl;
		}

		srand(time(NULL));
		double *numOfIns = new double[numTasks];

		// cout << "* Number of Instructions per Task *" << endl;
		for (int i = 0; i < numTasks; i++)
		{
			// cout << "Number of Instructions of Task " << i + 1 << " :";
			// cin >> numOfIns[i];
			numOfIns[i] = rand() % 300 +1;
			// numOfIns[i]=300;
			cout<<"num instructions of task: "<<i+1<<" "<<numOfIns[i]<<endl;
		}
		Universe *universe = new Universe[50];//17 24		27 71 107 133

		for (int i = 0; i < 50; i++)
		{
			universe[i].set(numTasks, numMachines, numOfIns, vms);
			universe[i].AssignVMTasks();
		}
		int max_iterations = 20;
		Universe best_solutions[50];
		int iter = 0, count = 0;

		for (int k = 0; k < max_iterations; k++)
		{

			for (int i = 0; i < 50; i++)
			{
				double x = universe[i].Calculatemakespan(0);
				// cout << x << endl;
				if (universe[i].MakespanTime < backup)
				{
					backup = universe[i].MakespanTime;
				}
			}
			Universe temp[50];
			for (int i = 0; i < 50; i++)
			{
				temp[i].MakespanTime = universe[i].MakespanTime;
			}

			quickSort(universe, 0, 49);

			// printArray(universe,numTasks);

			//(((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
			//#################### updating best_so_far  #################################

			if (best_so_far.MakespanTime > universe[0].MakespanTime){
				best_so_far = universe[0];
				best_so_far.VirtualMachines = universe[0].VirtualMachines;
			}


			int roulette = 0;
			int random = -1;
			double sum = 0;
			for (int i = 0; i < 50; i++)
			{
				sum += universe[i].MakespanTime * universe[i].MakespanTime;
			}
			for (int i = 0; i < 50; i++) // calculating normalized iflation rate
			{
				universe[i].NI = universe[i].MakespanTime / sqrt(sum);
				// cout<<"NI:  "<<universe[i].NI<<endl;
			}

			for (int i = 1; i < 50; i++)
			{
				roulette = RouletteWheel(temp);
				// roulette=rand()%50;
				// cout << "roulette:   " << roulette << endl;

				for (int j = 0; j < numTasks; j++)
				{

					//(((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
					//################### Black/White Holes #############################################

					random = rand() % 2;
					if (random < universe[i].NI)
					{
						universe[i].Tasks[j].vMachine = universe[roulette].Tasks[j].vMachine;
					}
					//(((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
					//################### Worm Holes #############################################

					float TDR = 1 - (pow((float)i, (1 / 6.0)) / pow(50.0, (1 / 6.0)));

					float WEP = (0.2) + (float)i * (1 - 0.2 / 50.0);
					int r2 = rand() % 2;
					if (r2 < WEP)
					{

						int r3 = rand() % 2, r4 = rand() % 2;
						int TDR1 = (int)(j - floor(TDR * r4)) % numTasks;
						int TDR2 = (int)(j + ceil(TDR * r4)) % numTasks;
						

						
						if (r3 < 0.5)
						{

							if (TDR2 >= numTasks || TDR2 < 0)
							{
							}
							else
								universe[i].Tasks[j].vMachine = best_so_far.Tasks[TDR2].vMachine;
						}
						else if (r3 >= 0.5)
						{
							if (TDR1 >= numTasks || TDR1 < 0)
							{
							}
							else
								universe[i].Tasks[j].vMachine = best_so_far.Tasks[TDR1].vMachine;
						}
					}
					//((((((((((((((((((((((((((((((((((((((()))))))))))))))))))))))))))))))))))))))
				}
				universe[i].Calculatemakespan(0);
			}
			quickSort(universe, 0, 49);
			//(((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
			//################### Store best 5 solution  #################################

			for (int i = 0; i < 5; i++)
			{
				best_solutions[iter] = universe[i];
				iter++;
				
			}
			count++;
			//(((((((((((((((((((((((((((((((((((((())))))))))))))))))))))))))))))))))))))
			//################### Sending back best solutions as input  ##################
			if (count % 10 == 0)
			{
				universe = best_solutions;
				iter = 0;
			}
			
			cout << "\niteration: " << k << endl;
		}
		//max iterations reached


		cout << "best optimal solution: ";
		for (int i = 0; i < numTasks; i++)
		{
			cout << best_so_far.Tasks[i].vMachine.id << "     ";
		}
		double x=best_so_far.Calculatemakespan(1);
		cout << "\nwith makespan time: " << x << endl;
		for (int i = 0; i < numTasks; i++)
		{
			cout<<best_so_far.Tasks[i].no_of_instructions<<endl;
		}
		
		
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		cout << "\n execution time: " << duration.count()<<" MiliSeconds" << endl;
	}
	return 0;
}
//19
//210

//300