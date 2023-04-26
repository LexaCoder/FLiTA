#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения графа
typedef struct Graph {
    int vertices;
    int **adjMatrix;
} Graph;

Graph *createGraph(int vertices);
void addEdge(Graph *graph, int src, int dest);
bool isConnected(Graph *graph);
void dfs(Graph *graph, int vertex, bool *visited);
void visualizeGraph(Graph *graph);

int main() {
    FILE *file;
    int src, dest;
    int max_vertex = 0;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Cannot open the file.\n");
        return 1;
    }

    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        if (src > max_vertex) max_vertex = src;
        if (dest > max_vertex) max_vertex = dest;
    }
    fseek(file, 0, SEEK_SET);

    Graph *graph = createGraph(max_vertex + 1);

    while (fscanf(file, "%d %d", &src, &dest) != EOF) {
        addEdge(graph, src, dest);
    }
    fclose(file);

    visualizeGraph(graph);
    printf("The graph is %sconnected.\n", isConnected(graph) ? "" : "not ");

    return 0;
}

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->adjMatrix = (int **)malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int *)calloc(vertices, sizeof(int));
    }

    return graph;
}

void addEdge(Graph *graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}

bool isConnected(Graph *graph) {
    bool *visited = (bool *)calloc(graph->vertices, sizeof(bool));
    dfs(graph, 0, visited);

    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i]) {
            free(visited);
            return false;
        }
    }
    free(visited);
    return true;
}

void dfs(Graph *graph, int vertex, bool *visited) {
    visited[vertex] = true;
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[vertex][i] && !visited[i]) {
            dfs(graph, i, visited);
        }
    }
}

void visualizeGraph(Graph *graph) {
    FILE *dot_file = fopen("graph.dot", "w");
    if (dot_file == NULL) {
        printf("Cannot create graph.dot file.\n");
        return;
    }

    fprintf(dot_file, "graph G {\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adjMatrix[i][j]) {
                fprintf(dot_file, "%d -- %d;\n", i, j);
                graph->adjMatrix[j][i] = 0; // Чтобы не выводить дублирующие ребра
            }
        }
    }
    fprintf(dot_file, "}\n");
    fclose(dot_file);
}


