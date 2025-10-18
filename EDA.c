//Linguagem C, Matriz de incidência, 2-coloração de grafos, python 
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARESTAS 100
#define VERTICES 100

typedef struct{
    int matriz[VERTICES][ARESTAS];
    int numVertices;
    int numArestas;
}Grafo;

int verificarArestas(){
    FILE *arq;
    char linha[100];
    int linha_1 = 1;
    int linha_2 = 2;
    arq = fopen("exemplo.txt", "r");
    if (arq == NULL) {
        return -1;
    }
    while(fgets(linha, sizeof(linha),arq)){
        if(linha_1==linha_2){
            int i = 0;
            while (linha[i] != '\0' && linha[i] != '\n') {
                i++;
            }
            return i;
        }
        linha_1++;
    }
    fclose(arq);
    return -1;
}

int verificarVertices(){
    FILE *arquivo;
    int i=0;
    char linha[100];
    // Abre o arquivo no modo leitura
    arquivo = fopen("exemplo.txt", "r");
    if (arquivo == NULL) {
        return -1;
    }
    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha),arquivo)){
        i++;
    }
    fclose(arquivo);
    return (i-1);
}

void preencherMatriz(Grafo *g){
    g->numVertices = verificarVertices();
    g->numArestas = verificarArestas();
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
    g->numVertices = verificarVertices();
    g->numArestas = verificarArestas();
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = 0; j < g->numArestas; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

void verticesAdj(Grafo *g, int vx, int vy){
    int i;
    for(i = 0; i<g->numArestas; i++){
        if(g->matriz[vx-1][i]==g->matriz[vy-1][i] && g->matriz[vx-1][i] == 1){
            printf("Sao adjacentes pela aresta: %d", i+1);
            break;
        }
    }
    if(i == g->numArestas){
        printf("Nao sao adjacentes");
    }
}

int grauVertice(Grafo *g, int v){
    int k = 0;
    for(int i = 0; i<g->numArestas; i++){
        if(g->matriz[v-1][i] == 1){
            k++;
        }
    }
    return k;
}

void buscarVizinhos(Grafo *g, int v){
    int k = 0;
    for(int j = 0; j<g->numArestas; j++){
        for(int i = 0; i<g->numVertices; i++){
            if(v-1!=i && g->matriz[v-1][j]==1){
                if(g->matriz[v-1][j]==g->matriz[i][j]){
                    k++;
                    printf("\nO vertice: %d", i+1);
                }
            }
        }
    }
    printf("\nO vertice %d tem %d vizinhos", v, k);
}

void visitarArestas(Grafo *g){
    for(int j = 0; j<g->numArestas; j++){
        for(int i = 0; i<g->numVertices; i++){
            if(g->matriz[i][j]==1){
                printf("\nVertice %d na aresta %d",i+1,j+1);
            }
        }
    }
}

int DFS(Grafo *g, int v, int c, int *color){
    color[v] = c;

    for (int a = 0; a < g->numArestas; a++) {
        if (g->matriz[a][v] == 0)
            continue;

        // Procurar o outro vértice da mesma aresta
        for (int u = 0; u < g->numVertices; u++) {
            if (u != v && g->matriz[a][u]) {
                if (color[u] == -1) {
                    if (!DFS(g, u, 1 - c, color))
                        return 0;
                } else if (color[u] == c) {
                    return 0;  // mesma cor = não bipartido
                }
            }
        }
    }
    return 1;
}

int isBicolor(Grafo *g, int *color){
    for (int i = 0; i < g->numVertices; i++)
        color[i] = -1;

    for (int i = 0; i < g->numVertices; i++)
        if (color[i] == -1)
            if (!DFS(g, i, 0, color))
                return 0;
    return 1;
}

void gerarNovoArq(Grafo *g){
    FILE *arq;
    arq = fopen("NovoGrafo.txt","w");
    if (arq == NULL) {
        printf("Erro ao criar/abrir o arquivo.\n");
    }
    for(int i = 0; i<g->numVertices; i++){
        for(int j = 0; j<g->numArestas; j++){
            fprintf(arq,"%d\t",g->matriz[i][j]);
        }
        fprintf(arq,"\n");
    }
    fclose(arq);
}

int main() {
    Grafo grafo;
    preencherMatriz(&grafo);
    int vertice = verificarVertices();
    int* color = malloc(vertice*sizeof(int));
    int o;
    do {
        printf("\n\n----- MENU -----\n");
        printf("1 - Receber dois vertices e apresentar se sao adjacentes\n");
        printf("2 - Calcular o grau de um vertice qualquer\n");
        printf("3 - Buscar os vizinhos de um vertice qualquer\n");
        printf("4 - Visitar todas as arestas do grafo\n");
        printf("5 - Fazer dupla coloracao\n");
        printf("6 - Gerar novo arquivo\n");
        printf("7 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &o);
        switch (o){
            case 1:
                mostrarMatriz(&grafo);
                printf("\nDigite o numero dos vertices\n");
                printf("Vertice um: ");
                int vx, vy;
                scanf("%d",&vx);
                printf("Vertice dois: ");
                scanf("%d",&vy);
                verticesAdj(&grafo, vx, vy);
                break;
            case 2:
                mostrarMatriz(&grafo);
                printf("\nDigite o numero do vertice: ");
                int v1;
                scanf("%d",&v1);
                int grau = grauVertice(&grafo, v1);
                printf("grau do vertice: %d", grau);
                break;
            case 3:
                mostrarMatriz(&grafo);
                int v2;
                printf("\ndigite um vertice para buscar os vizinhos: ");
                scanf("%d", &v2);
                buscarVizinhos(&grafo, v2);
                break;
            case 4:
                mostrarMatriz(&grafo);
                visitarArestas(&grafo);
                break;
            case 5:
                mostrarMatriz(&grafo);
                if (isBicolor(&grafo, color)) {
                    printf("\nO grafo e bipartido.\n");
                    for (int i = 0; i < vertice; i++)
                        printf("Vertice %d -> cor %d\n", i, color[i]);
                } else {
                    printf("O grafo nao e bipartido.\n");
                }
                break;
            case 6:
                gerarNovoArq(&grafo);
                break;
            // case 7:
            //     Py_Initialize();  // Inicializa o interpretador Python

            //     PyRun_SimpleString("print('Olá do Python!')");
            //     PyRun_SimpleString("import grafos");  // Executa um script Python (sem .py)
            
            //     Py_Finalize();
            //     break;
        }
    }while (o!=8);
    // system("grafo.py");

}
