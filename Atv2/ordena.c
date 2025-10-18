#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

size_t memoria_alocada = 0;

void* meu_malloc(size_t tamanho) {
    memoria_alocada += tamanho;
    return malloc(tamanho);
}

void meu_free(void* ptr, size_t tamanho) {
    memoria_alocada -= tamanho;
    free(ptr);
}

//BUBBLESORT
void Bubblesort(int v[], int n){
    int aux;
    for (int i=0; i<n-1; i++){ //O(n-1)
        for (int j=0;j<n-i-1;j++){ //O(n-i-1)
            if (v[j]>v[j+1]){ //O(n^2)
                aux = v[j]; //O(n^2)
                v[j] = v[j+1]; //O(n^2)
                v[j+1] = aux; //O(n^2)
            }
        }
    }
}

//SELECTION SORT
int Selmin(int *v,int i, int n){ //O(n-1)
    int k=i; //O(n-1)
    for(int j=i+1;j<n;j++){ //O(n^2)
        if(v[j]<v[k]){ //O(n^2)
            k=j; //O(n^2)
        }
    }
    return k; //O(n-1)
}

void selectionsort(int *v, int n){
    int k;
    for(int i=0;i<n-1;i++){ //O(n-1)
        k=Selmin(v,i,n); //O(n-1)
        int x; //O(n-1)
        x = v[i]; //O(n-1)
        v[i]=v[k]; //O(n-1)
        v[k] = x; //O(n-1)
    }
}

//MERGESORT
void merge(int v[], int l, int m, int r) {
    int n1 = m - l + 1; //O(1)
    int n2 = r - m; //O(1)
    int *L = (int *)meu_malloc(n1 * sizeof(int)); //O(1)
    int *R = (int *)meu_malloc(n2 * sizeof(int)); //O(1)
    for (int i = 0; i < n1; i++) //O(n1)
        L[i] = v[l + i]; //O(n1)
    for (int j = 0; j < n2; j++) //O(n2)
        R[j] = v[m + 1 + j]; //O(n2)
    int i = 0, j = 0, k = l; //O(1)
    while (i < n1 && j < n2) { //O(n)
        if (L[i] <= R[j]) { //O(n)
            v[k] = L[i]; //O(n)
            i++; //O(n)
        } else { //O(n)
            v[k] = R[j]; //O(n)
            j++; //O(n)
        } 
        k++; //O(n)
    }
    while (i < n1) { //O(n1)
        v[k] = L[i]; //O(n1)
        i++; //O(n1)
        k++; //O(n1)
    }
    while (j < n2) { //O(n2)
        v[k] = R[j]; //O(n2)
        j++; //O(n2)
        k++; //O(n2)
    }
    free(L);
    free(R);
}
void mergeSort(int v[], int l, int r) {
    if (l < r) { //O(1)
        int m = l + (r - l) / 2; //O(1)
        mergeSort(v, l, m); //T([n/2])
        mergeSort(v, m + 1, r); //T([n/2])
        merge(v, l, m, r); //O(n)
    }
}

void preencherMelhorCaso(int *v, int n){
    for (int i = 0; i < n; i++) {
        v[i] = i;
    }
}

void preencherPiorCaso(int v[], int n){
    int j = n;
    for(int i = 0; i<n; i++){
        v[i] = j;
        j--;
    }
}

void preencherAleatorio(int v[], int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
}

void imprimir(int v[], int n){
    printf("\nVetor: ");
    for(int i=0;i<n;i++){
        printf("%d,\t",v[i]);
    }
}

void exibir_memoria_dinamica() {
    printf("\nMemoria: %lu\n", (unsigned long)memoria_alocada);
}

