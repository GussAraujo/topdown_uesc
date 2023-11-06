#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<long long int> cartoes;
vector<vector<long long int>> memo;

long long int maxScore(int left, int right, int turn) {
    if (left > right) {
        return 0;
    }
    if (memo[left][right] != -1) {
        return memo[left][right];
    }

    long long int score;
    if (turn % 2 == 1) {
        score = max(maxScore(left + 1, right, turn + 1) + cartoes[left], maxScore(left, right - 1, turn + 1) + cartoes[right]);
    } else {
        score = min(maxScore(left + 1, right, turn + 1), maxScore(left, right - 1, turn + 1));
    }

    memo[left][right] = score;
    return score;
}

int main() {
    int n;
    while (cin >> n) {
        memo.clear();
        cartoes.clear();
        memo.resize(n + 1, vector<long long int>(n + 1, -1));
        cartoes.push_back(0);
        long long int aux;
        for (int i = 0; i < n; i++) {
            cin >> aux;
            cartoes.push_back(aux);
        }

        long long int result = maxScore(1, n, 1);
        cout << result << endl;
    }
    return 0;
}
