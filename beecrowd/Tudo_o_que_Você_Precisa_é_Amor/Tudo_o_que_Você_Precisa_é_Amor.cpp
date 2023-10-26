#include <bits/stdc++.h>

using namespace std;

int main() {
  int n;
  int p = 1;

  cin >> n;

  while (n--) {
    string s1, s2;
  
    cin >> s1;
    cin >> s2;

    bitset<32> s1_binary(s1);
    bitset<32> s2_binary(s2);

    if(__gcd(s1_binary.to_ulong(), s2_binary.to_ulong()) == 1)
      cout << "Pair #" << p++ << ": Love is not all you need!" << endl;
    else
      cout << "Pair #" << p++ << ": All you need is love!" << endl;
  }

  return 0;
}
