#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

void FisherYetsAlgor(int arr[], int size){
    srand(time(0));
    for(int n=size-1; n>0; n--){
        int swap;
        int indx=rand()%(n+1);
        swap=arr[indx];
        arr[indx]=arr[n];
        arr[n]=swap;
    }
    for(int i=0; i<size; i++){
        cout<<arr[i]<<"\t";
    }
}

int equal(int x, int y){
    int sumX = 0;
    int sumY = 0;
    while(x!=0){
        sumX+=x%10;
        x/=10;
    }
    while(y!=0){
        sumY+=y%10;
        y/=10;
    }
    return (sumX>sumY)+2*(sumX<sumY);
} 

void selectionSort(int arr[], int size){
    for(int i=0; i<size-1; i++){
        int inf = i;
        for(int j=i+1; j<size; j++){
            if(equal(arr[j],arr[inf])==2){
                inf = j;
            }
            if(equal( arr[j],arr[inf])==0 && arr[j]<arr[inf] ){
                inf = j;
            }
        }
        int swap;
        swap = arr[i];
        arr[i] = arr[inf];
        arr[inf] = swap; 
    }
    for(int i=0; i<size; i++){
        cout<<arr[i]<<"\t";
    }
}

int main(){
    const int N = 200;
    int arr[N];
    
    cout<<"The initial array: \n";
    for(int i=0; i<N; i++){
        arr[i]=1+i;
        cout<<arr[i]<<"\t";
    }
    cout<<endl;
    cout<<endl;

    cout<<"The array mixed using Fisher-Yates algorithm: \n";
    FisherYetsAlgor(arr,N);

    cout<<endl;
    cout<<endl;
    
    cout<<"The array sorted using selection sort with given criteria: \n";
    selectionSort(arr,N);

    return 0;
}