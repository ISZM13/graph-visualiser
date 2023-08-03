#include<iostream>
#include <list>

using namespace std;

// This class represents an undirected graph using adjacency list representation
class Graph
{
	int numberOfVertices; // No. of vertices

	// Pointer to an array containing adjacency lists
	list<int> *adjacencyList;
public:
	Graph(int numberOfVertices); // Constructor

	void addEdge(int from, int to);

	void bfsTraversal(int startingVertex);
};

Graph::Graph(int numberOfVertices)
{
	this->numberOfVertices = numberOfVertices;
	adjacencyList = new list<int>[numberOfVertices];
}

void Graph::addEdge(int v, int w)
{
	adjacencyList[v].push_back(w);
	adjacencyList[w].push_back(v);
}

void Graph::bfsTraversal(int vertex)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[numberOfVertices];
	for(int i = 0; i < numberOfVertices; i++)
		visited[i] = false;

	// Create a queue for bfsTraversal
	list<int> queue;

	// Mark the current node as visited and enqueue it
	visited[vertex] = true;
	queue.push_back(vertex);

	list<int>::iterator i;

	while(!queue.empty())
	{
		// Dequeue a vertex from queue and print it
		vertex = queue.front();
		cout << vertex << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued vertex. 
		// If a adjacent vertex has not been visited, then mark it visited and enqueue it
		for (i = adjacencyList[vertex].begin(); i != adjacencyList[vertex].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
}

int main()
{
    // Create a graph given in the above diagram
    Graph graph(7);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 1);
    graph.addEdge(2, 5);
    graph.addEdge(3, 6);

    cout << "Breadth First Traversal from 1 is : \n";
    graph.bfsTraversal(1);

    return 0;
}

