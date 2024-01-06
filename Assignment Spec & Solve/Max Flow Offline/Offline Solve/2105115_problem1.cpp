#include <bits/stdc++.h>

using namespace std;

bool bfs(int vertices, int src, int dest, int parent[100], int rG[100][100])
{
    queue<int> q;
    q.push(src);

    parent[src] = -1;

    int visited[100];
    memset(visited, 0, sizeof(visited));

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        visited[u] = 1;

        for (int v = 1; v <= vertices; v++)
        {
            if (rG[u][v] > 0 & visited[v] == 0)
            {
                parent[v] = u;
                visited[v] = 1;
                q.push(v);

                if (v == dest)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void dfs(int src, int vertices, int visited[100], int rG[100][100])
{
    visited[src] = 1;

    for (int i = 1; i <= vertices; i++)
    {
        if (visited[i] == 0 && rG[src][i] > 0)
        {
            dfs(i, vertices, visited, rG);
        }
    }
}

int main()
{

    int G[100][100], rG[100][100], flow[100][100];

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            G[i][j] = 0;
            flow[i][j] = 0;
        }
    }

    int vertices;
    cin >> vertices;

    int edges;
    cin >> edges;

    for (int i = 1; i <= edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        G[u][v] = w;
        rG[u][v] = w;
    }

    int src, dest;
    cin >> src >> dest;

    int parent[100];
    memset(parent, -1, sizeof(parent));

    int maxFlow = 0;

    while (bfs(vertices, src, dest, parent, rG))
    {
        int pathFlow = INT_MAX;

        int v = dest;

        while (v != src)
        {
            int u = parent[v];
            pathFlow = min(pathFlow, rG[u][v]);
            v = u;
        }

        v = dest;

        while (v != src)
        {

            int u = parent[v];

            rG[u][v] -= pathFlow;
            rG[v][u] += pathFlow;

            if (G[u][v] == 0)
            {
                flow[v][u] -= pathFlow;
            }

            else
            {
                flow[u][v] += pathFlow;
            }

            v = u;
        }

        maxFlow += pathFlow;
    }


    int maxOutFlow = INT_MIN;
    int maxOutFlowNode;


    for (int i = 1; i <= vertices; i++)
    {

        if (i != src && i != dest)
        {
            int tempmax = 0;
            for (int j = 1; j <= vertices; j++)
            {
                if (G[i][j] != 0)
                {
                    tempmax += flow[i][j];
                }
            }

            if (tempmax > maxOutFlow)
            {
                maxOutFlow = tempmax;
                maxOutFlowNode = i;
            }
        }
    }

    cout << maxOutFlowNode << " " << maxOutFlow << endl;

    int visited[100];
    memset(visited, 0, sizeof(visited));

    dfs(src, vertices, visited, rG);

    cout << "[ {";

    int cnt = 0;

    for (int i = 1; i <= vertices; i++)
    {
        if (visited[i] == 1)
        {
            if(cnt == 0) {
                cout << i;
                cnt++;
                continue;
            }

            cout << ", " << i;
        }
    }

    cout << "}, {";

    cnt = 0;

    for (int i = 1; i <= vertices; i++)
    {
        if (visited[i] == 0)
        {
            if(cnt == 0) {
                cout << i ;
                cnt++;
                continue;
            }
            cout << ", " << i;
        }
    }

    cout << "} ]" << endl;


    cout << maxFlow << endl;

}
