#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cmath>

using namespace std;

int main(){
    srand(time(0));
    int a =16;
    int maxi;
    int arrayb[a];
    int arrayc[a/2];

    for ( int i=0; i<a; i++){
       arrayb[i]=rand()%10; // заповнюємо масив випадковими числами
    }
    for (int i=0; i<a/2; i++){
       arrayc[i]=arrayb[i]+arrayb[15-i]; //заповнюємо новий масив значеннями з попереднього відповідно до умови
       cout<<arrayc[i]<<'\t';               
    }

    cout<<endl;

    maxi = arrayc[0];

    for ( int i = 1; i<a/2; i++ ){
        maxi = max(maxi,arrayc[i]);
    }

    cout<<"The max is: "<<maxi<<endl;

    return 0;

}