#include <bits/stdc++.h>

using namespace std;

int main() {
  int N;
  string cmd;
  stack<long long int> pilha;
  long long int mem[100];
  
  cin >> N;

  for (int n = 0; n < N; n++){
    int i = 0;
    long long int num = 0;
    string aux = "";

    cin >> cmd;

    if (cmd != "add" && cmd != "mul" && cmd != "div" && cmd != "sub" && cmd != "print") {
      for (i = 0; cmd[i] != '_'; i++)
        aux += cmd[i];
      if(aux == "push") {
        if(cmd[i+1] == 'R') {
          int numMem = 0;
          for (; cmd[i+2] != '\0'; i++)
            numMem = numMem * 10 + cmd[i+2] - '0';
          pilha.push(mem[numMem]);
        } else {
          for (; cmd[i+1] != '\0'; i++)
            num = num * 10 + cmd[i+1] - '0';
          pilha.push(num);
        }
      } else if(aux == "pop") {
        int numMem = 0;
        long long int a = pilha.top(); pilha.pop();
        for (; cmd[i+2] != '\0'; i++)
          numMem = numMem * 10 + cmd[i+2] - '0';
        mem[numMem] = a;
      }
    } else {
      if (cmd == "print") {
        cout << pilha.top() << endl;
        pilha.pop();
      } else if (cmd == "add") {
        long long int a, b;
        a = pilha.top(); pilha.pop();
        b = pilha.top(); pilha.pop();
        pilha.push(a+b);
      } else if (cmd == "sub") {
        long long int a, b;
        a = pilha.top(); pilha.pop();
        b = pilha.top(); pilha.pop();
        pilha.push(b-a);
      } else if (cmd == "mul") {
        long long int a, b;
        a = pilha.top(); pilha.pop();
        b = pilha.top(); pilha.pop();
        pilha.push(a*b);
      } else if (cmd == "div") {
        long long int a, b;
        a = pilha.top(); pilha.pop();
        b = pilha.top(); pilha.pop();
        pilha.push(b/a);
      }
    }
  }

  return 0;
}
