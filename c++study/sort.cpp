#include <iostream>
#include <vector>

using namespace std;

int PRNG() { 
    static unsigned int seed = 5323; 
    seed = 8253729 * seed + 2396403; 
    return seed % 32768; 
};

const int knights_r[8]={2,2,-2,-2,1,1,-1,-1};
const int knights_c[8]={1,-1,1,-1,2,-2,2,-2};
void swap(int& a, int& b){
    int temp=a;
    a=b;
    b=temp;
}

void quicksort(int* a, int left, int right){
    if(left<right){
        int pivot=a[left], i=left, j=right+1;
        do{
            do i++;while(a[i]<pivot);
            do j--;while(a[j]>pivot);
            if(i<j){
                swap(a[i], a[j]);
            }
        } while(i<j);

        swap(a[j], a[left]);
        quicksort(a, left, j-1);
        quicksort(a, j+1, right);

    }
    
}

int temp[5000000]={0};

void mergesort(int *a, int left, int right){
    if(left<right){
        int mid=int((left+right)/2);

        mergesort(a, left, mid);
        mergesort(a, mid+1, right);
        int i=left, j=mid+1;
        int cnt=0;
        while(i<=mid&&j<=right){
            if(a[i]<a[j]){
                temp[cnt++]=a[i++];
            }else{
                temp[cnt++]=a[j++];
            }
        }
        while(i<=mid){
            temp[cnt++]=a[i++];
        }
        while(j<=right){
            temp[cnt++]=a[j++];
        }
        for(int i=0;i<cnt;i++){
            a[left+i]=temp[i];
        }

    }
    
}

// void swap(int arr[3]){
//     int temp=arr[1];
//     arr[1]=arr[2];
//     arr[2]=temp;
//     return;
// }

int main()
{
    // vector<int> arr;
    int N=100000;
    int* arr=new int[N];
    
    for(int i=0;i<N;i++){
        int next=PRNG();
        arr[i]=next;
    }
    mergesort(arr,0,N-1);
    
    //verify
    bool sorted=true;
    for(int i=0;i<N-1;i++){
        if(arr[i]>arr[i+1]){
            sorted=false;
            break;
        }
    }
    cout<<sorted<<endl;

    return 0;

}
