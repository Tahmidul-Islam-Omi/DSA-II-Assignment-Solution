#include<bits/stdc++.h>

using namespace std;

int main() {

    int city, road;
    cin >> city >> road;

    int dist[city + 1][city + 1];

    for(int i=0; i<= city; i++) {
        for(int j=0; j<= city; j++) {
            if(i == j) {
                dist[i][j] = 0;
            }
            else {
                dist[i][j] = INT_MAX;
            }
        }
    }

    for(int i=1; i<= road; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w;
    }

    int threshold_cost;
    cin >> threshold_cost;

    for(int k=1; k<= city; k++) {
        for(int i=1; i<= city; i++) {
            for(int j=1; j<= city; j++) {
                if(dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) {
                    continue;
                }

                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    vector< pair<int,int> > v1;

    int min_city = INT_MAX;

    for(int i=1; i<= city; i++) {
        int city_num = 0;
        for(int j=1; j<= city; j++) {

            if(i == j) {
                continue;
            }

            if(dist[i][j] <= threshold_cost) {
                city_num++;
            }
        }

        if(min_city > city_num) {
            min_city  = city_num;
        }

        v1.push_back( {city_num , i} );
    }

    cout << endl;

    for(int i=0; i<v1.size(); i++) {
        if(v1[i].first == min_city) {
            cout << v1[i].second << " ";
        }
    }

    cout << endl;

}