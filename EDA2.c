#include <stdio.h>

#define MAX_VERTICES 100
int color[4];  // 0 ou 1 (duas cores), -1 = incolor
int numVertices, numArestas;

#define ARESTAS 10
#define VERTICES 10

typedef struct{
    int matriz[VERTICES][ARESTAS];
    int numVertices;
    int numArestas;
}Grafo;

void preencherMatriz(Grafo *g){
    FILE *arq;
    char linha[100];
    int i = -1; int j = 0;
    arq = fopen("exemplo.txt", "r");
    if (arq == NULL) {
        printf("erro ao preencher grafo");
    }
    while(fgets(linha, sizeof(linha), arq)){
        j=0;
        while(linha[j]!='\0' && linha[j] != '\n'){
            if(linha[j] == '0'){
                g->matriz[i][j] = 0;
            }else if(linha[j] == '1'){
                g->matriz[i][j] = 1;
            }
            j++;
        }
        i++;
    }
    fclose(arq);
}

void mostrarMatriz(Grafo *g){
    printf("\nMatriz de incidencia:\n");
    g->numVertices = numVertices;
    g->numArestas = numArestas;
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numArestas; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

// Retorna 1 se grafo for bipartido, 0 caso contrário
int dfs(Grafo *g, int v, int c) {
    color[v] = c;

    for (int a = 0; a < numArestas; a++) {
        if (g->matriz[a][v] == 0)
            continue;

        // Procurar o outro vértice da mesma aresta
        for (int u = 0; u < numVertices; u++) {
            if (u != v && g->matriz[a][u]) {
                if (color[u] == -1) {
                    if (!dfs(g, u, 1 - c))
                        return 0;
                } else if (color[u] == c) {
                    return 0;  // mesma cor = não bipartido
                }
            }
        }
    }
    return 1;
}

int isBipartido(Grafo *g) {
    for (int i = 0; i < numVertices; i++)
        color[i] = -1;

    for (int i = 0; i < numVertices; i++)
        if (color[i] == -1)
            if (!dfs(g, i, 0))
                return 0;
    return 1;
}

int main() {
    Grafo grafo;
    numVertices = 4;
    numArestas = 4;
    preencherMatriz(&grafo);
    mostrarMatriz(&grafo);
    if (isBipartido(&grafo)) {
        printf("O grafo e bipartido.\n");
        for (int i = 0; i < numVertices; i++)
            printf("Vertice %d -> cor %d\n", i, color[i]);
    } else {
        printf("O grafo nao e bipartido.\n");
    }

    return 0;
}
