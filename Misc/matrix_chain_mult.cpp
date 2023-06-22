
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

// Source : https://sites.radford.edu/~nokie/classes/360/dp-matrix-parens.html

vector<vector<int>> m; // Table for storing the minimum number of multiplications.

int chainMatrix(vector<int> p, int i, int j)
{
    if (m[i][j] != -1)
    {
        return m[i][j];
    }
    if (i == j)
    {
        return 0;
    }
    m[i][j] = INT_MAX;

    
#pragma omp parallel for
    for (int k = i; k < j; k++)
    {
        m[i][j] = min(
            m[i][j], chainMatrix(p, i, k) + chainMatrix(p, k + 1, j) + p[i - 1] * p[k] * p[j]);
    }
    return m[i][j];
}
int MatrixChainOrder(vector<int> p, int n)
{
    return chainMatrix(p, 1, n - 1); // m[1][n-1] has the minimum number of multiplications.
}

int main()
{

    // There are 3 matrices here with 1*2, 2*3, 3*4.
    vector<int> ar{1000, 2000, 1000, 2500};
    int n = ar.size();

    vector<int> blank(*max_element(ar.begin(), ar.end()), -1);
    for (int i = 0; i < *max_element(ar.begin(), ar.end()); i++)
    {
        m.push_back(blank);
    }

    omp_set_num_threads(8);

    cout << "Minimum number of multiplications is "
         << MatrixChainOrder(ar, n);
}
