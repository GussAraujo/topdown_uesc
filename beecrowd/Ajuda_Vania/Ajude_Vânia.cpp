#include <iostream>

using namespace std;

int main()
{
  int caso = 0, n, sizeMax;

  while (cin >> n >> sizeMax && n != 0 && sizeMax != 0){
    caso++;

    int preco[n], peso[n];
  
    for (int i = 0; i < n; i++)
      cin >> peso[i] >> preco[i];

    int result[n + 1][sizeMax + 1];

    for (int i = 0; i <= n; i++)
      for (int j = 0; j <= sizeMax; j++) 
        result[i][j] = 0;

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= sizeMax; j++) {
        result[i][j] = result[i - 1][j];
        if (peso[i - 1] <= j) result[i][j] = max(result[i - 1][j], result[i - 1][j - peso[i - 1]] + preco[i - 1]);
      }
    }

    cout << "Caso " << caso << ": " << result[n][sizeMax] << endl;
  }

  return 0;
}
