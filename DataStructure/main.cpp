/************************************************************************
  windows7,64bit,visual studio2013

  THIS VSC++ Project is used for Data-Structure-Tutorial

  each pair of .h/.cpp files demonstrates a kind of DS or
  -	different implementations manners of the same DS....


  **more comments are required!
  **files and contents need optimizing.

/************************************************************************/
//  [11/15/2016 Administrator @gaohuancai QQ1293302539]
#include <stdio.h>
#include <stdlib.h>
#include "DSString.h"
#include <BinaryTree.h>
#include <BSTree.h>
#include <BTree.h>
#include <BreadthFirstSearch.h>
#include <BSTcpp.h>
#include <Graph/DSGraphA.h>
#include <Graph/DSGraphB.h>
#include <Graph/DSUDGraphADMatrix.h>
#include <Graph/DSUDGraphADList.h>
#include <Graph/UGraphImp.h>

///  >> 11/18/23/2016 BY.gaohuancai QQ1293302539 <<

int main()
{
	//nsBinaryTree::main_BinaryTree();
	//nsBSTree::main_BSTree();
	//nsBTree::main_BTree();
	//nsBreadthFirstSearch::main_BreadthFirstSearch();
	//BSTTree::main_BSTTree();
	//nsDSGraphA::main_DSGraphA();
	///nsDSGraphB::main_DSGraphB();

	///nsDSUDGraphCADMatrix::main_DSGraphADMatrix();
	///nsDSUDGraphCPPADMatrix::main_DSUDGraphCADMatrix();

	///nsDSUDGraphCADList::main_DSUDGraphCADList();
	///nsDSUDGraphCPPADList::main_DSUDGraphCPPADList();
	///nsDSUDGraphCPPADListEXTA::main_UDGraphADListEXTA();

	nsUGraphImp::main_UGraphImp();

	system("pause");
	return 0;
}

