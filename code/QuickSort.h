/*
*	Project: Enhanced Multiverse Optimixer
*	Authors : Rizwan Habib 19I-0657 , Talha Rizwan 19-652 , Noor Ul Eman 19I-0653 , Syed Iftikhar Mehdi 19I-0657
*	File : QuickSort.h
*   References : https://www.geeksforgeeks.org/quick-sort/
*	Date : 20-6-2021
*/

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>
using namespace std;

void swap(Universe *a, Universe *b)
{
	Universe t = *a;
	*a = *b;
	*b = t;
}

int partition(Universe *arr, int low, int high)
{
	double pivot = arr[high].MakespanTime;
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j].MakespanTime < pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(Universe *arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void printArray(Universe *arr, int num)
{
	int i;
	for (i = 0; i < 50; i++)
	{
		for (int j = 0; j < num; j++)
		{
			cout << arr[i].Tasks[j].vMachine.id << "    ";
		}
		cout << endl;
	}

	cout << endl;
}

#endif
