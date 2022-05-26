#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>

using namespace std;

int linearSearch(int sArr[], int size, int n){
    for(int i = 0; i<size; i++){
        if(n==sArr[i]){
            return i;
        }
    }
    return -1;
} 
int binarySearch(int sArr[], int size, int n){
    int mid;
    int low = 0;
    int high = size-1;
    while(low<=high){
        mid = (high + low)/2;
        if(n > sArr[mid]){
           low = mid + 1; 
        }
        else{
             if(n < sArr[mid]){
                high = mid -1;
            }
            else{
                return mid; // found
            }
        }    
    }
    return -1; // not found

}


int main(){
    srand(time(0));

    const int N = 1000;
    int arr[N];
    for(int i=0; i<N; i++){
        arr[i]=rand()%4001 - 2000;  //generating a random array in range [-2000;2000]
        cout<<arr[i]<<'\t';
    }

    cout<<endl;

    for(int j=0; j<(N-1);j++){     // sorting array using bubble sort  
        for(int i=0; i<(N-1); i++){
            int swap = 0;
            if(arr[i]>arr[i+1]){
                swap = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = swap;
            }
        }
    }

    cout<<"The sorted array is: \n"; //printing out the sorted array
    for(int i=0; i<N; i++){
        cout<<arr[i]<<'\t';
    } 
    cout<<"\n";

    int elemS;
    cout<<"Element search(Notice: if no such found -1) \nEnter the element you wanna find the index of: ";
    cin>>elemS;

    clock_t start1 = clock();
    for(int i=0;i<100000;i++){
        linearSearch(arr,N,elemS);
    }
    cout<<"The element`s index is: "<<linearSearch(arr,N,elemS)<<endl; // performing element`s index search using linear search algorythm
    clock_t end1 = clock();
    float seconds1 = (float(end1- start1));
    cout<<"Execution time of linear search: "<<seconds1<<endl; 

    clock_t start2 = clock();
    for(int i=0;i<100000;i++){
        binarySearch(arr,N,elemS);
    }
    cout<<"The element`s index is: "<<binarySearch(arr,N,elemS)<<endl; // performing element`s index search using binary search algorythm
    clock_t end2 = clock();
    float seconds2 = (float(end2- start2));
    cout<<"Execution time of binary search: "<<seconds2; 

    return 0;
}
