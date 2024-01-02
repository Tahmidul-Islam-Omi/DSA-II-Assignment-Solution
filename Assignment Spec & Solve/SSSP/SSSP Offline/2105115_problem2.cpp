#include <bits/stdc++.h>

using namespace std;

int bellman_ford(int nodes, vector<pair<pair<int, int>, int>> adjList, int src, int dst)
{

    vector<int> dist(nodes + 1, INT_MAX);

    dist[src] = 0;

    for (int i = 0; i < nodes - 1; i++)
    {
        for (auto it : adjList)
        {
            int u = it.first.first;
            int v = it.first.second;
            int wt = it.second;

            if (dist[u] != INT_MAX && dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
            }
        }

    }

    return dist[dst];

}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;

    vector<pair<pair<int, int>, int>> edges_info;

    for (int i = 1; i <= edges; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;

        edges_info.push_back({{a, b}, w});
    }

    int new_a, new_b;
    cin >> new_a >> new_b;

    int l, h;
    cin >> l >> h;

    int src, dst;
    cin >> src >> dst;

    int prev_dist = bellman_ford(nodes , edges_info , src ,dst);

    int d = bellman_ford(nodes , edges_info , new_b , new_a);

    if( d == INT_MAX || -d < l) {
        edges_info.push_back( {{ new_a, new_b} , l });
        int curr_dist = bellman_ford(nodes , edges_info , src , dst);

        if(curr_dist <  prev_dist) {
            cout << l << " " << curr_dist << endl;
        }

        else {
            cout << "impossible" << endl;
        }
    }

    else if( -d > h ) {
        cout << "impossible" << endl;
    }

    if(-d >= l && -d <= h) {
        edges_info.push_back( {{ new_a, new_b} , -d });
        int curr_dist = bellman_ford(nodes , edges_info , src , dst);

        if(curr_dist <  prev_dist) {
            cout << -d << " " << curr_dist << endl;
        }

        else {
            cout << "impossible" << endl;
        }
    }

}