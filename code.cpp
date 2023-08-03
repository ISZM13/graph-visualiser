#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<pair<int, int>> readCSVFile(const string &filename)
{
    vector<pair<int, int>> result;

    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return result;
    }

    // Skip the first line (header)
    string line;
    getline(file, line);

    int from, to;
    char comma; // Used to handle the comma separator in the CSV file
    while (file >> from >> comma >> to)
    {
        result.push_back(make_pair(from, to));
    }

    return result;
}

// Function to construct an adjacency list from the given vector of pairs
vector<vector<int>> buildAdjacencyList(const vector<pair<int, int>> &edges, int numVertices)
{
    vector<vector<int>> adjList(numVertices);
    for (int i=0;i<(int)edges.size();i++)
    {
        int from = edges[i].first;
        int to = edges[i].second;
        adjList[from].push_back(to);
        adjList[to].push_back(from); // If the graph is undirected, add this line
    }
    return adjList;
}

// BFS traversal function
void BFS(const vector<vector<int>> &adjList, int startNode)
{
    vector<bool> visited(adjList.size(), false);
    queue<int> q;

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        cout << currentNode << " ";

        for (int neighbor : adjList[currentNode])
        {
            if (!visited[neighbor])
            {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// DFS traversal function (recursive)
void DFS(const vector<vector<int>> &adjList, int currentNode, vector<bool> &visited)
{
    visited[currentNode] = true;
    cout << currentNode << " ";

    for (int neighbor : adjList[currentNode])
    {
        if (!visited[neighbor])
        {
            DFS(adjList, neighbor, visited);
        }
    }
}

// Driver Code
int main()
{
    // Taking the Input Graph from .csv file.
    string csvFilename = "data.csv"; // CSV path
    vector<pair<int, int>> data = readCSVFile(csvFilename);

    // For printing the array of pair of vertices of each edge
    cout<<"All edges of the graph are:"<<endl;
    for (const auto &edge : data)
    {
        cout << "From: " << edge.first << ", To: " << edge.second << endl;
    }
    cout<<endl;
    
    // Calculating the number of vertices
    int numvertices = 0;
    set<int> vertices;
    for (const auto &edge : data)
    {
        vertices.insert(edge.first);
        vertices.insert(edge.second);
    }

    numvertices = (int)vertices.size();
    // cout<<numvertices<<" ene vertice bange"<<endl;
    // Conversion
    vector<vector<int>> adjList = buildAdjacencyList(data,numvertices);
    
    // Printing adjlist
    cout<<"AdjList is"<<endl;
    for(int i=0; i<(int)adjList.size();i++)
    {
        for(int j=0;j<(int)adjList[i].size();j++)
        {
            cout<<adjList[i][j]<<" ";
        }
        cout<<endl;
    }

    // BFS Traversal
    cout << "BFS Traversal: ";
    BFS(adjList, 0); // Starting BFS from node 0
    cout << endl;

    // DFS Traversal
    cout << "DFS Traversal: ";
    vector<bool> visited(numvertices, false);
    DFS(adjList, 0, visited); // Starting DFS from node 0
    cout << endl;

    char x;
    cout << "Press any key to exit.";
    cin >> x;
    return 0;
}
