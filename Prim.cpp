#include<bits/stdc++.h>

using namespace std;
# define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));
}

void primMST(vector<pair<int,int> > adj[], int V)
{
	// Cria uma fila de prioridade para guardar os vértices  que estão sendo pré-MST
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

	int src = 0;

	// Cria um array de chaves e inicia todas como infinito
	vector<int> key(V, INF);

	// Para armazenar o array que armazena a MST
	vector<int> parent(V, -1);

	// Para acompanhar os vértices incluídos na MST
	vector<bool> inMST(V, false);

	// Insere a própria origem na fila de prioridade e inicializar a chave como 0
	pq.push(make_pair(0, src));
	key[src] = 0;

	while(!pq.empty())
	{
        // O primeiro vértice no par é a chave mínima
        // no segundo guardamos o ponteiro pra o que tá guardado
		int u = pq.top().second;
		pq.pop();

        // Inclui o vértice na MST
		inMST[u] = true;

		// Vai em todos os vizinhos de u
		for(auto x : adj[u])
		{
			// Pega todos os ponteiros de vértice peso dos vizinhos de u
			int v = x.first;
			int weight = x.second;

			// Se v não esta na MST e o peso de (u, v) é menor que o atual
			if(inMST[v] == false && key[v] > weight)
			{
				// Atualiza a chave de v
				key[v] = weight;
				pq.push(make_pair(key[v], v));
				parent[v] = u;
			}
		}
	}

	// Printa a MST
	for(int i = 1; i < V; ++ i)
		printf("%d - %d\n", parent[i], i);
}

int main()
{
    int op;
    printf("Digite 1 caso deseje rodar um teste manual, para um teste automatico digite 0\n");
    scanf("%d", &op);

    if(op)
    {
        int V, E;
        printf("Digite a quantidade de vertices e a de arestas que deseja ter em seu grafo(respectivamente)\n");
        scanf("%d %d", &V, &E);

        vector<iPair > adj[V];

        int v1, v2, w;
        for(int i = 0; i < E; i ++)
        {
            printf("Digite o vertice inicial, o adjacente e o peso da aresta que os conecta\n");
            addEdge(adj, v1, v2, w);
        }

        primMST(adj, V);
    }
    else
    {
        int V = 9;
        vector<iPair > adj[V];

        addEdge(adj, 0, 1, 4);
        addEdge(adj, 0, 7, 8);
        addEdge(adj, 1, 2, 8);
        addEdge(adj, 1, 7, 11);
        addEdge(adj, 2, 3, 7);
        addEdge(adj, 2, 8, 2);
        addEdge(adj, 2, 5, 4);
        addEdge(adj, 3, 4, 9);
        addEdge(adj, 3, 5, 14);
        addEdge(adj, 4, 5, 10);
        addEdge(adj, 5, 6, 2);
        addEdge(adj, 6, 7, 1);
        addEdge(adj, 6, 8, 6);
        addEdge(adj, 7, 8, 7);

        primMST(adj, V);
    }

}
