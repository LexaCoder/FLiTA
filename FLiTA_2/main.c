#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VERTICES 100
#define MAX_EDGES MAX_VERTICES * (MAX_VERTICES - 1) / 2

typedef struct {
    int from;
    int to;
} Edge;

typedef struct {
    int num_vertices;
    int num_edges;
    Edge edges[MAX_EDGES];
} Graph;

int isValidInput(char* input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i]) && input[i] != ' ' && input[i] != '\n') {
            return 0;
        }
    }
    return 1;
}

void inputGraph(Graph* g, FILE* fp) {
    char input[100];
    int validInput = 0;

    fgets(input, sizeof(input), fp);  // считываем первую строку из файла

    validInput = isValidInput(input);
    if (!validInput) {
        printf("Ошибка: некорректный ввод.\n");
        exit(1);
    }
    g->num_vertices = atoi(input);

    g->num_edges = 0;
    while (fgets(input, sizeof(input), fp) != NULL) {  // считываем остальные строки
        validInput = isValidInput(input);
        if (!validInput) {
            printf("Ошибка: некорректный ввод.\n");
            exit(1);
        }
        sscanf(input, "%d %d", &g->edges[g->num_edges].from, &g->edges[g->num_edges].to);
        g->num_edges++;
    }
}

void outputGraph(Graph* g) {
    FILE* fp;
    fp = fopen("graph.dot", "w");
    fprintf(fp, "graph G {\n");
    for (int i = 0; i < g->num_edges; i++) {
        fprintf(fp, " %d -- %d;\n", g->edges[i].from, g->edges[i].to);
    }
    fprintf(fp, "}");
    fclose(fp);
    system("dot -Tpng graph.dot -o graph.png");
    printf("Граф сохранен в файле graph.png\n");
}

int main() {
    Graph g;
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }
    inputGraph(&g, fp);
    fclose(fp);
    outputGraph(&g);
    return 0;
}
