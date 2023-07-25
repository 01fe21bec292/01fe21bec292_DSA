#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
typedef struct {
    int items[MAX_NODES];
    int top;
} Stack;

void push(Stack *s, int value) {
    s->top++;
    s->items[s->top] = value;
}

int pop(Stack *s) {
    int item = s->items[s->top];
    s->top--;
    return item;
}

int isempty(Stack *s) {
    return s->top == -1;
}
typedef struct {
    int adjacencymatrix[MAX_NODES][MAX_NODES];
    int numnodes;
} Graph;

Graph* createGraph(int numnodes) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numnodes = numnodes;

    int i, j;
    for (i = 0; i < numnodes; i++) {
        for (j = 0; j < numnodes; j++) {
            graph->adjacencymatrix[i][j] = 0;
        }
    }

    return graph;
}

void addedge(Graph* graph, int src, int dest) {
    graph->adjacencymatrix[src][dest] = 1;
}
void dfs(Graph* graph, int startvertex, FILE* output) {
    Stack stack;
    stack.top = -1;

    int visited[MAX_NODES] = {0};

    push(&stack, startvertex);
    visited[startvertex] = 1;

    while (!isempty(&stack))
   {
        int currentvertex = pop(&stack);
        fprintf(output, "%d ", currentvertex);

        int i;
        for (i = 0; i < graph->numnodes; i++) {
            if (graph->adjacencymatrix[currentvertex][i] && !visited[i]) {
                push(&stack, i);
                visited[i] = 1;
            }
        }
    }
}

int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        printf("Failed to open input file.\n");
        return 1;
    }

    FILE* output = fopen("output.txt", "w");
    if (output == NULL) {
        printf("Failed to open output file.\n");
        return 1;
    }

    int numnodes, numedges;
    fscanf(input, "%d %d", &numnodes, &numedges);

    Graph* graph = createGraph(numnodes);

    int i;
    for (i = 0; i < numedges; i++) {
        int src, dest;
        fscanf(input, "%d %d", &src, &dest);
        addedge(graph, src, dest);
    }

    int startvertex;
    fscanf(input, "%d", &startvertex);

    dfs(graph, startvertex, output);

    fclose(input);
    fclose(output);

    printf("DFS traversal completed. The output has been written to the file 'output.txt'.\n");

    return 0;
}

