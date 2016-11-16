/************************************************************************
	
	https://www.owent.net/2009/07/ccpp%E8%AF%AD%E8%A8%80%E5%B8%B8%E7%94%A8%E6%8E%92%E5%BA%8F%E7%AE%97%E6%B3%95.html

	相关知识介绍（所有定义只为帮助读者理解相关概念，并非严格定义）;
	1、稳定排序和非稳定排序
	简单地说就是所有相等的数经过某种排序方法后，仍能保持它们在排序之前的相对次序，我们就
	说这种排序方法是稳定的。反之，就是非稳定的;
	比如：一组数排序前是a1,a2,a3,a4,a5，其中a2=a4，经过某种排序后为a1,a2,a4,a3,a5，
	则我们说这种排序是稳定的，因为a2排序前在a4的前面，排序后它还是在a4的前面。假如变成a1,a4,
	a2,a3,a5就不是稳定的了;
	2、内排序和外排序;
	在排序过程中，所有需要排序的数都在内存，并在内存中调整它们的存储顺序，称为内排序;
	在排序过程中，只有部分数被调入内存，并借助内存调整数在外存中的存放顺序排序方法称为外排序;
	3、算法的时间复杂度和空间复杂度;
	所谓算法的时间复杂度，是指执行算法所需要的计算工作量;
	一个算法的空间复杂度，一般是指执行这个算法所需要的内存空间;
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

  快速排序(quick sorting);
  最大时间代价：θ(n^2)	  ;
  最小时间代价：θ(n*logn) ;
  平均时间代价：θ(n*logn) ;
  最差情况下退化成冒泡排序法;

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

  插入排序(insert sorting);
  最大时间代价：θ(n^2)		;
  最小时间代价：θ(n)		;
  平均时间代价：θ(n^2)		 ;

/************************************************************************/


/// 
/// /Bubble Sort/;
///
/************************************************************************
	http://blog.csdn.net/liyuefeilong/article/details/46568551
	冒泡排序算法的整体流程如下;
	
	比较数组中两个相邻的元素。如果元素下标小的值比下标大的值要大，则两者进行交换;
	对数组的每一对相邻元素重复以上过程，从数组的底部比较到顶部。完成这一步后，数组顶部元素是最小的元素;
	顶部最小的元素无需再次比较，对其余的元素重复以上的步骤;
	持续每次对当前数组中越来越少的元素重复上面的步骤，直到没有任何一对元素需要比较;
	
	冒泡排序(bubble sorting);
	最大时间代价：θ(n^2)	  ;
	最小时间代价：θ(n^2)	  ;
	平均时间代价：θ(n^2)	  ;

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
	归并排序（英语：Merge sort，或mergesort）;
	是创建在归并操作上的一种有效的排序算法，效率为O(nlgn);
	1945年由约翰·冯·诺伊曼首次提出;
	该算法是采用分治法（Divide and Conquer）的典型应用，且各层分治递归可以同时进行;


	http://simplestcodings.blogspot.kr/2010/08/merge-sort-implementation-in-c.html
	Merge Sort is a technique in which we use the algorithm of divide and conquer.
	The input array is first divided into smaller sub-arrays, 
	which are sorted in turn and again merged to get the original array in a sorted manner.

/************************************************************************/
