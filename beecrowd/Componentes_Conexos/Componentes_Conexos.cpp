#include <bits/stdc++.h>

using namespace std;

void DFS(int raiz, vector<vector<int>> &listAdj, vector<bool> &visitado, vector<int> &connected){
    visitado[raiz] = true;
    connected.push_back(raiz);
    for(auto x: listAdj[raiz]) {
      if(!visitado[x])
        DFS(x, listAdj, visitado, connected);
    }
}

int main() {
  int N, inst = 1;
  cin >> N;

  while (N--) {
    int V, E, conn = 0;
    char str1, str2;
    cin >> V >> E;

    vector<vector<int>> adj(V);
    vector<bool> visited(V, false);

    for (int i = 0; i < E; i++) {
      cin >> str1 >> str2;      
      adj[str1 - 'a'].push_back(str2 - 'a');
      adj[str2 - 'a'].push_back(str1 - 'a');
    }

    cout << "Case #" << inst++ << ":" << endl;

    for (int i = 0; i < V; ++i) {
      vector<int> connected;
      if (!visited[i]) {
        DFS(i, adj, visited, connected);
        sort(connected.begin(), connected.end());
        conn++;
        for (int i = 0; i < connected.size(); ++i) 
          cout << (char)(connected[i] + 'a') << ',';      
        cout << endl;
      }
    }

    cout << conn << " connected components" << endl << endl;
  }

  return 0;
}
