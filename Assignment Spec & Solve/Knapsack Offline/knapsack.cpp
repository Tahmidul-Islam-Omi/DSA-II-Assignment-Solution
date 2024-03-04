#include<bits/stdc++.h>

using namespace std;

int main() {

    int n, w;
    cin >> n >> w;

    vector<int> weight(n+1), value(n+1);

    int maxValue = -100000;

    for(int i = 1; i <= n; i++) {
        cin >> value[i] >> weight[i] ;
        maxValue = max(maxValue, value[i]);
    }

    maxValue = maxValue * n;

    //cout << maxValue << endl;

    vector<vector<int>> dp(n + 1, vector<int>(maxValue+1));

    // knapsack problem polytime approximation scheme

    for(int i = 0; i <= n; i++) {
        for(int v = 0; v <= maxValue; v++) {

            //cout << "Hello" << endl;

            if(v <= 0) {
                //cout << "Hi2" << endl;
                dp[i][v] = 0;
            }

            else if(i == 0 && v > 0) {
                //cout << "HiBye" << endl;
                dp[i][v] = 1e9;
                
            }


            else {
                //cout << "Hi3" << endl;
                dp[i][v] = min(dp[i-1][v], dp[i-1][v - value[i]] + weight[i]);
                //cout << "Hi4" << endl;
            }

        }
    }


    int ans = 0;

    for(int v=0; v <= maxValue; v++) {
        //cout << v << " " << dp[n][v] << endl;
        if(dp[n][v] <= w) {
            ans = v;
        }
    }

    cout << ans << endl;

    return 0;
}
