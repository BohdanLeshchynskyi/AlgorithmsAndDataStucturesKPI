#include<iostream>

using namespace std;

void reverse(int x){
    if (x!=0){
        /*cout<<x%10<<"\t";
        x/=10;*/
        reverse(x/10);
        cout<<x%10<<"\t";
    }
}

int main(){
    int a;
    cout<<"Enter number:\n";
    cin>>a;
    reverse(a);
    return 0;
}