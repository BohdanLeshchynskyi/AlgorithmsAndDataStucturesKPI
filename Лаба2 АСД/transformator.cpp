#include<iostream>
#include<cmath>

using namespace std;

void translation(int x){
    int i;
    i=0;
    int xtrans[10000];

    while((x/4)>0){
        xtrans[i] = x%4;
        x/=4;
        if((x/4)>0){ 
        i++;
        }
    }
    i++;
    xtrans[i] = x;

    cout<<"The translated number is:\n";
    for(int k = i; k >=0; k-- ){
        cout<<xtrans[k];
    }
    cout<<endl;
}
void get_initialDecimal(int y){
    int initialX[10000];
    int j = -1;
    int x1 = 0;

    if(y<4){
        cout<<"The initial decimal is:\n"<<y;
    }
    else{
        while(y!=0){
            j++;
            initialX[j] = y%10;
            y/=10;
        }
        for(int l = 0; l<=j; l++){  
            x1+=initialX[l]*pow(4,l);
        }
        cout<<"The initial decimal is:\n"<<x1;
    }    
}
int main(){
    int a;
    int b;
   
    cout<<"Enter a decimal natural number for translation:\n";
    cin>>a;
   
    translation(a);

    cout<<"Enter a number in 4th system to get the initial decimal:\n";
    cin>>b;

    get_initialDecimal(b);

    return 0;
}