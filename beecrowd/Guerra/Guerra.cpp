#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int t, cont = 0;
    cin >> t;

    int Q[t], N[t];

    for (int i = 0; i < t; i++)
        cin >> Q[i];
    for (int i = 0; i < t; i++)
        cin >> N[i];

    sort(N, N + t);
    sort(Q, Q + t);

    for (int i = 0; i < t; i++) {
        for (int j = i; j < t; j++) {
            if (N[i] >= Q[j]) {
                cont++;
                break;
            }
        }
    }

    cout << cont << endl;

    return 0;
}
