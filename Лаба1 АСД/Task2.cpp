#include <iostream> 

using namespace std;

int main(){
    int a,b,c;
    cout<<"Enter three numbers to compute them:\n";
    cin>>a;
    cin>>b;
    cin>>c;

    if ( (a == 0)||(b == 0)||(c == 0) ){
        cout<<"The sum is: "<<a+b+c<<endl;
    } 
    else {
        cout<<"The product is: "<<a*b*c<<endl; 
    }

    return 0;
}