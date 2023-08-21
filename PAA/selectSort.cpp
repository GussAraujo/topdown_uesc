#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void imprimir(vector<int> &array)
{
    for (int item : array)
    {
        cout << item << " ";
    }

    cout << endl;
}

int selectSort(vector<int> &array)
{
    int tam = array.size();

    for (int i = 0; i < tam; i++)
    {
        int pos = i;

        for (int j = i; j < tam; j++)
        {
            if (array[j] < array[pos])
                pos = j;
        }

        swap(array[i], array[pos]);
    }
}

int main()
{
    vector<int> array = {2, 4, 6, 8, 3, 1, 0, 3, 12, 3, 53, 25, 62};

    selectSort(array);
    imprimir(array);

    return 0;
}
