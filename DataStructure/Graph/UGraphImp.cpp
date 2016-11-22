/************************************************************************


  http://www.codebangla.net/2016/09/graph.html


/************************************************************************/
#include "UGraphImp.h"
#include<stdlib.h>
#include<iostream>
namespace nsUGraphImp
{
	using namespace std;


	struct Edge
	{
		int edgeData;
		struct Edge* edgeNext;
	} *edge;

	struct Vertex
	{
		int vertexData;
		struct Vertex* vertexNext;
		struct Edge* edgeHead;
	} *vertex;


	struct Head
	{
		struct Vertex *p;
	} *head;

	void createHead()
	{
		head = (struct Head*)malloc(sizeof(struct Head));
		head->p = NULL;
	}

	/// create vertex & edge ...
	void createVertex()
	{
		vertex = (struct Vertex*)malloc(sizeof(struct Vertex));
		vertex->vertexNext = NULL;
		vertex->edgeHead = NULL;
		cout << "Input Vertex: " << endl;
		cin >> vertex->vertexData;
	}

	void createEdge()
	{
		edge = (struct Edge*)malloc(sizeof(struct Edge));
		edge->edgeNext = NULL;
		cout << "Related edge: " << endl;
		cin >> edge->edgeData;
	}

	///add vertex & edge...

	void addEdge(int v);
	void addVertex()
	{
		createVertex();
		struct Vertex* temp;
		if (head->p != NULL)
		{
			temp = head->p;
			while (temp->vertexNext != NULL){
				temp = temp->vertexNext;
			}
			temp->vertexNext = vertex;
		}
		else
			head->p = vertex;

		int i, x;
		cout << "Total related edge number: " << endl;
		cin >> x;
		for (i = 0; i < x; i++){
			addEdge(vertex->vertexData);
		}
	}

	void addEdge(int v)
	{

		struct Vertex* temp = head->p;
		struct Edge* t;
		while (temp->vertexData != v)
		{
			temp = temp->vertexNext;
		}

		createEdge();
		edge->edgeNext = temp->edgeHead;
		temp->edgeHead = edge;

	}

	/// Delete vertex & edge...
		void deleteEdge(int v, int e)
	{
		struct Vertex* temp = head->p;
		struct Edge *t1 = nullptr, *t2 = nullptr;
		int i = 0;
		while (temp->vertexData != v)
		{
			if (temp->vertexNext != NULL){
				temp = temp->vertexNext;
			}
			else{
				i = 1;
				break;
			}
		}
		if (i == 1 || temp->edgeHead == NULL)
			return;
		t1 = temp->edgeHead;
		while (t1->edgeData != e)
		{
			if (t1->edgeNext != NULL){
				t2 = t1;
				t1 = t1->edgeNext;
			}
			else{
				i = 1;
				break;
			}
		}
		if (i == 1)
			return;
		if (temp->edgeHead->edgeData == t1->edgeData){
			//delete 1st
			temp->edgeHead = t1->edgeNext;
			free(t1);
		}
		else if (t1->edgeNext == NULL){
			//delete last
			free(t1);
			t2->edgeNext = NULL;
		}
		else{
			//delete mid
			t2->edgeNext = t1->edgeNext;
			free(t1);
		}
	}

	void deleteVertex()
	{
		if (head->p != NULL){
			int x, i = 0;
			cout << "Enter vertex to delete: ";
			cin >> x;
			struct Vertex *t = nullptr, *temp = head->p;
			while (temp->vertexData != x)
			{
				t = temp;
				temp = temp->vertexNext;
				if (temp == NULL){
					i = 1;
					cout << "Vertex unmatched!" << endl;
					break;
				}
			}
			if (i == 1)
				return;
			//edges of the vertex are going to be deleted
			if (temp->edgeHead != NULL){
				struct Edge* temp1 = temp->edgeHead;
				while (temp->edgeHead != NULL)
				{
					deleteEdge(temp->vertexData, temp->edgeHead->edgeData);
					// cout<<"Delete Edge"<<endl;
				}
			}
			//all edge of the vertex are deleted

			//Now the vertex is going to be deleted
			if (temp->vertexData == head->p->vertexData){
				head->p = temp->vertexNext;
				free(temp);
			}
			else if (temp->vertexNext == NULL){
				free(temp);
				t->vertexNext = NULL;
			}
			else{
				t->vertexNext = temp->vertexNext;
				free(temp);
			}
			//vertex deleted

			//relative edge delete

			temp = head->p;
			while (temp != NULL)
			{
				deleteEdge(temp->vertexData, x);
				temp = temp->vertexNext;
			}
		}
		else
			cout << "Add vertex first!" << endl;

	}

	/// print & main...
		void print()
	{
		struct Vertex *temp = head->p;
		while (temp != NULL){

			cout << temp->vertexData << " ";
			struct Edge* temp2 = temp->edgeHead;
			while (temp2 != NULL){
				cout << temp2->edgeData << " ";
				temp2 = temp2->edgeNext;
			}
			cout << endl;
			temp = temp->vertexNext;
		}
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	int main_UGraphImp()
	{

		createHead();

		addVertex();
		addVertex();
		addVertex();
		addVertex();
		addVertex();
		print();
		deleteVertex();
		print();


		return 0;
	}
}
