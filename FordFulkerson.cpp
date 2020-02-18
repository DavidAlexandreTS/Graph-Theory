#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>

using namespace std;

// Define o número de vértices
#define V 6

//O algoritmo de busca que decidi usar foi o BFS
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Cria um array de visitados e marca todos como não visitado
	bool visited[V];
	memset(visited, 0, sizeof(visited));

	queue <int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		for(int v = 0; v < V; v ++)
		{
			if(visited[v] == false && rGraph[u][v] > 0)
			{
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	return (visited[t] == true);
}


int fordFulkerson(int graph[V][V], int s, int t)
{
	int u, v;

	// Cria o grafo residual onde rGraph[i][j] indica a capacidade residual da aresta de i a j
	int rGraph[V][V];

	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			rGraph[u][v] = graph[u][v];

	int parent[V]; // Esse array é preenchido pelo BFS para armazenar o caminho

	int max_flow = 0;

	// Aumente o fluxo enquanto houver caminho da fonte até o final
	while(bfs(rGraph, s, t, parent))
	{
		// Encontra a capacidade residual mínima das arestas
		int path_flow = INT_MAX;
		for(v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);
		}

		// Atualiza as capacidades residuais das arestas
		for(v = t; v != s; v = parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}

        // Adicionar fluxo de caminho ao geral
		max_flow += path_flow;
	}

	// Retorna o fluxo total
	return max_flow;
}

int main()
{
	//Criando um grafo pra testar
	int graph[V][V] = { {0, 16, 13, 0, 0, 0},
						{0, 0, 10, 12, 0, 0},
						{0, 4, 0, 0, 14, 0},
						{0, 0, 9, 0, 0, 20},
						{0, 0, 0, 7, 0, 4},
						{0, 0, 0, 0, 0, 0}
					};

	cout << "O fluxo maximo e " << fordFulkerson(graph, 0, 5);
}

