#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

// Classe para representar um Grafo direcionado
class Graph
{
    int V;//Número de Vértices
    list< pair<int, int> > *adj;//Armazenando os vértices e os pesos

public:
    Graph(int V);

    // Função para adicionar uma aresta ao grafo
    void addEdge(int u, int v, int w);

    // Função para achar e printar o menor caminho
    void shortestPath(int s);
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// Um Dijkstra para printar o menor caminho
// do vértice de entrada para todos os outros vértices
void Graph::shortestPath(int source)
{
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;//Cria uma fila de prioridade para guardar os vértices

    vector<int> dist(V, INF);//Cria o vetor de distância e inicia todas as distâncias como infinitas

    pq.push(make_pair(0, source));//Insere a própria origem na fila de prioridade
    dist[source] = 0;//Inicializa a sua distância como zero

    // Loop até a fila de prioridade ficar vazia
    while(!pq.empty())
    {
        int u = pq.top().second;//O primeiro vértice do par é a distância mínima
        pq.pop();//Aqui tiramos ele da fila de prioridade

        // 'i' e usado para obter todos os vertices adjacentes de um vértice
        list< pair<int, int> >::iterator i;
        for(i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;//Pega o ponteiro para o vertice
            int weight = (*i).second;//Pega o peso do vertice adjacente

            // Se tiver um caminho curto para v atraves de u
            if(dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;//Atualiza a distância de v
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Printa as distâncias mais curtas armazenadas no array dist[]
    printf("Distancia do vertice para o source\n");
    for(int i = 0; i < V; ++ i)
        printf("%d \t\t %d\n", i, dist[i]);
}

int main()
{
    int yorn;

    printf("Se voce deseja fazer um teste automatico, digite 1, caso contrario digite 0\n");
    scanf("%d", &yorn);

    if(yorn)
    {
        int V = 9;
        Graph g(V);

        g.addEdge(0, 1, 4);
        g.addEdge(0, 7, 8);
        g.addEdge(1, 2, 8);
        g.addEdge(1, 7, 11);
        g.addEdge(2, 3, 7);
        g.addEdge(2, 8, 2);
        g.addEdge(2, 5, 4);
        g.addEdge(3, 4, 9);
        g.addEdge(3, 5, 14);
        g.addEdge(4, 5, 10);
        g.addEdge(5, 6, 2);
        g.addEdge(6, 7, 1);
        g.addEdge(6, 8, 6);
        g.addEdge(7, 8, 7);

        g.shortestPath(0);
    }
    else
    {
        int n_testes;

        printf("Quantos testes voce deseja fazer?\n");
        scanf("%d", &n_testes);

        for(int i = 0; i < n_testes; i ++)
        {
            int V;
            printf("Digite a quantidade de Vertices que deseja ter para o Grafo %d\n", n_testes);
            scanf("%d", &V);
            Graph g(V);

            for(int j = 0; j < V; j ++)
            {
                int v1, v2, peso;
                printf("Digite, respectivamente o Vertice I, Vertice II e o Peso da aresta entre eles\n");
                scanf("%d %d %d", &v1, &v2, &peso);
                g.addEdge(v1, v2, peso);
            }

            g.shortestPath(0);
        }
    }
}
