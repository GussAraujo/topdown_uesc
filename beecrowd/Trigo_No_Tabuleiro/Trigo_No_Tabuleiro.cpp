#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;

  cin >> n;

  while (n--) {
    unsigned long long int graos = 1, qnt;
    cin >> qnt;
    if(qnt == 64) { 
      cout << ULLONG_MAX / (12 * 1000) << " kg" << endl;
    } else {
      graos = (graos<<qnt) - 1;
      cout << graos / (12 * 1000) << " kg" << endl;
    }
  }

  return 0;
}
