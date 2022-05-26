#include<iostream>  
#include<cmath>

using namespace std;

int main(){

    long double x,y,res_xy,result;

    cout<<"Enter x value\n";
    cin>>x;
    cout<<"Enter y value\n";
    cin>>y;
    cout<<"*super hard computing process*\n";

    res_xy = x*y;

    result = (sqrt(1+fabs(res_xy))-3*y)/(fabs(sin(res_xy)-x));
    
    cout<<"The result is: "<<result<<endl;

    return 0;
}