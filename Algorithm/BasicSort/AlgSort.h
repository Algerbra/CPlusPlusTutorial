/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************

Quick-Sort

http://www.algolist.net/Algorithms/Sorting/Quicksort
http://blog.csdn.net/v_JULY_v/article/details/6116297

时间复杂度 (n*lg(n));
最     差	(n^2);

空间复杂度 (n*lg(n));


/************************************************************************/
///  >> 11/16/9/2016 BY.gaohuancai QQ1293302539 <<

namespace nsAlgSort
{
	class AlgSort
	{
	public:
		static void quickSort(int arr[], int left, int right);

		static void bubbleSort(int arr[], int arrSz);
		static void bubbleSortA(int arr[], int arrSz);

		static void insertSort(int arr[], int arrSz);

		static void selectSort(int arr[], int arrSz);

		///
		static void mergeSortedArrays(int dataA[], int dataB[], int dataaSz, int databSz, int data[]);

		static void mergeSort(int data[], int left, int right);


		static void heapSort(int arr[], int arrSz);

	public:


	};

	extern void logArray(int data[], int lind, int dataSz, int pivot, const char * str = "Log Element");


	int main_AlgSort();
}