void ordenar(int *vetor, char *caso){

    time_t agora;
    struct tm *infoTempo;

    time(&agora);
    infoTempo = localtime(&agora);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", infoTempo);

    char linha[15];
    char palavra[15];

    FILE *arq;
    arq = fopen("ordena.txt","r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }

    clock_t inicio, fim;
    double tempo;
    float vTempo[4];
    int tam;
    fscanf(arq,"%d", &tam);

    printf("\nelementos: %d", tam);

    fgets(linha, sizeof(linha), arq);
    if (fgets(linha, sizeof(linha), arq) != NULL) {
        sscanf(linha, "%s", palavra);
        if (strcmp(palavra, "Bubble") == 0) {
            printf("\nIniciando Bubblesort\n");
            if(strcmp(caso,"aleatorio")==0){
                printf("teste1\n");
                for(int i=0;i<5;i++){
                    preencherAleatorio(vetor, tam);
                    inicio = clock();
                    Bubblesort(vetor, tam);
                    fim = clock();
                    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    vTempo[i] = tempo;
                    printf("\ntempo %d: %f", i, tempo);
                }
                float soma = 0;
                for(int j=0;j<5;j++){
                    soma += vTempo[j];
                }
                float a = 5;
                tempo = soma/a;
                printf("\ntempo medio: %f", tempo);
                printf("\n%s,bubble,%d,aleatorio,%f,%lu\n",buffer,tam,tempo,(unsigned long)memoria_alocada);
            }else{
                inicio = clock();
                Bubblesort(vetor, tam);
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            }
            strcpy(palavra, "bubble");
        }else if(strcmp(palavra, "Selection") == 0){
            printf("\nIniciando Selectionsort\n");
            if(strcmp(caso,"aleatorio")==0){
                for(int i=0;i<5;i++){
                    preencherAleatorio(vetor, tam);
                    inicio = clock();
                    selectionsort(vetor, tam);
                    fim = clock();
                    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    vTempo[i] = tempo;
                }
                float soma = 0;
                for(int j=0;j<5;j++){
                    soma += vTempo[j];
                }
                float a = 5;
                tempo = soma/a;
                printf("\ntempo medio: %f", tempo);
                printf("\n%s,selection,%d,aleatorio,%f,%lu\n",buffer,tam,tempo,(unsigned long)memoria_alocada);
            }else{
                inicio = clock();
                selectionsort(vetor, tam);
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            }
            strcpy(palavra, "selection");

        }else if(strcmp(palavra, "Merge") == 0){
            printf("\nIniciando Mergesort\n");
            printf("teste\n");
            if(strcmp(caso,"aleatorio")==0){
                printf("teste1\n");
                for(int i=0;i<5;i++){
                    preencherAleatorio(vetor, tam);
                    inicio = clock();
                    mergeSort(vetor, 0, tam);
                    fim = clock();
                    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
                    vTempo[i] = tempo;
                    printf("\ntempo: %f", tempo);
                }
                float soma = 0;
                for(int j=0;j<5;j++){
                    soma += vTempo[j];
                }
                float a = 5;
                tempo = soma/a;
                printf("\ntempo medio: %f", tempo);
                printf("\n%s,merge,%d,aleatorio,%f,%lu\n",buffer,tam,tempo,(unsigned long)memoria_alocada);
            }else{
                printf("teste2\n");
                inicio = clock();
                mergeSort(vetor, 0, tam);
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
            }
            strcpy(palavra, "merge");
            printf("teste\n");
        }else{
            printf("\nPalavra nao identificada");
        }
    }
    printf("\n%s,%s,%d,%s,%f,%lu\n", buffer, palavra, tam, caso, tempo, (unsigned long)memoria_alocada);
    FILE *arq1 = fopen("saida.txt", "a");
    fprintf(arq1, "%s,%s,%d,%s,%f,%lu\n", buffer, palavra, tam, caso, tempo, (unsigned long)memoria_alocada);
    printf("\nescrito no arquivo");
    fclose(arq1);
    fclose(arq);
}

int main(){

    FILE *arq;
    arq = fopen("ordena.txt","r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para leitura!\n");
    }
    char linha[15];
    char algoritmo[15];
    fgets(linha, sizeof(linha), arq);
    if (fgets(linha, sizeof(linha), arq) != NULL) {
        sscanf(linha, "%s", algoritmo);
    }
    int tam, k;
    fscanf(arq,"%d", &tam);
    int *vetor = (int *)meu_malloc(tam * sizeof(int));
    //"Data HH:mm:ss", algoritmo, n, caso, tempo, memoria
    fclose(arq);
        printf("\n1-Melhor caso\n");
        printf("2-Pior caso\n");
        printf("3-Caso medio\n");
        printf("4-sair\n");
        scanf("%d",&k);
        switch(k){
            case 1:{
                char caso[] = "melhor";
                printf("teste1\n");
                preencherMelhorCaso(vetor, tam);
                printf("teste2\n");
                ordenar(vetor, caso);
            break;
            }
            case 2:{
                char caso[] = "pior";
                preencherPiorCaso(vetor, tam);
                ordenar(vetor, caso);

            break;
            }
            case 3:{
                char caso[] = "aleatorio";
                ordenar(vetor, caso);
            }
        }
}