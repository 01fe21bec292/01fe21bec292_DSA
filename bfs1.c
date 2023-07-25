#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
typedef struct
{
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

void enqueue(Queue *q, int value)
{
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue *q)
{
    int item = q->items[q->front];
    q->front++;
    return item;
}

int isempty(Queue *q)
 {
    return q->front > q->rear;
}
typedef struct
{
    int adjacencymatrix[MAX_NODES][MAX_NODES];
    int numNodes;
} Graph;

Graph* createGraph(int numnodes)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->numnodes = numnodes;

    int i, j;
    for (i = 0; i < numnodes; i++)
        {
        for (j = 0; j < numnodes; j++)
        {
            graph->adjacencymatrix[i][j] = 0;
        }
    }

    return graph;
}

void addedge(Graph* graph, int src, int dest)
{
    graph->adjacencymatrix[src][dest] = 1;
}
void bfs(Graph* graph, int startVertex, FILE* output)
 {
    Queue* q = malloc(sizeof(Queue));
    q->front = 0;
    q->rear = -1;

    int visited[MAX_NODES] = {0};
    visited[startvertex] = 1;
    enqueue(q, startvertex);

    while (!isempty(q))
    {
        int currentvertex = dequeue(q);
        fprintf(output, "%d ", currentvertex);

        int i;
        for (i = 0; i < graph->numnodes; i++)
        {
            if (graph->adjacencymatrix[currentvertex][i] && !visited[i])
             {
                visited[i] = 1;
                enqueue(q, i);
            }
        }
    }

    free(q);
}

int main()
{
    FILE* input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Failed to open input file.\n");
        return 1;
    }

    FILE* output = fopen("output.txt", "w");
    if (output == NULL)
    {
        printf("Failed to open output file.\n");
        return 1;
    }

    int numnodes, numedges;
    fscanf(input, "%d %d", &numnodes, &numedges);

    Graph* graph = createGraph(numNodes);

    int i;
    for (i = 0; i < numedges; i++)
    {
        int src, dest;
        fscanf(input, "%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    int startvertex;
    fscanf(input, "%d", &startvertex);

    bfs(graph, startvertex, output);

    fclose(input);
    fclose(output);

    return 0;
}

