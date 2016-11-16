/************************************************************************/
/*                                                                      */
/************************************************************************/

#include <stdio.h>

#include "AlgSort.h"

void logArray(int data[], int lind, int dataSz, int pivot, const char * str/*=""*/)
{
	static int loopCounter = 0;
	fprintf(stderr, "[%s][LT= %d]\n[L= %d],[R= %d]\n[Pivt= %d]\n\t\t",  str, ++loopCounter,lind, dataSz, pivot);
	for (int i = 0; i < dataSz; ++i)
		fprintf(stderr, "%4d", data[i]);

	fprintf(stderr, "\n");

}

/// Quick Sort;
void AlgSort::quickSort(int data[], int srcLindex, int srcRindex)
{
	if (srcLindex >= srcRindex || NULL == data)
		return;

	int leftIndex = srcLindex;
	int rightIndex = srcRindex;

	//potential for integer overflow for calculating the mid-point index of the arr;
	int pivot = data[srcLindex + ( srcRindex - srcLindex) / 2];

	//TODO:
	logArray(data, srcLindex, srcRindex + 1, pivot, "before");
	//partition
	int temp;
	while (leftIndex <= rightIndex)
	{
		while (data[leftIndex] < pivot)
			++leftIndex;

		while (data[rightIndex] > pivot)
			--rightIndex;

		if (leftIndex <= rightIndex)
		{
			temp = data[leftIndex];
			data[leftIndex] = data[rightIndex];
			data[rightIndex] = temp;

			++leftIndex;
			--rightIndex;
		}

	}//while (i <= j)

	//recursion;
	if (srcLindex < rightIndex)//this could be commented;
		quickSort(data, srcLindex, rightIndex);

	if (leftIndex < srcRindex)//this could be commented;
		quickSort(data, leftIndex, srcRindex);
}

/// Bubble Sort;
void AlgSort::bubbleSort(int data[], int dataSz)
{
	for (int iLoop = 0; iLoop < dataSz; ++iLoop)//external for number serial loop;
	{
		//TODO:
		logArray(data, 0, dataSz, 0, "before");

		for (int iEle = 0; iEle < dataSz - iLoop - 1; ++iEle)//internal for element comparison
		{
			if (data[iEle] > data[iEle + 1])
			{
				int tmp = data[iEle];
				data[iEle] = data[iEle + 1];
				data[iEle + 1] = tmp;
			}

		}//for(iElement)

	}//for (iLoop)

}
void AlgSort::bubbleSortA(int data[], int dataSz)
{
	for (int iLoop = 0; iLoop < dataSz; ++iLoop)
	{
		bool bubbleFinished = true;
		logArray(data, 0, dataSz, bubbleFinished, "before");
		for (int iBubble = 0; iBubble < (dataSz - iLoop - 1); ++iBubble)
		{
			if (data[iBubble] > data[iBubble + 1])
			{

				int tmp = data[iBubble];
				data[iBubble] = data[iBubble + 1];
				data[iBubble + 1] = tmp;

				bubbleFinished = false;
			}
		}

		if (bubbleFinished)
			break;
	}
}

/// Insert Sort;
void AlgSort::insertSort(int data[], int dataSz)
{
	int tmp;
	for (int iUnorder = 1; iUnorder < dataSz; ++iUnorder)//loop for unordered serial;
	{
		tmp = data[iUnorder];
		logArray(data, 0, dataSz, 0, "before");
		int iOrder;
		//[loop] (index > 0) && the new element is smaller than the older;
		for (iOrder = iUnorder; iOrder > 0 && data[iOrder - 1] > tmp; --iOrder)//loop for ordered serial;
		{
			data[iOrder] = data[iOrder - 1];//the ordered serial move backward UNIT position;
		}

		data[iOrder] = tmp;

	}//for (iUnorder)
}

/// Select Sort;
void AlgSort::selectSort(int data[], int dataSz)
{
	for (int iminIndex = 0; iminIndex < dataSz; ++iminIndex)
	{
		int minIndex = iminIndex;

		//TODO:
		logArray(data, 0, dataSz, data[minIndex], "before");
		for (int iLoop = iminIndex + 1; iLoop < dataSz; ++iLoop)
		{
			if (data[minIndex] > data[iLoop])
				minIndex = iLoop;

		}

		if (minIndex != iminIndex)
		{
			int tmp = data[minIndex];
			data[minIndex] = data[iminIndex];
			data[iminIndex] = tmp;
		}

	}

}


/// Merge Sorted Array;
void AlgSort::mergeSortedArrays(int dataA[], int dataB[], int dataaSz, int databSz, int data[])
{
	int itoDataA = 0;
	int itoDataB = 0;
	int itoDataC = 0;
	while (itoDataA < dataaSz && itoDataB < databSz)
	{
		if (dataA[itoDataA] < dataB[itoDataB])
			data[itoDataC++] = dataA[itoDataA++];
		else
			data[itoDataC++] = dataB[itoDataB++];
	}

	while (itoDataA < dataaSz)
		data[itoDataC++] = dataA[itoDataA++];
	while (itoDataB < databSz)
		data[itoDataC++] = dataB[itoDataB++];
}

void mergeSort_Merge(int data[], int low, int pivot, int hight)
{
	int n1 = pivot - low + 1;
	int n2 = hight - pivot;

	/* create temp arrays */
	int * larr = new int[n1];
	int * rarr = new int[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (int indexL = 0; indexL < n1; indexL++)
		larr[indexL] = data[low + indexL];
	for (int indexR = 0; indexR < n2; indexR++)
		rarr[indexR] = data[pivot + 1 + indexR];

	/* Merge the temp arrays back into arr[l..r]*/
	int indexL = 0;
	int indexR = 0;
	int indexData = low;
	while (indexL < n1 && indexR < n2)
	{
		if (larr[indexL] <= rarr[indexR])
			data[indexData++] = larr[indexL++];
		else
			data[indexData++] = rarr[indexR++];
	}

	while (indexL < n1)
		data[indexData++] = larr[indexL++];

	while (indexR < n2)
		data[indexData++] = rarr[indexR++];
	logArray(data, 0, hight + 1,pivot, "before");

}
void AlgSort::mergeSort(int data[], int left, int right)
{

	if (left < right)
	{
		int pivot = left + (right - left) / 2; //Same as (l+r)/2 but avoids overflow for large l & h
		mergeSort(data, left, pivot);
		mergeSort(data, pivot + 1, right);
		mergeSort_Merge(data, left, pivot, right);
	}
}

void AlgSort::heapSort(int arr[], int arrSz)
{

}
