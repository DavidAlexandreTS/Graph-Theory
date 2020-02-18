#include <bits/stdc++.h>

// Uma struct para representar uma aresta no grafo
struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;//Numero de v�rtices e de edges

    // Representando o Grafo como um array de arestas
    struct Edge* edge;
};

// Cria um Grafo com V v�rtices e E arestas
struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = new Graph;

    graph -> V = V;
    graph -> E = E;
    graph -> edge = new Edge[E];

    return graph;
}

// Fun��o para printar a solu��o
void printArr(int dist[], int n)
{
    printf("Distancia do vertice para o Source\n");
    for(int i = 0; i < n; ++ i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// A fun��o principal que encontra as dist�ncias mais curtas e tamb�m detecta ciclos negativos
void BellmanFord(struct Graph* graph, int src)
{
    int V = graph -> V;
    int E = graph -> E;
    int dist[V];

    // Inicializa as dist�ncias como infinito
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // O caminho do src para qualquer outro v�rtice pode ter no m�ximo | V | - 1 arestas
    for (int i = 1; i <= V - 1; i++)
    {
        for (int j = 0; j < E; j++)
        {
            int u = graph -> edge[j].src;
            int v = graph -> edge[j].dest;
            int weight = graph -> edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    /* Verifica os ciclos de peso negativo. Al�m de garantir dist�ncias menores se o grafo
    n�o tiver ciclo de peso negativo.
    Se conseguirmos um caminho mais curto, ent�o haver� � um ciclo.*/
    for(int i = 0; i < E; i ++)
    {
        int u = graph -> edge[i].src;
        int v = graph -> edge[i].dest;
        int weight = graph -> edge[i].weight;

        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            printf("Grafo contem ciclo negativo");
            return; //Se detectar ciclo negativo, retorna
        }
    }

    printArr(dist, V);

    return;
}

int main()
{
    int option;
    printf("Se voce deseja realizar um teste automatico digite 0, caso contrario digite 1\n");
    scanf("%d", &option);

    if(option)
    {
        int V, E;
        printf("Digite a quantidade de vertices e a de arestas respectivamente\n");
        scanf("%d %d", &V, &E);

        struct Graph* graph = createGraph(V, E);

        int sr, dt, w;
        for(int i = 0; i < E; i ++)
        {
            printf("Digite respectivamente o vertice inicial, o de destino e o peso da aresta que os conecta\n");
            scanf("%d %d %d", &sr, &dt, &w);

            // Adiciona uma aresta de sr para dt com peso w
            graph -> edge[i].src = sr;
            graph -> edge[i].dest = dt;
            graph -> edge[i].weight = w;
        }

        BellmanFord(graph, 0);
    }
    else
    {
        int V = 5;
        int E = 8;

        struct Graph* graph = createGraph(V, E);

        // Adiciona uma aresta de sr para dt com peso w
        graph -> edge[0].src = 0;
        graph -> edge[0].dest = 1;
        graph -> edge[0].weight = -1;

        graph -> edge[1].src = 0;
        graph -> edge[1].dest = 2;
        graph -> edge[1].weight = 4;

        graph->edge[2].src = 1;
        graph->edge[2].dest = 2;
        graph->edge[2].weight = 3;

        graph -> edge[3].src = 1;
        graph -> edge[3].dest = 3;
        graph -> edge[3].weight = 2;

        graph -> edge[4].src = 1;
        graph -> edge[4].dest = 4;
        graph -> edge[4].weight = 2;

        graph -> edge[5].src = 3;
        graph -> edge[5].dest = 2;
        graph -> edge[5].weight = 5;

        graph -> edge[6].src = 3;
        graph -> edge[6].dest = 1;
        graph -> edge[6].weight = 1;

        graph -> edge[7].src = 4;
        graph -> edge[7].dest = 3;
        graph -> edge[7].weight = -3;

        BellmanFord(graph, 0);
    }

}
