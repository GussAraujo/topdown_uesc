#include <bits/stdc++.h>

using namespace std;

int tab[8][8] = {0};

int main (){
  int i[2];
  char c[2];

  while (cin >> c[0] >> i[0] >> c[1] >> i[1]) {
    tab[i[0]-1][c[0] - 'a'] = 1;


    cout << "  a b c d e f g h" << endl;
    for (int i = 0; i < 8; i++) {
      cout << i+1 << " ";
      for (int j = 0; j < 8; j++) {
        cout << tab[i][j] << " ";
      }
      cout << endl;
    }
  }

  return 0;
}
