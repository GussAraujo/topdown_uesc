#include <bits/stdc++.h>

using namespace std;

int dynamic(int T, int D[], int P[], int N) {
  if (N == 0 || T == 0) {
    return 0;
  }

  if (D[N - 1] > T) {
    return dynamic(T, D, P, N - 1);
  } else {
    return max(P[N - 1] + dynamic(T - D[N - 1], D, P, N), dynamic(T, D, P, N - 1));
  }
}

int main() {
    int N, T, inst = 0, D[100] = {0}, P[600] = {0};;

    while (cin >> N >> T && N != 0 && T != 0) {
      inst++; 

      for (int i = 0; i < N; i++)
        cin >> D[i] >> P[i];

      int resultado = dynamic(T, D, P, N);
      cout << "Instancia " << inst << endl << resultado << endl << endl;
    }

    return 0;
}
