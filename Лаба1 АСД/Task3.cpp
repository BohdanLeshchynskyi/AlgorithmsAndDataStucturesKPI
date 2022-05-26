#include<iostream>
#include<cmath> 

using namespace std;

int main(){
    int e;
    double sum = 0;

    cout<<"Enter e for the series`s summands` number: \n";
    cin>>e;

    for ( int k = 1; k < e + 1  ; k++ ){
        
        sum += 1/(4*pow(k,2)-1); // відповідно додаємо члени ряду е разів

    }
       
    cout<<"The series`s sum is: "<<sum<<endl;

    return 0; 
}