#pragma once
#include <iostream>
using namespace std;

class Matrix
{
    int n, m;
    double **a;
public:
    Matrix (int n, int m)
    {
		this -> n = n;
		this -> m = m;
        a = new double* [n];
        for (int i = 0; i < n; i++)
            a[i] = new double[m];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j]=0;
    }
    void SetMatr ()
    {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                    cin >> a[i][j];
    }
    void PrintMatr ()
    {
        for (int i = 0; i  <n; i++)
        {
            for (int j = 0; j < m; j++)
                    cout << a[i][j] << " ";
            cout << endl << endl;
        }

    }
    Matrix operator+ (Matrix M)
    {
        if (!( n == M.n && m == M.m ))
            return *this;
        Matrix temp(n,m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                temp.a[i][j] = a[i][j] + M.a[i][j];
        return temp;
    }
    Matrix operator* (Matrix M)
    {
        if (!(m==M.n))
            return *this;
        Matrix temp(n, M.m);
        for (int i = 0; i < n; i++)
            for (int j=0; j < M.m; j++)
                for (int r = 0; r < m; r++)
                    temp.a[i][j] += a[i][r] * M.a[r][j];
        return temp;
    }
};
