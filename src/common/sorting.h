/*--------------------------------------------//
Sorting header
This is how we sort objects in more efficent
structures.
//--------------------------------------------*/
#ifndef SORT_H
#define SORT_H
class Sort;
class HeapSort;

/*--------------------------------------------//
Includes
//--------------------------------------------*/
	#include <stdlib.h>
	#include <stdio.h>

class Sort{
	protected:
		/*--------------------------------------------//
		Class Variables
		//--------------------------------------------*/
			void** objs;//our elements in the heap
			double** cost;//a defined value for compairing between two elements.
			int size;//the size of our element array

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void Swap(void* obj1, void* obj2);
			virtual void SortObjs(){}

	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			Sort();

		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void Insert(void* elmnt, double* value);
			void Remove(int index);
};

class HeapSort:public Sort{
	protected:
		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			void BuildHeap(int n, int i);
			void SortObjs();
	public:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			HeapSort();
			HeapSort(void** arr1, double** arr2, int s);
};

class BinarySearch{
	private:
		/*--------------------------------------------//
		Constructors
		//--------------------------------------------*/
			BinarySearch();
	protected:
	public:
		/*--------------------------------------------//
		Functions
		//--------------------------------------------*/
			static void* Search(void** arr, int size, void* tar);
};
#endif