/*--------------------------------------------//
Sorting definition
This is how we sort objects in more efficent
structures.
//--------------------------------------------*/
#ifndef SORTING
#define SORTING
	/*--------------------------------------------//
	Includes
	//--------------------------------------------*/
		#include "sorting.h"

	/*--------------------------------------------//
	Swap two elements
	//--------------------------------------------*/
		void Sort::Swap(void* obj1, void* obj2){
			void* temp = obj1;
			obj1 = obj2;
			obj2 = temp;
			temp = NULL;
		}

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		Sort::Sort(){
			objs = NULL;
			cost = NULL;
			size = 0;
		}

	/*--------------------------------------------//
	Inserion
	//--------------------------------------------*/
		void Sort::Insert(void* elmnt, double* value){
			//resize our arrays
			void** newobjs = (void**) realloc(objs, sizeof(void*)*(size+1));
			double** newcost = (double**) realloc(cost, sizeof(double*)*(size+1));

			//verify reizing worked
			if (newobjs != NULL && newcost != NULL) {
				//insert new element
				objs = newobjs;
				cost = newcost;

				objs[size] = elmnt;
				cost[size] = value;
				size++;
				//resort arrays
				SortObjs();
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		}

	/*--------------------------------------------//
	Deletion
	//--------------------------------------------*/
		void Sort::Remove(int index){
			//resize our arrays
			void** newobjs = (void**) realloc(objs, sizeof(void*)*(size-1));
			double** newcost = (double**) realloc(cost, sizeof(double*)*(size-1));

			//verify reizing worked
			if (newobjs != NULL && newcost != NULL) {
				//remove element
				for(int i, j = 0; i < size; i++){
					if (i != index){
						newobjs[j] = objs[i];
						newcost[j] = cost[i];
						j++;
					}
				}

				objs = newobjs;
				cost = newcost;
				size--;
			}else{
				puts ("Error (re)allocating memory");
				exit (1);
			}
		}

	/*--------------------------------------------//
	Maintanence
	//--------------------------------------------*/
		void HeapSort::BuildHeap(int n, int i){
			int l = 2*i + 1;
		    int r = 2*i + 2;
		    int largest;
		 
		    //find largest of i and l
		    if (l < n && *(cost[l]) > *(cost[i])){
		        largest = l;
		    }else{
		    	largest = i;
		    }
		 
		    // If right child is larger than largest so far
		    if (r < n && *(cost[r]) > *(cost[largest]))
		        largest = r;
		 
		    // If largest is not root
		    if (largest != i){
		        Swap(objs[i], objs[largest]);
		        Swap(cost[i], cost[largest]);
		 
		        // Recursively heapify the affected sub-tree
		        BuildHeap(n, largest);
		    }
		}
		void HeapSort::SortObjs(){
			//populate heap
			for (int i = size/2 -1; i>=0; i--){
				BuildHeap(size, i);
			}

			//pull from top of heap into array
			//this does our sorting
			for (int i=size -1; i>=0; i--){
				//move current root to the end
				Swap(objs[0], objs[i]);
				Swap(cost[0], cost[i]);

				//call max heapify on the reduced heap
				BuildHeap(i, 0);
			}
		}

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		HeapSort::HeapSort():Sort(){}
		
	/*--------------------------------------------//
	Initialized constructor
	//--------------------------------------------*/
		HeapSort::HeapSort(void** arr1, double** arr2, int s){
			objs = arr1;
			cost = arr2;
			size = s;
			SortObjs();
		}

	/*--------------------------------------------//
	Default constructor
	//--------------------------------------------*/
		BinarySearch::BinarySearch(){}

	/*--------------------------------------------//
	Binary Search for tar
	Uses recursion
	//--------------------------------------------*/
		void* BinarySearch::Search(void** arr, int size, void* tar){
			if (size < 1)
				return NULL;

			void* ptr = arr[size/2];
			if (ptr == tar)
				return arr[size/2];

			if (ptr < tar){
				return Search(arr, size/2, tar);
			}else{
				return Search(&arr[size/2], size/2, tar);
			}
		}
#endif