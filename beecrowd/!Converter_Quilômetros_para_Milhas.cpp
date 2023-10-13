#include <bits/stdc++.h>

using namespace std;

int fib(int n) {
    int fib1 = 0, fib2 = 1, fibN;

    if (n == 1 || n == 2 || n == 3) {
      fibN = n;
    } else {
      for (int i = 2; i <= n; ++i) {
        fibN = fib1 + fib2;
        fib1 = fib2;
        fib2 = fibN;
      }
    }

    return fibN;
}

int main() {
  int q;

  cin >> q;

  while (q > 0) {
    int t;
    cin >> t;

    int b[t] = {0}, indice[t], soma = 0;
    int i = t - 1, j = 0;

    while(i > 1){
      int fibI = fib(i);
      if (fibI + soma <= t) {
        indice[j] = i;
        b[i-1] = 1;
        soma += fibI;
        j++;
      }
      i--;
    }
    
    int result = 0;

    for (int i = 2; i < indice[0]; i++) result += fib(i) * b[i];

    cout << result << endl;
    q--;
  }

  return 0;
}
