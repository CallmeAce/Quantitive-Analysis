/* File:   sorting_algorithms.cpp
 * Name:   sorting algorithms
 * Author: XuanWang
 *
 */


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

/* Insertsort
 * stable sort
 * time complexity n^2
 * perform well when most of the numbers are sorted well 

 * */
//void insertsort( int array[], int n)
//{
//	int i; int j;int k;
//	for(i=1;i<n;i++)
//	{
//		for(j=i-1;j>=0;j--)
//			if(array[i]>array[j])
//				break;
//	
//	
//		if(j!=i-1)
//		{
//			int tmp = array[i];
//			for( k=i-1;k>j;k--)
//				array[k+1] = array[k];
//			array[j+1] = tmp;
//
//		}
//
//	}
//}
//
void insertsort(int array[],int n)
{
	int i,j,k;
	for(i=1;i<n;i++)
	{
		for(j=i-1;j>=0;j--)
		{
			if(array[i]>array[j])
				break;
		
		}
		
		int tmp = array[i];
		for(k=i-1;k>j;k--)
		{
		//	int tmp = array[i];
			array[k+1] = array[k];
		}
		array[j+1] = tmp;
	}
}

/*   Bubble sort  
 *	 stable sort
 *	 time complexity: n*n
 *	 the simplest sorting method 
 *   */

void swap(int array[],int a,int b)
{
	int tmp  = array[a];
	array[a] = array[b];
    array[b] = tmp;	
}


void bubblesort(int array[],int n)
{
	for(int i =0;i<n;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(array[j]>array[j+1])
				swap(array,j,j+1);			
		}
	}

}

/* QuickSort
 * unstable sorting
 * time complexity: n*logn, in worst case, n*n
 * widely used sorting method
 * perform better when n is big
 
*/
// recursive version
void quicksort(int array[],int start,int end)
{
	int i,j,pivot;
	pivot = array[start];  // use the first element as the pivot
	j = start;
	if(start<end)
	{
		for(i=start+1;i<=end;i++)
		{
			if(array[i]<pivot)
			{
				j++;
				swap(array,j,i);
			}
		}
		swap(array,start,j);
	
	
	quicksort(array,start,j-1);
	quicksort(array,j+1,end);
	}
}

/* HeapSort 
 * unstable sort
 * time complexity: n*log n
 * maybe the fastest method
 * Step1: build the heap
 * Step2: sort the heap
 * */
void heapdown(int array[],int start,int n)
{
	int tmp = array[start];
	int i = start;
	int j = 2*i+1;
	while(j<n)
	{
		if(j+1<n&&array[j]<array[j+1])
			j++;
		if(array[j]<tmp)
			break;
		array[i] = array[j];
		i = j;
		j= 2*i+1;

	}
	array[i] = tmp;
}

void buildheap(int array[],int n)
{
	for(int i = n/2-1;i>=0;i--)
	{
		heapdown(array,i,n);

	}

}

void heapsort(int array[],int n)
{
	buildheap(array,n);
	for(int i = n-1;i>=1;i--)
	{
		swap(array,i,0);
		heapdown(array,0,i);
	}
}
/* MergeSort
 * stable sort
 * timecomplexity: n* log n
 * perform better when n is large
 * merge a bunch of sorted elements together 
*/
// recursive version
//void merge(int array[],int a_start,int b_start,int n)
//{
//	int i = a_start;
//	int j = b_start;
//	int n_tmp = n-a_start;
//	int *tmp = new int[n_tmp];
//	int * t   = tmp;
//	while(i<=b_start&&j<=n)
//	{
//		if(array[i]>array[j])
//		{	
//			*t = array[j];
//			t++;
//			j++;
//		}
//		else
//		{
//			*t = array[i];
//			i++;
//			t++;
//		}
//	
//	}
//	while(j<=n)
//	{
//		*t= array[j];
//		t++;
//		j++;
//	}
//	while(i<=b_start)
//	{
//		*t= array[i];
//		t++;
//		i++;
//	}
//	for(int k= a_start;k<n;k++)
//		array[k]=tmp[k];
//}
//
//
//void mergesort(int array[],int a_start,int n)
//{
//	if(a_start<n)
//	{
//	   	int mid = a_start + (n-a_start)/2;
//		mergesort(array,a_start,mid-1);
//		mergesort(array,mid+1,n);
//		merge(array,a_start,mid,n);
//	}
//}

void merge(int array[],int a_start,int b_start,int end,int tmp[])
{
	int i = a_start;
	int j = b_start+1;
	int n = end;
	int k = 0;
	while(i<=b_start&&j<=n)
	{
		if(array[i]>array[j])
			tmp[k++] = array[j++];
		else
			tmp[k++] = array[i++];
	}

	while(i<=b_start)
		tmp[k++] = array[i++];
	while(j<=n)
		tmp[k++] = array[j++];

	for(int s=0;s<k;s++)
		array[a_start+s] = tmp[s];
			
}

void mergesort(int array[],int a_start,int n,int tmp[])
{
	if(a_start<n)
	{
		int mid = (n+a_start)/2;
		mergesort(array,a_start,mid,tmp);
		mergesort(array,mid+1,n,tmp);
		merge(array,a_start,mid,n,tmp);
	}
}

void selectsort(int array[],int n)
{
	for(int i =0;i<n;i++)
	{
		int min_p =i;
		int min_v = array[i];
		for(int j=i;j<n;j++)
		{
			if(min_v>array[j])
			{
				min_v = array[j];	
				min_p = j;
			}		
		}	
		swap(array,i,min_p);
	}
	
}

void shellsort(int array[],int n)
{
	
	for(int step = n/2;step>0;step = step/2)
	{
		for(int i = step;i<n;i++)
		{
			if(array[i]<array[i-step])
			{
				int j = i-step;
				int value = array[i];
				while(j>=0&&array[j]>value)
				{
					array[j+step] = array[j];
					j = j-step;
				}
				array[j+step]=value;
			}
		}
	}
}

int main(int argc,int *argv[])
{
	//array to be sorted
	int sort_array[] = {12,343,32,56,3,21,53,21,56,46,7,98,5};
	
	int n = sizeof(sort_array)/sizeof(sort_array[0]);
	
	/* all the sorting methods */
	//insertsort(sort_array,n);
	//bubblesort(sort_array,n);
    //quicksort(sort_array,0,n-1);
	//heapsort(sort_array,n);
	int * tmp = new int[n];
//	mergesort(sort_array,0,n-1,tmp);
//	selectsort(sort_array,n);
	shellsort(sort_array,n);
	for(int i = 0; i<n;i++)
		printf("%d ",sort_array[i]);
}
