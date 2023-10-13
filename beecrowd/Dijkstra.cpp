#include <bits/stdc++.h>

using namespace std;

int main() {
  set<string> strings;
  string str;

  while (getline(cin, str)) strings.insert(str);

  cout << strings.size() << endl;

  return 0;
}
