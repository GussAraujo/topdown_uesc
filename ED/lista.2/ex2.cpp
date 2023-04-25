#include <iostream>
#include <math.h>

using namespace std;

int main() {
  int dias[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
  double result[30], intenso = 0.0;
  int indice = 0;

  for (int i = 0; i <= 30; i++) {
    result[i] = sin(0.126 * dias[i] - 1.6);
    cout << i << ": " << result[i] << endl;
    if (result[i] > intenso){
      intenso = result[i];
      indice = i;
    }
  }

  cout << "Dia mais intenso: " << indice << endl;

  return 0;
}
