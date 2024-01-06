#include<bits/stdc++.h>

using namespace std;

bool maxMatch(vector<vector<int>> G, int jobsAssign[], int u, bool seen[])
{

    int jobs = G[0].size();

    for (int v = 0; v < jobs; v++)
    {
        if (G[u][v] == 1 && !seen[v])
        {
            seen[v] = true;

            if (jobsAssign[v] == -1 || maxMatch(G, jobsAssign, jobsAssign[v], seen))
            {
                jobsAssign[v] = u;
                return true;
            }
        }
    }

    return false;
}

int maximumMatch(vector<vector<int>> G)
{
    // Code here
    int people = G.size();
    int jobs = G[0].size();

    int jobsAssign[jobs];

    memset(jobsAssign, -1, sizeof(jobsAssign));

    int result = 0;

    for (int i = 0; i < people; i++)
    {

        bool seen[jobs];
        memset(seen, false, sizeof(seen));

        if (maxMatch(G, jobsAssign, i, seen) == true)
        {
            result++;
        }
    }

    return result;
}

int main() {

    int m,n;
    cin >> m >> n;

    int size = m+n;

    vector<vector<int>> G(size , vector<int>(size , 0));

    vector<vector<int>> data(size);

    for(int i=0; i<size; i++) {
        int height , age , status;
        cin >> height >> age >> status;

        data[i].push_back(height);
        data[i].push_back(age);
        data[i].push_back(status);

    }

    for(int i=0; i< m; i++) {
        for(int j=m; j<data.size(); j++) {
            if( abs( data[i][0] - data[j][0] ) <= 10 && abs( data[i][1] - data[j][1] ) <=5 && abs (data[i][2] - data[j][2]) == 0  ) {
                G[i][j]=1;
            }
        }
    }

    cout << maximumMatch(G) << endl;
}
