#include <iostream>
 

using namespace std;

int coordinates[401][5001];

int main()
{
    int m=400;
    int n=5000;
    int** dynmaic_arr=new int*[m];
    for(int i=0;i<m;i++){
        dynmaic_arr[i]=new int[n];
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            dynmaic_arr[i][j]=i+j;
 
    return 0;
}
