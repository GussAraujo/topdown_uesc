#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N, T, inst = 0, D[100] = {0}, P[600] = {0};

  while (cin >> N >> T && N != 0 && T != 0) {
    inst++;

    for (int i = 0; i < N; i++)
      cin >> D[i] >> P[i];
    
    int result[T+1];

    for (int i = 0; i <= T; i++)
      result[i] = 0;
  
    for (int i = 1; i <= T; i++) {
      for (int j = 0; j <= N; j++) {
        if (D[j] <= i) 
          result[i] = max(result[i], result[i - D[j]] + P[j]);
      }
    }

    cout << "Instancia " << inst << endl << result[T] << endl << endl;
  }
  
  return 0;
}
