#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;

  while (cin >> n && n) {
    int g, gols1 = 0, gols2 = 0;
    string nomes[n], time1, time2;

    for (int i = 0; i < n; i++)
      getline(cin, nomes[i]);
      
    cin >> g;

    for (int i = 0; i < g; i++) {
      cin >> time1 >> time2 >> gols1 >> gols2;

      if (time1 == nomes[0]) {
        gols1 = 0;
      }
      if (time2 == nomes[1]) {
        gols2 = 0;
      }
    }
    
  }

  return 0;
}
