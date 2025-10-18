import networkx as nx
import matplotlib.pyplot as plt


def verificarArestas():
    with open("NovoGrafo.txt", "r") as f:
        linha = f.readline()
        return len(linha.strip().split())

def verificarVertices():
    with open("NovoGrafo.txt", "r") as f:
        return sum(1 for _ in f)

def preencher_matriz():
    numVertices = verificarVertices()
    numArestas = verificarArestas()

    matriz = [[0 for _ in range(numArestas)] for _ in range(numVertices)]

    with open("NovoGrafo.txt", "r") as arq:
        for i, linha in enumerate(arq):
            for j, caractere in enumerate(linha.strip().split()):
                if caractere == '1':
                    matriz[i][j] = 1
                else:
                    matriz[i][j] = 0
    return matriz

G = nx.Graph()
with open("NovoGrafo.txt", "r") as arq:
    for i, linha in enumerate(arq):
        numV = i+1
        G.add_node(f'v{numV}', tipo="letra")
matriz = preencher_matriz()
a = verificarArestas()
vert = verificarVertices()

for j in range(a):
    vetor = [0]*vert
    for i in range(vert):
        if matriz[i][j] == 1:
            vetor[i] = 1
        else:
            vetor[i] = 0
    vertice = [v+1 for v, valor in enumerate(vetor) if valor == 1]
    numA = j+1
    G.add_edge(f'v{vertice[0]}',f'v{vertice[1]}', label=f'a{numA}')\

pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_size=500, node_color='green')
edge_labels = nx.get_edge_attributes(G, 'label')
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels, font_color='red')
plt.show()