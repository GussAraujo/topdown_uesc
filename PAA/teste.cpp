#include <iostream>
#include <math.h>

using namespace std;

int q(int n) {
  if (n == 1) return 1;
  return q(n - 1)  * 2 + 1;
}

int main(){

  int n, a;
  cin >> n;

  a = 1 << n;

  // cout << "shift: " << a - 1<< endl;
  cout << "formula fechada: " << ((pow(2, n)) - 1) << endl;
  cout << "recursao: " << q(n) << endl;
      
  return 0;
}
