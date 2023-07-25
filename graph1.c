#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for representing a vertex in the graph
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Graph structure
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Function to create a new node
Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with a given number of vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));
    for (int i = 0; i < numVertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add an edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Function to print the graph and write to a file
void printGraph(Graph* graph, FILE* outputFile) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        fprintf(outputFile, "Adjacency list of vertex %d\n", i);
        while (temp) {
            fprintf(outputFile, "%d -> ", temp->dest);
            temp = temp->next;
        }
        fprintf(outputFile, "NULL\n");
    }
}

// Depth-First Search (DFS) algorithm
void DFS(Graph* graph, int vertex, bool visited[]) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->dest;
        if (!visited[adjVertex])
            DFS(graph, adjVertex, visited);
        temp = temp->next;
    }
}

// Breadth-First Search (BFS) algorithm
void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    visited[startVertex] = true;

    int queue[graph->numVertices];
    int front = 0, rear = 0;
    queue[rear++] = startVertex;

    printf("BFS Traversal: ");

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->dest;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    free(visited);
}

// Main function for reading inputs from file, constructing graph, and writing output to another file
int main() {
    FILE* inputFile = fopen("input.txt", "r");
    FILE* outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open files.\n");
        return -1;
    }

    int numVertices;
    fscanf(inputFile, "%d", &numVertices);

    Graph* graph = createGraph(numVertices);

    int src, dest;
    while (fscanf(inputFile, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }

    printGraph(graph, outputFile);

    // Perform DFS starting from vertex 0
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (int i = 0; i < graph->numVertices; i++)
        visited[i] = false;

    printf("DFS Traversal: ");
    DFS(graph, 0, visited);
    printf("\n");

    // Perform BFS starting from vertex 0
    printf("\n");
    BFS(graph, 0);
    printf("\n");

    fclose(inputFile);
    fclose(outputFile);

    free(visited);

    return 0;
}

