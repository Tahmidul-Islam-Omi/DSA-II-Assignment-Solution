#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<set>
#include<cstring>

using namespace std;

int visited[100];

class DS {
    vector<int> parent , size;

    public:
        DS(int n) {
            parent.resize(n+1 , 0);
            size.resize(n+1 , 0);

            for(int i=0; i<=n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int findUltParent(int node) {
            

            if( node == parent[node]) {
                return node;
            }

            return parent[node] = findUltParent(parent[node]);
            
        }

        void unionBySize(int u , int v) {
            int ulPar_u = findUltParent(u);
            int ulPar_v = findUltParent(v);

            if( ulPar_u == ulPar_v) {
                return;
            }

            else if(ulPar_u < ulPar_v) {
                parent[ulPar_u] = ulPar_v;
                size[ulPar_v] += size[ulPar_u];
            }

            else {
                parent[ulPar_v] = ulPar_u;
                size[ulPar_u] += size[ulPar_v];
            }

        }
};

bool compareAlgo(const pair < pair<int, int> , int> &a, const pair <pair<int, int> , int> &b) {
    return a.second < b.second;
}


int findMSTWeight (vector< pair < pair<int,int> , int > > edges_info , int vertices) {
    
    DS ds(vertices);

    int mst_weight = 0;

    sort(edges_info.begin() , edges_info.end() , compareAlgo);

    for(int i=0; i< edges_info.size() ; i++) {
        
        int u = edges_info[i].first.first;
        int v = edges_info[i].first.second;


        if(ds.findUltParent(u) != ds.findUltParent(v)) {
            ds.unionBySize(u , v);
            mst_weight += edges_info[i].second;        
        }

    }

    return mst_weight;
    
}

vector<vector<pair < pair<int,int> , int >>> generateCombinations(const vector< pair < pair<int,int> , int > > edges_info, int r, int start, int index) {

    vector<vector<pair < pair<int,int> , int >>> result;

    if (index == r) {
        std::vector< pair < pair<int,int> , int > > combination(r);
        for (int i = 0; i < r; ++i) {
            combination[i] = edges_info[i];
        }
        result.push_back(combination);
        return result;
    }


    for (int i = start; i < edges_info.size(); ++i) {
        vector<vector<pair < pair<int,int> , int >>> subCombinations = generateCombinations(edges_info, r, i + 1, index + 1);

        for (const auto& subCombination : subCombinations) {
            std::vector< pair < pair<int,int> , int > > combination = subCombination; 
            combination[index] = edges_info[i];
            result.push_back(combination);
        }
    }

    return result;
}

bool whether_MST(vector< pair < pair<int,int> , int > > edges_info , int mst_weight) {

    int temp_mst_weight = 0;

    for(int i=0; i< edges_info.size(); ++i) {
        temp_mst_weight += edges_info[i].second;
    }

    if( temp_mst_weight == mst_weight ) {
        return true;
    }

    else {
        return false;
    }

}

void print_MST(vector< pair < pair<int,int> , int > > edges_info ) {

    cout << "[";
    for(int i=0; i< edges_info.size() ; i++) {
        cout << "[" << edges_info[i].first.first << ", " << edges_info[i].first.second << ", " << edges_info[i].second << "]";

        if( i != edges_info.size()-1) {
            cout << ", " ;
        }
    }
    cout << "]" << endl;
}

bool dfs(int root , int parent , vector<vector<int> > adj_list ) {
    
    visited[root] = 1;

    for(auto adjacent_node : adj_list[root]) {
        if(visited[adjacent_node] == 0) {
            if ( dfs( adjacent_node , root , adj_list ) ) {
                return true;  
            }
         }

        else if( adjacent_node != parent) {
            return true;
        }
    }

    return false;
}


bool cycle_detect(const vector<pair<pair<int, int>, int>>& edges_info) {

    vector<vector<int>> adj_list(100);
    set<int> curr_vertices;

    for (int i = 0; i < edges_info.size(); i++) {
        adj_list[edges_info[i].first.first].push_back(edges_info[i].first.second);
        adj_list[edges_info[i].first.second].push_back(edges_info[i].first.first);
        curr_vertices.insert(edges_info[i].first.first);
        curr_vertices.insert(edges_info[i].first.second);

    }

    memset(visited , 0, sizeof(visited));

    for (auto it = curr_vertices.begin(); it != curr_vertices.end(); it++) {
        int vertex = *it;  

        if (visited[vertex] == 0) {
            if ( dfs(vertex , -1 , adj_list) ) {
                return true;
            }
        }

    }

    return false;

}

int main() {

    int vertices , edges;
    cin >> vertices >> edges;

    vector< pair < pair<int,int> , int > > edges_info;

    for(int i=1; i<= edges; i++) {

        int u , v , w;
        cin >> u >> v >> w;

        pair<int, int> pr;
        pr.first = u , pr.second = v;

        edges_info.push_back({pr , w});

    }

    int mst_weight = findMSTWeight(edges_info , vertices);

    vector<vector<pair < pair<int,int> , int >>> possible_mst = generateCombinations(edges_info , vertices-1 , 0, 0);

    cout << "MSTs:" << endl;
    int mst_num = 0;

    for(int i=0; i< possible_mst.size(); i++) {
        if(whether_MST( possible_mst[i] , mst_weight) && !cycle_detect(possible_mst[i])) {
            mst_num++;
            cout << mst_num << " : " ;
            print_MST( possible_mst[i]);
        }
    }

    return 0;
}