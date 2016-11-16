/************************************************************************
	
	https://www.owent.net/2009/07/ccpp%E8%AF%AD%E8%A8%80%E5%B8%B8%E7%94%A8%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95.html

	���֪ʶ���ܣ����ж���ֻΪ�������������ظ�������ϸ��壩;
	1���ȶ�����ͷ��ȶ�����
	�򵥵�˵����������ȵ�������ĳ�����򷽷������ܱ�������������֮ǰ����Դ������Ǿ�
	˵�������򷽷����ȶ��ġ���֮�����Ƿ��ȶ���;
	���磺һ��������ǰ��a1,a2,a3,a4,a5������a2=a4������ĳ�������Ϊa1,a2,a4,a3,a5��
	������˵�����������ȶ��ģ���Ϊa2����ǰ��a4��ǰ�棬�������������a4��ǰ�档������a1,a4,
	a2,a3,a5�Ͳ����ȶ�����;
	2���������������;
	����������У�������Ҫ������������ڴ棬�����ڴ��е������ǵĴ洢˳�򣬳�Ϊ������;
	����������У�ֻ�в������������ڴ棬�������ڴ������������еĴ��˳�����򷽷���Ϊ������;
	3���㷨��ʱ�临�ӶȺͿռ临�Ӷ�;
	��ν�㷨��ʱ�临�Ӷȣ���ִָ���㷨����Ҫ�ļ��㹤����;
	һ���㷨�Ŀռ临�Ӷȣ�һ����ִָ������㷨����Ҫ���ڴ�ռ�;
/************************************************************************/


/// 
/// /Quick sort/;
///
/************************************************************************

  http://codereview.stackexchange.com/questions/77782/quick-sort-implementation
  The classic quick-sort is done in 5 stages:

  find a 'pivot value'.
  move all values less than (or equal to) the pivot value to 'the left'.
  move all values larger than the pivot to 'the right'.
  quick-sort the values less than(or equal)
  quick-sort the values larger than.

  ��������(quick sorting);
  ���ʱ����ۣ���(n^2)	  ;
  ��Сʱ����ۣ���(n*logn) ;
  ƽ��ʱ����ۣ���(n*logn) ;
  ���������˻���ð������;

/************************************************************************/


///
/// /Inersion Sort/;
///
/************************************************************************

  http://mathbits.com/MathBits/CompSci/Arrays/Insertion.htm


  The insertion sort splits an array into two sub-arrays. 
  The first sub-array (such as the cards in your hand) is sorted 
  and increases in size as the sort continues. 

  The second sub-array (such as the cards to be picked up) is unsorted, 
  contains all the elements to yet be inserted into the first sub-array, 
  and decreases in size as the sort continues.

  ��������(insert sorting);
  ���ʱ����ۣ���(n^2)		;
  ��Сʱ����ۣ���(n)		;
  ƽ��ʱ����ۣ���(n^2)		 ;

/************************************************************************/


/// 
/// /Bubble Sort/;
///
/************************************************************************
	http://blog.csdn.net/liyuefeilong/article/details/46568551
	ð�������㷨��������������;
	
	�Ƚ��������������ڵ�Ԫ�ء����Ԫ���±�С��ֵ���±���ֵҪ�������߽��н���;
	�������ÿһ������Ԫ���ظ����Ϲ��̣�������ĵײ��Ƚϵ������������һ�������鶥��Ԫ������С��Ԫ��;
	������С��Ԫ�������ٴαȽϣ��������Ԫ���ظ����ϵĲ���;
	����ÿ�ζԵ�ǰ������Խ��Խ�ٵ�Ԫ���ظ�����Ĳ��裬ֱ��û���κ�һ��Ԫ����Ҫ�Ƚ�;
	
	ð������(bubble sorting);
	���ʱ����ۣ���(n^2)	  ;
	��Сʱ����ۣ���(n^2)	  ;
	ƽ��ʱ����ۣ���(n^2)	  ;

/************************************************************************/

///
/// /Merge Sorted Arrays/
///
/************************************************************************

	http://www.algolist.net/Algorithms/Merge/Sorted_arrays

	Algorithm to merge sorted arrays

	In the article we present an algorithm for merging two sorted arrays. 
	One can learn how to operate with several arrays and master read/write indices. 
	Also, the algorithm has certain applications in practice, for instance in merge sort.

	Merge algorithm

	Assume, that both arrays are sorted in ascending order and we want resulting array to maintain the same order. 
	Algorithm to merge two arrays A[0..m-1] and B[0..n-1] into an array C[0..m+n-1] is as following:

			Introduce read-indices i, j to traverse arrays A and B, accordingly. 
			Introduce write-index k to store position of the first free cell in the resulting array. 
			By default i = j = k = 0.

			At each step: if both indices are in range (i < m and j < n), 
			choose minimum of (A[i], B[j]) and write it to C[k]. 
			Otherwise go to step 4.

			Increase k and index of the array, algorithm located minimal value at, by one. 
			Repeat step 2.

			Copy the rest values from the array, 
			which index is still in range, to the resulting array.


	Complexity analysis

	Merge algorithm's time complexity is O(n + m). 
	Additionally, it requires O(n + m) additional space to store resulting array.
/************************************************************************/

/// 
/// /Merge Sort/
///
/************************************************************************

	http://quiz.geeksforgeeks.org/merge-sort/
	Merge Sort
	MergeSort is a Divide and Conquer algorithm. 
	It divides input array in two halves, 
	calls itself for the two halves and then merges the two sorted halves. 
	The merge() function is used for merging two halves. 
	The merge(arr, l, m, r) is key process that assumes that 
	arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one. 
	See following C implementation for details.

			MergeSort(arr[], l,  r)
			If r > l
				1. Find the middle point to divide the array into two halves:
				middle m = (l+r)/2
				2. Call mergeSort for first half:
				Call mergeSort(arr, l, m)
				3. Call mergeSort for second half:
				Call mergeSort(arr, m+1, r)
				4. Merge the two halves sorted in step 2 and 3:
				Call merge(arr, l, m, r)


	https://zh.wikipedia.org/wiki/%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F
	�鲢����Ӣ�Merge sort����mergesort��;
	�Ǵ����ڹ鲢�����ϵ�һ����Ч�������㷨��Ч��ΪO(nlgn);
	1945����Լ�����롤ŵ�����״����;
	���㷨�ǲ��÷��η���Divide and Conquer���ĵ���Ӧ�ã��Ҹ�����εݹ����ͬʱ����;


	http://simplestcodings.blogspot.kr/2010/08/merge-sort-implementation-in-c.html
	Merge Sort is a technique in which we use the algorithm of divide and conquer.
	The input array is first divided into smaller sub-arrays, 
	which are sorted in turn and again merged to get the original array in a sorted manner.

/************************************************************************/
