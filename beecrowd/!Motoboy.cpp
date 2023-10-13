#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;

  while (cin >> n && n != 0) {    
    int T[n], P[n], sizeMax;

    cin >> sizeMax;

    for (int i = 0; i < n; i++)
      cin >> T[i] >> P[i];
    
    int result[n + 1][sizeMax + 1];

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= sizeMax; j++)
        result[i][j] = 0;

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= sizeMax; j++) {
        result[i][j] = result[i - 1][j];
        if (T[i - 1] <= j) result[i][j] = max(result[i - 1][j], result[i - 1][j - T[i - 1]] + P[i - 1]);
      }
    }

    cout << result[n][sizeMax] << " min." << endl;
  }

  return 0;
}
