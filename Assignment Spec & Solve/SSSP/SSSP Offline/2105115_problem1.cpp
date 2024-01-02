#include <bits/stdc++.h>

using namespace std;

class edge
{

    public:

    int city_num;
    int gas_left; 
    int weight;

    edge(int city_num, int gas_left, int weight)
    {
        this->city_num = city_num;
        this->gas_left = gas_left;
        this->weight = weight;
    }
};

struct CompareNode {
    bool operator()(const edge& a, const edge& b) const {
        return a.weight > b.weight;

    }
};

int dijkstra(int city , vector<vector<vector<edge>>> v1 , int src , int dst) {

    priority_queue< pair < int , pair<int,int> > > pq;

    vector<vector<int>> disTo(10000, vector<int>(10000, numeric_limits<int>::max()));

    disTo[src][0] = 0;

    pq.push({ 0 , { src , 0}});

    while (! pq.empty())
    {
        pair<int,int> u = pq.top().second;
        int dist = pq.top().first;
        pq.pop();

        for(auto it: v1[u.first][u.second]) {
            pair<int , int > v = make_pair(it.city_num, it.gas_left);
            int w = it.weight;

            if(dist + w < disTo[v.first][v.second]) {
                disTo[v.first][v.second] = dist+w;

                pq.push({dist + w , {v}});
            } 
        }
        
    }

    if(disTo[dst][0] != INT_MAX) {
        return disTo[dst][0];
    }

    else {
        return INT_MIN;
    }
    
}


int main()
{
    int city, roads, capacity;
    cin >> city >> roads >> capacity;

    int price[city + 1];

    for (int i = 1; i <= city; i++)
    {
        int price_Gas;
        cin >> price_Gas;
        price[i] = price_Gas;
    }

    vector<vector<  vector<edge>  >> v1(1000, vector<vector<edge>>(1000));


    for (int i = 1; i <= city; i++)
    {
        for (int j = 0; j <= capacity - 1; j++)
        {
            edge a( i , j+1, price[i]);
            v1[i][j].push_back(a);
        }
    }


    for(int i=1; i<= roads; i++) {

        int u,v,w;
        cin >> u >> v >> w;

        int k=0;

        for(int i=w; i<= capacity; i++) {
            edge a(v , k ,0);
            v1[u][i].push_back(a);
            k++;
        }

    }

    int src , dst;
    cin >> src >> dst;

    int ans = dijkstra(city , v1 ,src ,dst);

    if ( ans != INT_MIN ) {
        cout << ans << endl;
    }

    else {
        cout << "impossible" << endl;
    }

}