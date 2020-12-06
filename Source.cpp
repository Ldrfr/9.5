#include<stdio.h>
#include <iostream>
#include<malloc.h>
using namespace std;
void equation(double** a, double* b, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << "*x" << j;
            if (j < n - 1)
                cout << "+";
        }
        cout << "=" << b[i] << endl;
    }
    return;
}
double* func(double** a, double* b, int n){
    double max;
    double* x;
    int k, index;
    const double e = 0.0000001; //precise 
    x = new double[n];
    //x = (double*)malloc(n * sizeof(double));
    k = 0;
    while (k < n){
        max = abs(a[k][k]);
        index = k;
        for (int i = k + 1; i < n; i++){
            if (abs(a[i][k]) > max){
                max = abs(a[i][k]);
                index = i;
            }
        }
        // перестановка строк
        if (max < e){
            cout << "null column ";
            cout << index << " in matrix" << endl;
            return 0;
        }
        for (int j = 0; j < n; j++){
            double flag = a[k][j];
            a[k][j] = a[index][j];
            a[index][j] = flag;
        }
        double flag = b[k];
        b[k] = b[index];
        b[index] = flag;
        for (int i = k; i < n; i++){
            double flag = a[i][k];
            if (abs(flag) < e) continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] / flag;
            b[i] = b[i] / flag;
            if (i == k)  continue;
            for (int j = 0; j < n; j++)
                a[i][j] = a[i][j] - a[k][j];
            b[i] = b[i] - b[k];
        }
        k++;
    }
    //reverse
    for (k = n - 1; k >= 0; k--){
        x[k] = b[k];
        for (int i = 0; i < k; i++)
            b[i] = b[i] - a[i][k] * x[k];
    }
    return x;
}
int main(){
    double** a, * b, * x;
    int n;
    cout << " оличество уравнений: ";
    cin >> n;
    a = new double* [n];
    b = new double[n];
    for (int i = 0; i < n; i++){
        a[i] = new double[n];
        for (int j = 0; j < n; j++){
            cout << "a[" << i << "][" << j << "]= ";
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++){
        cout << "b[" << i << "] = ";
        cin >> b[i];
    }
    equation(a, b, n);
    x = func(a, b, n);
    for (int i = 0; i < n; i++)
        cout << "x[" << i << "] =" << x[i] << endl;
    return 0;
}