#include <iostream>
#include <vector>
#include <queue>
#include <nlohmann/json.hpp>
#include <fstream>
using namespace std;
using json = nlohmann::json;

// Structure to represent a node in the graph or tree
struct Node
{
    int value;
    vector<Node *> children;

    Node(int val) : value(val) {}
};

// Function to build a graph from user inputs
void buildGraph(vector<Node *> &graph)
{
    int n;
    cout << "Enter the number of nodes in the graph: ";
    cin >> n;
    graph.resize(n);

    for (int i = 0; i < n; ++i)
    {
        graph[i] = new Node(i);
    }

    cout << "Enter the connections between nodes (enter -1 to finish):\n";
    int node1, node2;
    while (true)
    {
        cin >> node1;
        if (node1 == -1)
            break;

        cin >> node2;
        if (node2 == -1)
            break;

        if (node1 < 0 || node1 >= n || node2 < 0 || node2 >= n)
        {
            cout << "Invalid node index! Try again.\n";
            continue;
        }

        graph[node1]->children.push_back(graph[node2]);
        graph[node2]->children.push_back(graph[node1]);
    }
}

// Function to build a tree from user inputs
Node *buildTree()
{
    int n;
    cout << "Enter the number of nodes in the tree: ";
    cin >> n;

    vector<Node *> nodes(n);
    for (int i = 0; i < n; ++i)
    {
        nodes[i] = new Node(i + 1);
    }

    cout << "Enter the parent for each node (enter -1 for root):\n";
    int parent;
    for (int i = 1; i < n; ++i)
    {
        cin >> parent;
        if (parent == -1)
        {
            nodes[0]->children.push_back(nodes[i]);
        }
        else
        {
            nodes[parent - 1]->children.push_back(nodes[i]);
        }
    }

    return nodes[0]; // Return the root of the tree
}

// BFS in a graph
void BFS_graph(vector<Node *> &graph, int startNode)
{
    if (graph.empty() || startNode < 0 || startNode >= graph.size())
    {
        cout << "Invalid input!" << endl;
        return;
    }

    queue<Node *> q;
    vector<bool> visited(graph.size(), false);

    q.push(graph[startNode]);
    visited[startNode] = true;

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        cout << current->value << " ";

        for (Node *neighbor : current->children)
        {
            if (!visited[neighbor->value])
            {
                q.push(neighbor);
                visited[neighbor->value] = true;
            }
        }
    }

    cout << endl;
}

// BFS in a tree
void BFS_tree(Node *root)
{
    if (!root)
    {
        cout << "Invalid input!" << endl;
        return;
    }

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        cout << current->value << " ";

        for (Node *child : current->children)
        {
            q.push(child);
        }
    }

    cout << endl;
}

// DFS in a graph
void DFS_graph(Node *node, vector<bool> &visited)
{
    if (!node)
        return;

    cout << node->value << " ";
    visited[node->value] = true;

    for (Node *neighbor : node->children)
    {
        if (!visited[neighbor->value])
        {
            DFS_graph(neighbor, visited);
        }
    }
}

// DFS in a tree
void DFS_tree(Node *node)
{
    if (!node)
        return;

    cout << node->value << " ";

    for (Node *child : node->children)
    {
        DFS_tree(child);
    }
}

// Function to delete the dynamically allocated memory of the graph or tree
void cleanupGraph(vector<Node *> &graph)
{
    for (Node *node : graph)
    {
        delete node;
    }
}

int main()
{
    system("cls");
    vector<Node *> graph;
    int choice;

    do
    {
        cout << "Please select a choice from this submenu.\n"
             << "1) Create a Graph and Perform BFS on Graph.\n"
             << "2) Create a Tree and Perform BFS on Tree.\n"
             << "3) Create a Tree and Perform DFS on Graph.\n"
             << "4) Create a Tree and Perform dFS on Tree.\n"
             << "5) leave this menu.\n";
    one:
        cout << "Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            buildGraph(graph);

            int startNode;
            cout << "Enter the starting node for BFS in the graph: ";
            cin >> startNode;
            cout << "BFS in graph from node " << startNode << ": ";
            BFS_graph(graph, startNode);
            string input;
            cout << "Do you wish to write the data of graph in external file?? (y/n): ";
            cin >> input;

            if (input == "y")
            {
                json data;
                data["name"] = "John Doe";
                data["age"] = 30;
                data["is_student"] = true;
                data["hobbies"] = {"Reading", "Hiking", "Cooking"};

                std::ofstream outputFile("data.json");
                if (outputFile.is_open())
                {
                    outputFile << data.dump(4); // "4" is for pretty printing with indentation
                    outputFile.close();
                    std::cout << "Data successfully written to data.json\n";
                }
                else
                {
                    std::cerr << "Error opening the file\n";
                }
            }
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            system("cls");
            Node *root = buildTree();

            cout << "\nBFS in tree: ";
            BFS_tree(root);
            int choose;
            cout << "\nWant to clear memory of saved tree?(press 1 if yes || 0 if no): ";
            cin >> choose;

            if (choose == 1)
            {
                // Clean up memory
                cleanupGraph(graph);
                delete root;
            }
            else
            {
                continue;
            }
            system("cls");
        }
        break;

        case 3:
        {
            system("cls");
            buildGraph(graph);
            int startNode;
            cout << "Enter the starting node for DFS in the graph: ";
            cin >> startNode;
            vector<bool> visited(graph.size(), false);
            cout << "DFS in graph from node " << startNode << ": ";
            DFS_graph(graph[startNode], visited);
            system("pause");
            system("cls");
        }
        break;

        case 4:
        {
            system("cls");
            Node *root = buildTree();
            cout << "\nDFS in tree: ";
            DFS_tree(root);
            cout << endl;
            int choose;
            cout << "\nWant to clear memory of saved tree?(press 1 if yes || 0 if no): ";
            cin >> choose;

            if (choose == 1)
            {
                // Clean up memory
                cleanupGraph(graph);
                delete root;
            }
            else
            {
                continue;
            }
            system("cls");
        }
        break;

        case 5:
        {
            system("cls");
        }

        case 6:
        {
            system("cls");
            goto two;
        }
        break;
        }
    } while (choice != 4);
    goto one;
    system("pause");
    system("cls");
two:
    return 0;
}