/*
*	Project: Enhanced Multiverse Optimixer
*	Authors : Rizwan Habib 19I-0657 , Talha Rizwan 19-652 , Noor Ul Eman 19I-0653 , Syed Iftikhar Mehdi 19I-0657
*	File : RouletteWheelSelction.h
*	Date : 20-6-2021
*/

#pragma once
#include "universe.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int RouletteWheel(Universe *universe)
{
	srand((unsigned)time(NULL));

	double mkspanSum = 0, sumProbability = 0;

	for (int i = 0; i < 50; i++)
	{
		mkspanSum += universe[i].MakespanTime;
	}

	int probability = 0;
	for (int i = 0; i < 50; i++)
	{
		universe[i].probability = (universe[i].MakespanTime / mkspanSum);
		sumProbability += universe[i].probability;
	}

	int univserseIndex = -1;
	float random = 0.0;

	double previous = 0;
	for (int i = 0; i < 50; i++)
	{
		random = (double)rand() / RAND_MAX;
		if (random < universe[i].probability - previous /*and random < universe[i + 1].probability*/)
		{
			univserseIndex = i;
			break;
		}
		previous = universe[i].probability;
	}

	if (univserseIndex == -1)
	{
		univserseIndex = rand() % 50;
	}

	return univserseIndex;
}