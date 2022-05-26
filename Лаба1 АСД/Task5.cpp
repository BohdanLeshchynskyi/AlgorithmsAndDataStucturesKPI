#include<iostream>
#include<cmath>

using namespace std;

int main(){

    double x,f,mValue;
    x = -3;
    mValue = 0;

    for (int i=0; i<15; i++){
        
        f = x*x*x - 2*x*x + x - 1;
        x += 0.5;
        mValue = max(mValue,f);

    }

    cout<<"The function`s maximal value in range of [-3;4] is: "<<mValue<<endl;

    return 0;
}