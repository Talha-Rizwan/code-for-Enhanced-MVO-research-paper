/*
*	Project: Enhanced Multiverse Optimixer 
*	Authors : Rizwan Habib 19I-0657 , Talha Rizwan 19-652 , Noor Ul Eman 19I-0653 , Syed Iftikhar Mehdi 19I-0657
*	File : Universe.h
*	Date : 20-6-2021
*/

#ifndef UNIVERSE_H
#define UNIVERSE_H
#include <iostream>
#include <time.h>
using namespace std;

struct VM
{
public:
	int id;
	double MIPS;

public:
	VM() : MIPS(0), id(0)
	{
	}

	VM(double Mips, int ID) : MIPS(Mips), id(ID)
	{
	}
};

struct Task
{
public:
	int no_of_instructions;
	VM vMachine;

public:
	Task() : no_of_instructions(0), vMachine(0, -1)
	{
	}

	Task(int ins, VM vm) : no_of_instructions(ins), vMachine(vm)
	{
	}
};

class Universe
{
public:
	int no_of_tasks;
	Task *Tasks;
	VM *VirtualMachines;
	int numMachines;
	double MakespanTime;
	double probability;
	double NI;

public:
	Universe() : Tasks(nullptr), no_of_tasks(0), numMachines(0), MakespanTime(0), probability(-1), NI(-1)
	{
	}
	Universe (const Universe &other){
		cout<<"cpy jh"<<endl;
		NI=other.NI;
		MakespanTime=other.MakespanTime;
		no_of_tasks=other.no_of_tasks;
		numMachines=other.numMachines;
		probability=other.probability;
		Tasks==new Task[no_of_tasks];
		VirtualMachines=new VM[numMachines];
		for (int i = 0; i < no_of_tasks; i++)
		{
			Tasks[i]=other.Tasks[i];
		}
		for (int i = 0; i < numMachines; i++)
		{
			VirtualMachines[i]=other.VirtualMachines[i];
		}
		
		
	}
	Universe(int tasks, int Machines, double mkspan) : no_of_tasks(tasks), numMachines(Machines), MakespanTime(mkspan), probability(-1)
	{
		Tasks = new Task[tasks];
		VirtualMachines = new VM[Machines];
	}

	void set(int tasks, int Machines, double *notask, VM *vm)
	{
		no_of_tasks = tasks;
		numMachines = Machines;
		VirtualMachines = vm;

		Tasks = new Task[no_of_tasks];
		for (int i = 0; i < no_of_tasks; i++)
		{
			Tasks[i].no_of_instructions = notask[i];
		}
	}

	void AssignVMTasks()
	{
		for (int i = 0; i < no_of_tasks; i++)
		{

			int x = rand() % numMachines;
			for (int j = 0; j < numMachines; j++)
			{

				if (x == VirtualMachines[j].id)
				{
					Tasks[i].vMachine = VirtualMachines[j];
				}
			}
		}
	}

	double Calculatemakespan(int o)
	{
		double *count = new double[numMachines];
		for (int i = 0; i < numMachines; i++)
		{
			count[i] = 0;
		}
		
		for (int i = 0; i < no_of_tasks; i++)
		{
			for (int j = 0; j < numMachines; j++)
			{
				if (Tasks[i].vMachine.id == j)
				{
					count[j] += Tasks[i].no_of_instructions;
				}
			}
		}

		
		double *mkspan = new double[numMachines];
		for (int i = 0; i < numMachines; i++)
		{
			if (VirtualMachines[i].id == i)
			{
				mkspan[i] = count[i] / (double)((VirtualMachines[i].MIPS));
			}
		}
		if(o==1){
		for (int i = 0; i < numMachines; i++)
		{
			cout<<"VM["<<i<<"]:  "<<VirtualMachines[i].MIPS<<endl;
		}
		}
		double max = -1;
		for (int i = 0; i < numMachines; i++)
		{
			if (max < mkspan[i])
			{
				max = mkspan[i];
			}
		}
		this->MakespanTime = max;
		delete[] count;
		delete[] mkspan;
		return max;
	}
};

#endif