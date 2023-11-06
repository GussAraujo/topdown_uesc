#include <bits/stdc++.h>

using namespace std;

long long int dp[10001];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while(cin >> n)
    {
        long long int aux;
        vector<long long int> cartoes;
        cartoes.push_back(0);

        for(int i = 0; i < n; i++) {
            cin >> aux;
            cartoes.push_back(aux);
        }

        for(int i = 0; i <= n; i++)
            dp[i] = 0;

        int turn = 1;

        while(turn < n) {
            for(int i = 1; i + turn <= n; i++) {
                if(turn % 2)
                  dp[i] = max(dp[i] + cartoes[i + turn], dp[i + 1] + cartoes[i]);
                else
                  dp[i] = min(dp[i], dp[i + 1]);
            }
            turn++;
        }
        cout << dp[1] << endl;
    }
}
