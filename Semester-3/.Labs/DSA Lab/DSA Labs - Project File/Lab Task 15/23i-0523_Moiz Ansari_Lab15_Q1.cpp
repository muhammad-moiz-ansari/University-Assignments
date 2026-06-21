#include <iostream>
using namespace std;

class GraphNode
{
public:
	int id;
	GraphNode** list;
	GraphNode(int i = 0, GraphNode** l = NULL)
	{
		id = i;
		list = l;
	}

};

class Node
{
public:
	int data;
	Node* next;
	Node(int d = 0, Node* n = NULL)
	{
		data = d;
		next = n;
	}
};

//Adjacency List : // it’s a linked list class called adjlist
class AdjList
{
public:
	int data;
	Node* head;
	AdjList(int d = 0, Node* h = NULL)
	{
		data = d;
		head = h;
	}
	void Insert(Node* NewNode)
	{
		Node* temp = head;
		head = NewNode;
		NewNode->next = temp;
		temp = NULL;
	}
	void Display()
	{
		cout << data << ": [  ";
		Node* temp = head;
		while (temp)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}
		cout << "\b\b ]";
	}
};

//Graph:
class Graph
{
public:
	int maxVertices;  // max no of vertices in your graph
	int noOfVertices; // initially 0, increments with every call to createVertex function.
					// So basically its kind of counter
	AdjList* list = NULL;
	Graph(int maxv = 5)
	{
		maxVertices = maxv;
		list = new AdjList[maxVertices];
		noOfVertices = 0;
	}
	//Results:
	//Constructor.Creates an empty graph.Allocates enough memory for a graph
	//containing maxNumber vertices.

	Node* createVertex(int data)
	{
		list[noOfVertices++].data = data;
		return new Node(data);
	}

	void insert(int ind, int value)
	{
		list[ind].Insert(new Node(value));
	}
	// Results :
	// Create and return a Vertex.
	void insertEdge(int src, int dest)
	{
		if (src == dest)
			return;

		int ind = 0;
		bool s = 0, d = 0;
		for (int i = 0; i < noOfVertices; ++i)
		{
			if (list[i].data == src)
			{
				s = 1;
				ind = i;
			}
			if (list[i].data == dest)
				d = 1;
		}
		if (!d)
		{
			list[noOfVertices++].data = dest;
		}
		if (s)
		{
			insert(ind, dest);
		}
	}
	// Requirements :
	// The graph includes vertices source and destination.
	// Results :
	// Inserts an undirected edge connecting vertices source and destination into a graph.
	void showGraphStructure()
	{
		for (int i = 0; i < noOfVertices; ++i)
		{
			list[i].Display();
			cout << endl;
		}
		cout << "\n\n";
	}
	// Results :
	// Outputs a graph with the vertices in array form and the edges in adjacency list form.If the
	// graph is empty, outputs “Empty graph”.Note that this operation is intended for
	// testing / debugging purposes only.

	~Graph()
	{
		delete[] list;
	}
	//Results :
	//Destructor.Deallocates(frees) the memory used to store a graph.
};

int main()
{
	Graph g(5);

	g.createVertex(1);
	g.createVertex(2);
	g.insertEdge(1, 2);
	g.insertEdge(2, 5);
	g.insertEdge(2, 4);
	g.insertEdge(2, 3);
	g.insertEdge(2, 1);
	g.insertEdge(5, 1);
	g.insertEdge(5, 2);
	g.insertEdge(5, 4);

	g.showGraphStructure();



	return 0;
}